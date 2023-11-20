#include <vector>
#include <stdlib.h>
#include "ProgramState.hpp"
// added the include below
#include "Statement.hpp"
#include <string>
//#include <iostream>


ProgramState::ProgramState()
{
	for (size_t i = 0; i < NUM_REGISTERS; i++){   // NUM_REGISTERS defined in hpp file
		registers.push_back(0);
	}
	// intialize counter to start at the first line
	counter = 1;
	// initalize the 0th index of instructions vector to a dummy value
	instructions.push_back(nullptr);
	// initialize a condition register for comparison instruction, set to 3 which represents greater than 
	conditionRegister = 3;
	// set finished bool as false = running
	finished = false;
	// initialize isJump to false
	isJump = false;
}


ProgramState::~ProgramState()
{
	// deallocate the memory for the instruction objects in the vector
	for (Statement* instruction : instructions){
		delete instruction;
	}
	instructions.clear();   // not too sure if i need to clear the vector or not
}

size_t ProgramState::getCounter() const
{
	return counter;
}


void ProgramState::terminate()
{
	exit(1); 
}


bool ProgramState::done() const
{
	return finished;
}


int ProgramState::getRegister(size_t registerNum) const
{
	if (0 <= registerNum and registerNum < NUM_REGISTERS){
		return registers[registerNum];
	}
	return -1;
}



// do i need to add some kind fo set finished function? for the done function
// i added the function below
void ProgramState::setFinished(bool value){
	finished = value;
}

// SETTER FUNCTION: also need to add a setRegister function i think
void ProgramState::setRegister(size_t registerNum, int value){
	if(registerNum >= 0 and registerNum < registers.size()){  // check that register is valid
		registers[registerNum] = value;
	}
	else{
		terminate();  // am i supposed to terminate if invalid?
	}
}

// added a function to set the counter (used for jump instructions)
void ProgramState::setCounter(size_t lineNum){
	counter = lineNum;
}

// added a function to increment the counter to signal next line
void ProgramState::nextCounter(){
	counter++;  // go to next line by incrementing by 1
}

// SETTER FUNCTION: added a function set the value in the condition register
void ProgramState::setCondition(int condition){
	conditionRegister = condition;
}

// GETTER FUNCTION: added a function to get the value in the condition register for comparisons
const int & ProgramState::getCondition(){
	return conditionRegister;
}

// SETTER FUNCTION: added a function to add instruction to the vector
void ProgramState::addInstruction(Statement* instruction){
	instructions.push_back(instruction);
}

// GETTER FUNCTION: added a function to get the instruction at the given line for jump statements
Statement* ProgramState::getInstruction(size_t lineNum){
	// check that the given line number is valid
	if(lineNum >= 1 and lineNum < instructions.size()){
		return instructions[lineNum];
	}
	else{
		return nullptr;   // if line number is invalid what should i return?
	}
}

// GETTER FUNCTION: added a function return all instructions
const std::vector<Statement*> ProgramState::getInstructions(){
	return instructions;
}

void ProgramState::setJump(bool jump){
	isJump = jump;   // set jumping to either true or false
}

bool ProgramState::getJump()
{
	return isJump;
}

// uncomment the following function to  see all values in the registers printed
/*
void ProgramState::() {
    std::cout << "Registers: ";
    for (size_t i = 0; i < registers.size(); ++i) {
        char middleChar = 'a' + i;  // Calculate the middle character based on the position
        std::cout << "e" << middleChar << "x: " << registers[i] << " ";
    }
    std::cout << std::endl;
}
*/


