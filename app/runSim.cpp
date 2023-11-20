#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "runSim.hpp"
#include "ProgramState.hpp"

#include "Statement.hpp"
#include "MoveInstruction.hpp"
#include "AddInstruction.hpp"
#include "SubtractionInstruction.hpp"
#include "ImulInstruction.hpp"   // included this line
#include "IncInstruction.hpp"   // included this line
#include "CmpInstruction.hpp"
#include "JmpInstruction.hpp"
#include "JLInstruction.hpp"
#include "JEInstruction.hpp"
#include "EndInstruction.hpp"


// Simulates the given program.  The starting program state
// will be provided to you via the second parameter. 
// It is expected that you use this one, not a newly declared
// one, in running your program.
void runSimulator(std::istream &in, ProgramState * ps)
{
    // You will want to modify some of this.
    // You do not need to be very well versed in how std::stringstream works
    // You should be able to figure out how it works based on 
    // your knowledge of aspects like std::cin and reading the existing
    // code.  That is a skill worth developing!

    std::string line, word;
    std::string token1, token2;
    std::stringstream ss;


    while(  getline(in, line) )
    {
        ss.clear();
        ss << line;
        while( ss >> word )
        {
            if(word == "MOV"){
                ss >> token1 >> token2;
                ps->addInstruction(new MoveInstruction(token1, token2));
            }
            else if (word == "ADD"){
                ss >> token1 >> token2;
                ps->addInstruction(new AddInstruction(token2, token1));
            }
            else if (word == "SUB"){
                ss >> token1 >> token2;
                ps->addInstruction(new SubtractionInstruction(token2, token1));
            }
            else if(word == "IMUL"){
                ss >> token1 >> token2;
                ps->addInstruction(new ImulInstruction(token2, token1));
            }
            else if (word == "INC"){
                ss >> token1;
                ps->addInstruction(new IncInstruction(token1));
            }
            else if(word == "CMP"){
                ss >> token1 >> token2;
                ps->addInstruction(new CmpInstruction(token1, token2));
            }
            else if ( word == "JMP"){
                ss >> token1;
                ps->addInstruction(new JmpInstruction(token1));
            }
            else if(word == "JE"){
                ss >> token1;
                ps->addInstruction(new JEInstruction(token1));
            }
            else if (word == "JL"){
                ss >> token1;
                ps->addInstruction(new JLInstruction(token1));
            }
            else if (word == "END"){
                ps->addInstruction(new EndInstruction());
            }
        }
    }

    size_t lineNum = ps->getCounter();
    while (lineNum <= ps->getInstructions().size()){
        Statement* instruction = ps->getInstruction(lineNum);
        instruction->execute(ps);
        // std::cout << "executed: " << lineNum << std::endl;  // uncomment this to see line number executed
        if (ps->done()){
            break;
        }
        else{
            // update lineNum based on isJump or just move to the next line
            lineNum = ps->getCounter();
        }
    }
    // ps->();  // uncomment this line to print out register values

}


