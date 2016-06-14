#ifndef LOGICGATES_H
#define LOGICGATES_H

#include <vector>
#include <string>

using namespace std;
enum  class LOGIC_GATE {AND, OR, NOT, NAND, NOR};

class LogicGates
{
    public:
        LogicGates(enum LOGIC_GATE, int fanInValue = 1);
        int fanIn;
        int weight;
        virtual ~LogicGates();
        vector<double> neuralNewtork;
        int solve(vector<int> signals);
        void generateTruthTable();

    protected:

    private:
};

#endif // LOGICGATES_H
