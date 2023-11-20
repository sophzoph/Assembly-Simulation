#ifndef __PROGRAM_STATE_45C_HPP
#define __PROGRAM_STATE_45C_HPP

#include <vector>
// added the include below
//#include <Statement.hpp>
#include <string>


class Statement; // included this as a forward declaration

class ProgramState
{

public:

	ProgramState();
	~ProgramState();

	size_t getCounter() const;


	// terminate means quit when something bad happened (e.g., trying to access a non-existent register)
	void terminate();

	// returns true if we're done running the program (and haven't crashed).
	bool done() const; 

	// Registers are numbered 0 .. NUM_REGISTERS - 1
	// eax is 0, ebx is 1, etc. 



// If you want to add additional public member functions, you may do so here.
// The above functions must remain with their given interface: 
//	the grading script expects it.
	void setFinished(bool value);
	void setRegister(size_t registerNum, int value);
	void nextCounter();
	void addInstruction(Statement* instruction);
	Statement* getInstruction(size_t lineNum);
	int getRegister(size_t registerNum) const;
	const int& getCondition();    // to get the comparison operator after a CMP instruction
	void setCondition(int condition);   // for comparisons
	void setCounter(size_t lineNum);
	const std::vector<Statement*> getInstructions();
	void setJump(bool jump);
	bool getJump();

	size_t NUM_REGISTERS = 16;
	// void printRegisters();  // uncomment if need to use function to print register values

private:


// If you want to add private member variables, you may do so here.
	std::vector<int> registers;
	size_t counter;
	bool finished;
	std::vector<Statement*> instructions;
	int conditionRegister;   // where 1 means less than, 2 means equal, 3 means greater than
	bool isJump;
};



#endif



