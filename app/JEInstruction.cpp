#include <string>
#include "JEInstruction.hpp"


JEInstruction::JEInstruction(const std::string & dst) :m_dst(dst)
{}

void JEInstruction::execute(ProgramState * state) const
{   
    // if the most recent comparison condition is equal then jump to the target line
    if (state->getCondition() == 2){  // 2 represents equal
        int jumpTarget = std::stoi(m_dst);
        if (jumpTarget <= 0){
            state->terminate();
        }
        state->setCounter(jumpTarget);
    }
    // Move to the next line if the condition for the comparison is not equal
    else{
        state->nextCounter();
    }
}
