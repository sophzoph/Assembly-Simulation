#include <string>
#include "IncInstruction.hpp"


IncInstruction::IncInstruction(const std::string & reg) : registerName(reg)
{}

void IncInstruction::execute(ProgramState * state) const
{
    // get the specified register's value
    int currentRegValue = state->getRegister(registerName[1] - 'a');
    state->setRegister(registerName[1] - 'a', currentRegValue + 1);   // set its value to current val + 1
    state->nextCounter();
}