#ifndef CIRCUIT_H
#define CIRCUIT_H
#include "Circuit.h"
#include "LogicGates.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct Signals{
    string name = "sinal generico";
    int id = -1;
    int value = -1;
};

class Circuit
{
    public:
        Circuit();
        virtual ~Circuit();
        int solveCircuit(string F, vector<Signals> inputs);

    protected:

    private:
        vector<Signals> S;
        int findSignal(string name);
        int solveLogicGate(int x1, int x1id, int x2, int x2id, string gate, int gateid);
};

#endif // CIRCUIT_H
