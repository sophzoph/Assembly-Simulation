#include <string>
#include "AddInstruction.hpp"


AddInstruction::AddInstruction(const std::string & dest, const std::string & src)
    : destinationRegister(dest), source(src)  // added this
{}

void AddInstruction::execute(ProgramState * state) const
{
    int sourceValue;
    if ((source[0] == '-' and std::isdigit(source[1])) or std::isdigit(source[0])){
        sourceValue = std::stoi(source);
    }
    else{
        sourceValue = state->getRegister(source[1] - 'a');
    }
    // get the current value in the destination register
    int currentRegValue = state->getRegister(destinationRegister[1] - 'a');
    // set the destination register to the current + value from the source
    state->setRegister(destinationRegister[1] - 'a', currentRegValue + sourceValue);
    state->nextCounter();
}