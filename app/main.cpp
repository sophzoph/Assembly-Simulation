#include <iostream>
#include <fstream>
#include "ProgramState.hpp"
#include "runSim.hpp"


int main()
{
    std::ifstream in{"test.txt"};
    ProgramState ps;
    runSimulator(in, &ps);


    return 0;
}

