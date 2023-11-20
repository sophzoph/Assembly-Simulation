#include <string>
#include "JmpInstruction.hpp"


JmpInstruction::JmpInstruction(const std::string & dst) : m_dst(dst)
{}

void JmpInstruction::execute(ProgramState * state) const
{
    int jumpTarget = std::stoi(m_dst);  // cannot be a negative m_dst
    if (jumpTarget <= 0){
        state->terminate();
    }
    state->setCounter(jumpTarget);
}
