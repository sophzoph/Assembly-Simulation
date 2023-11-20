#ifndef __JE_INSTRUCTION_HPP
#define __JE_INSTRUCTION_HPP

#include <string>
#include "ProgramState.hpp"
#include "Statement.hpp"

class JEInstruction : public Statement
{
public:
	JEInstruction(const std::string & dst);
	void execute(ProgramState * state) const override;

// added below
private:
	std::string m_dst;
};


#endif
