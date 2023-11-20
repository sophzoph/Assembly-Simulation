#include <string>
#include "JLInstruction.hpp"


JLInstruction::JLInstruction(const std::string & dst) : m_dst(dst)
{}

void JLInstruction::execute(ProgramState * state) const
{
    if(state->getCondition() == 1){   // 1 represents less than
        int jumpTarget = std::stoi(m_dst);
        if (jumpTarget <= 0){
            state->terminate();
        }
        state->setCounter(jumpTarget);
    }
    else{
        state->nextCounter();
    }
}
