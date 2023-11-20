#include <string>
#include "CmpInstruction.hpp"


CmpInstruction::CmpInstruction(const std::string & lhs, const std::string & rhs)
    : m_lhs(lhs), m_rhs(rhs)
{}

void CmpInstruction::execute(ProgramState * state) const
{
    int leftVal;
    int rightVal;
    // convert the left value

    if((m_lhs[0] == '-' and std::isdigit(m_lhs[1])) or std::isdigit(m_lhs[0])){
        leftVal = std::stoi(m_lhs);
    }
    else{
        leftVal = state->getRegister(m_lhs[1] - 'a');
    }

    //Convert the right value
    if ((m_rhs[0] == '-' and std::isdigit(m_rhs[1])) or std::isdigit(m_rhs[0])){
        rightVal = std::stoi(m_rhs);
    }
    else{
        rightVal = state->getRegister(m_rhs[1] - 'a');
    }

    // compare the two values to properly set the condition register in ProgramState
    if (leftVal < rightVal){
        state->setCondition(1);  // 1 represents less than 
    }
    else if (leftVal == rightVal){
        state->setCondition(2);   // 2 represents equal
    }
    else{
        state->setCondition(3);  // 3 represents greater than
    }
    // increment pc
    state->nextCounter();
}
