#include <string>
#include "MoveInstruction.hpp"
#include <iostream>


MoveInstruction::MoveInstruction(const std::string & dest, const std::string & src) 
    : destinationRegister(dest), source(src)  // added this
{}

void MoveInstruction::execute(ProgramState * state) const
{
    int value;
    if ((source[0] == '-' and std::isdigit(source[1])) or std::isdigit(source[0])){
        value = std::stoi(source);   // convert string to int
    }
    else{
        if (source.length() == 3 and source[0] == 'e' and source[2] == 'x'){
            value = state->getRegister(source[1] - 'a');   // if src is register, get its value
        }
        else{
            state->terminate();  // for invalid register name, terminate
        }

    }
    //Set the value in dest register
    state->setRegister(destinationRegister[1] - 'a', value);
    // go to the next line 
    state->nextCounter();
}
