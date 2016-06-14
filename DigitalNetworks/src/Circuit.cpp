#include "Circuit.h"
#include "LogicGates.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>

Circuit::Circuit()
{
    //ctor
}

Circuit::~Circuit()
{
    //dtor
}

int Circuit::findSignal(string name){
    int result=-1;
    for(int i=0; i<S.size();i++){
        if(S[i].name == name)
            result = S[i].value;
    }
    return result;
}


 int Circuit::solveLogicGate(int x1, int x1id, int x2, int x2id, string gate, int gateid){
    vector<int> sinais;
    int value;
    int local_weight;
    sinais.push_back(x1);
    if(gate == "or"){
        sinais.push_back(x2);
        LogicGates logicGate(LOGIC_GATE::OR, 2);
        value = logicGate.solve(sinais);
        local_weight = logicGate.weight;
    }
    else if(gate == "not"){
        LogicGates logicGate(LOGIC_GATE::NOT);
        value = logicGate.solve(sinais);
        local_weight = logicGate.weight;
    }
    else if(gate == "and"){
        sinais.push_back(x2);
        LogicGates logicGate(LOGIC_GATE::AND, 2);
        value = logicGate.solve(sinais);
        local_weight = logicGate.weight;
    }
    else if(gate == "nand"){
        sinais.push_back(x2);
        LogicGates logicGate(LOGIC_GATE::NAND, 2);
        value = logicGate.solve(sinais);
        local_weight = logicGate.weight;
    }
    if(gate == "nor"){
        sinais.push_back(x2);
        LogicGates logicGate(LOGIC_GATE::NOR, 2);
        value = logicGate.solve(sinais);
        local_weight = logicGate.weight;
    }
    // Imprime as arestas, com o respectivo peso
    cout << x1id << " -> " << gateid <<"[label=\"" << local_weight << "\"];" << endl;
    cout << x2id << " -> " << gateid <<"[label=\"" << local_weight << "\"];" << endl;
    // Atualiza / o valor dos vértices
    cout << gateid << "[label=\"" << gate << " / " << value << "\"];" <<endl;
    return value;

}


int Circuit::solveCircuit(string F, vector<Signals> inputs){

    //Ler a string
    string buf; // Have a buffer string
    stringstream ss(F); // Insert the string into a stream
    vector<string> bool_func; // Create vector to hold our words
    stack <Signals> P;
    S = inputs;
    int result=-1;
    int vert_id = 1;
    stack <Signals> BU;
    // Inicia o arquivo de saída
    cout << "digraph { " << endl;
    cout << 0 << "[label=\"" << 1 << "\"];" <<endl;

    while (ss >> buf)
        bool_func.push_back(buf);

    for(int i=0; i<bool_func.size();i++){
        if(bool_func[i] == ")"){

            Signals in1, in2, gate;
            in1 = P.top();
            P.pop();
            if(!P.empty()){
                gate = P.top();
                P.pop();
                if(gate.name!="not"){
                    in2 = P.top();
                    P.pop();
                }
//                cout << in1.id << " -> " << gate.id << ";" << endl;
//                cout << in2.id << " -> " << gate.id << ";" << endl;

                // Calcula o valor lógico da equação Fan-in 2
                gate.value = solveLogicGate(in1.value,in1.id,in2.value,in2.id,gate.name,gate.id);
                if(P.empty())
                     result = gate.value;
                P.push(gate);
            }
            else
                result = in1.value;
        }
        else if (bool_func[i] != "("){

            Signals j;
            Signals iterate;
            j.name = bool_func[i];
            j.value = findSignal(j.name);
            // Caso seja um sinal estático, verifica se já existe vértice, se for o caso, copia o ID
            if (j.value != -1 ){
                stack <Signals> it;
                it = BU;
               while (it.size()){
                iterate = it.top();
                it.pop();
                if (iterate.name == j.name)
                    j.id = iterate.id;
               }

            }
            if (j.id == -1){
                    j.id = vert_id++;
                    if (j.value == -1 )
                        cout << 0 << " -> " << j.id << "[label=\"10\"];" << endl;
            }
            P.push(j);
            BU.push(j);

            //Gera os Vértices, inserindo o valor para os sinais estáticos (A, B, C, etc)
            if (j.value != -1)
                cout << j.id << "[label=\"" << j.name << " / " << j.value << "\"];" <<endl;
            else
                cout << j.id << "[label=\"" << j.name << "\"];" <<endl;
        }
    }
    cout << "}" << endl;
    return result;
}
