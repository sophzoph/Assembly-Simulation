#include <string>
#include "SubtractionInstruction.hpp"


SubtractionInstruction::SubtractionInstruction(const std::string & dest, const std::string & src)
    : destinationRegister(dest), source(src)
{}

void SubtractionInstruction::execute(ProgramState * state) const
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
    state->setRegister(destinationRegister[1] - 'a', currentRegValue - sourceValue);
    state->nextCounter();
}