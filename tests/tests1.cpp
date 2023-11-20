#include "catch_amalgamated.hpp"
#include "ProgramState.hpp"
#include "Statement.hpp"
#include "MoveInstruction.hpp"
#include "AddInstruction.hpp"
#include "SubtractionInstruction.hpp"
#include "CmpInstruction.hpp"
#include "ImulInstruction.hpp"
#include "JmpInstruction.hpp"
#include "JLInstruction.hpp"
#include "JEInstruction.hpp"
#include "EndInstruction.hpp"
#include "IncInstruction.hpp"
#include "runSim.hpp"
#include <fstream>
#include <string>


// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.
// However, be aware that if ANY test marked "Required" fails, 
// your score for the portion will be zero, regardless of other considerations.


namespace{


/*
This LOOKS LIKE a lot of test cases!  
Remember you DO NOT need to pass every case the first time you build.
build and run tests for the starting code, and look through the case(s) that fail.
Read the description in the test files.

Decide which one you think will be the easiest to achieve:  what is the smallest amount of programming you can do to pass one more test case?  Write that code and find out.  If you now pass it, repeat -- what is the smallest amount of programming you can do to pass one more test case (without causing any previously-passing test cases to now fail).

Believe it or not, this will make programming a lot easier.  In future projects, you might want to write a lot of different test cases yourself at the beginning, based on reading the skeleton code and the project requirements, and then try the above approach.  You might find yourself turning what feels like a very large and intimidating programming assignment into a series of small, very manageable mini-projects. 

*/




TEST_CASE("StoreAConstant", "[RequiredMoveOperations]")
{
        ProgramState ps;
        MoveInstruction m1{"eax", "15"};
        m1.execute(&ps);
        REQUIRE(ps.getRegister(0) == 15);
}

TEST_CASE("MoveAConstant", "[RequiredMoveOperations]")
{
        ProgramState ps;
        MoveInstruction m1{"eax", "15"};
        m1.execute(&ps);
        MoveInstruction m2{"ebx", "eax"};
        m2.execute(&ps);
        REQUIRE(ps.getRegister(0) == 15);
        REQUIRE(ps.getRegister(1) == 15);
}

TEST_CASE("MoveUsesPolymorphism", "[RequiredMoveOperations]")
{
        ProgramState ps;
        Statement * m1 = new MoveInstruction{"eax", "15"};
        m1->execute(&ps);
        Statement * m2 = new MoveInstruction{"ebx", "eax"};
        m2->execute(&ps);
        REQUIRE(ps.getRegister(0) == 15);
        REQUIRE(ps.getRegister(1) == 15);
        delete m1;   // added these two lines
        delete m2;

}

TEST_CASE("AddAConstant", "[RequiredArithmeticOperations]")
{
        ProgramState ps;
        MoveInstruction m1("eax", "15");
        m1.execute(&ps);
        REQUIRE(ps.getRegister(0) == 15);

        AddInstruction ai1("eax", "20");
        ai1.execute(&ps);
        REQUIRE(ps.getRegister(0) == 35);
}



TEST_CASE("AddARegister", "[RequiredArithmeticOperations]")
{
        ProgramState ps;
        MoveInstruction m1("eax", "15");
        m1.execute(&ps);
        REQUIRE(ps.getRegister(0) == 15);

        MoveInstruction m2("ebx", "20");
        m2.execute(&ps);
        REQUIRE(ps.getRegister(1) == 20);

        AddInstruction ai1("eax", "ebx");
        ai1.execute(&ps);
        REQUIRE(ps.getRegister(0) == 35);
}

// This test case is NOT REQUIRED to be eligible for grading.
// Remember that does not mean that this functionality won't
// be graded;  rather, it just means this test does not affect
// your eligibility to be graded.
// This is provided to demonstrate functionality of the subtract operation.
TEST_CASE("Subtraction", "[FYI]")
{
        ProgramState ps;
        MoveInstruction m1{"eax", "15"};
        m1.execute(&ps);
        REQUIRE(ps.getRegister(0) == 15);

        MoveInstruction m2{"ebx", "20"};
        m2.execute(&ps);
        REQUIRE(ps.getRegister(1) == 20);

        SubtractionInstruction si1{"eax", "ebx"};
        si1.execute(&ps);
        REQUIRE(ps.getRegister(0) == -5);

}



// [RequiredAllOperations] does an unconditional jump and the program counter changes appropriately. 

TEST_CASE("UnconditionalJump", "[RequiredAllOperations]")
{
        ProgramState ps;
        JmpInstruction js{"5"};
        js.execute(&ps);
        REQUIRE(ps.getCounter() == 5);
}



// "Full Programs" test cases use the full set of available operations,
// although some individual programs may only use a subset.

TEST_CASE("StoreAConstantAsAProgram", "[RequiredFullPrograms]")
{
        std::ifstream in{"prog1.txt"};
        ProgramState ps;
        runSimulator(in, &ps);
        REQUIRE(ps.getRegister(0) == 15);
        REQUIRE(ps.getRegister(1) == 20);
}

TEST_CASE("MoveAConstantAsAProgram", "[RequiredFullPrograms]")
{
        std::ifstream in{"prog2.txt"};
        ProgramState ps;
        runSimulator(in, &ps);
        REQUIRE(ps.getRegister(0) == 15);
        REQUIRE(ps.getRegister(1) == 15);
}


// uncomment the below personal tests when needed
// TODO: JMP test cases
TEST_CASE("UnconditionalJumping", "[PersonalTests]") {
        ProgramState ps;
        JmpInstruction js{"5"};
        js.execute(&ps);
        REQUIRE(ps.getCounter() == 5);
}

// TODO: JL test cases
TEST_CASE("ConditionalJumpLess", "[PersonalTests]") {
        ProgramState ps;
        ps.setCondition(1);
        ps.setRegister(0, 10); // Set register 1 to 10
        JLInstruction jl{"5"};
        jl.execute(&ps);
        REQUIRE(ps.getCounter() == 5); // Should jump because register 1 < 15
}

TEST_CASE("ConditionalJumpGreater", "[PersonalTests]") {
        ProgramState ps;
        ps.setCondition(3);
        ps.setRegister(0, 20); // Set register 1 to 20
        JLInstruction jl{"5"};
        jl.execute(&ps);
        REQUIRE(ps.getCounter() == 2); // Should not jump because register 1 > 15
}

// TODO: JE test cases
TEST_CASE("ConditionalJumpEqual", "[PersonalTests]") {
        ProgramState ps;
        ps.setCondition(2);
        ps.setRegister(0, 15); // Set register 1 to 15
        JEInstruction je{"5"};
        je.execute(&ps);
        REQUIRE(ps.getCounter() == 5); // Should jump because register 1 = 15
}

// TODO: ADD test cases
TEST_CASE("AddTwoRegisters", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(0, 5);
        ps.setRegister(1, 10);
        AddInstruction addInstruction("eax", "ebx");
        addInstruction.execute(&ps);
        REQUIRE(ps.getRegister(0) == 15); // eax should contain 15 after adding ebx to it
        REQUIRE(ps.getRegister(1) == 10);
}

TEST_CASE("AddRegisterAndConstant", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(0, 5);
        AddInstruction addInstruction("eax", "10");
        addInstruction.execute(&ps);
        REQUIRE(ps.getRegister(0) == 15); // eax should contain 15 after adding 10 to it
}

TEST_CASE("AddNegativeConstant", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(0, 1);
        AddInstruction addInstruction("eax", "2147483647"); // Attempt to add a negative constant
        addInstruction.execute(&ps);
        REQUIRE(ps.getRegister(0) == -2147483648); // eax should contain -5 after adding -10 to it
}

TEST_CASE("AddPosNegativeConstant", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(0, -2147483648);
        AddInstruction addInstruction("eax", "2147483647"); // Attempt to add a negative constant
        addInstruction.execute(&ps);
        REQUIRE(ps.getRegister(0) == -1); // eax should contain -5 after adding -10 to it
}

TEST_CASE("AddzeroNegativeConstant", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(0, -2147483648);
        AddInstruction addInstruction("eax", "0"); // Attempt to add a negative constant
        addInstruction.execute(&ps);
        REQUIRE(ps.getRegister(0) == -2147483648); // eax should contain -5 after adding -10 to it
}

TEST_CASE("AddToAllRegister", "[PersonalTests]") {
        ProgramState ps;
        std::string regName = "eax";
        for (size_t i = 0; i < 16; i++){
                char mid = 'a' + i;
                //std::string conv = mid;
                // std::string regName = 'e' + conv + 'x';
                regName[1] = mid;
                ps.setRegister(i, -1);
                AddInstruction ad(regName, "-2147483648");
                ad.execute(&ps);
                REQUIRE(ps.getRegister(i) == 2147483647);
        }
        ps.printRegisters();
}

// TODO: SUB test cases
TEST_CASE("SubtractTwoRegisters", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(0, 15);
        ps.setRegister(1, 7);
        SubtractionInstruction subInstruction("eax", "ebx");
        subInstruction.execute(&ps);
        REQUIRE(ps.getRegister(0) == 8); // eax should contain 8 after subtracting ebx from it
        REQUIRE(ps.getRegister(1) == 7);
}

TEST_CASE("SubtractRegisterAndConstant", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(0, 0);
        SubtractionInstruction subInstruction("eax", "-2147483648");
        subInstruction.execute(&ps);
        REQUIRE(ps.getRegister(0) == -2147483648); // eax should contain 10 after subtracting 10 from it
}

TEST_CASE("SubtractNegativeConstant", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(0, 10);
        SubtractionInstruction subInstruction("eax", "-5"); // Attempt to subtract a negative constant
        subInstruction.execute(&ps);
        REQUIRE(ps.getRegister(0) == 15); // eax should contain 15 after subtracting -5 from it
}

TEST_CASE("SubtractTwolargeRegisters", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(0, 2147483647);
        ps.setRegister(1, -2147483648);
        SubtractionInstruction subInstruction("ebx", "eax");
        subInstruction.execute(&ps);
        REQUIRE(ps.getRegister(1) == 1); // eax should contain 8 after subtracting ebx from it
}

TEST_CASE("SubtractzerolargeRegisters", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(0, 0);
        ps.setRegister(1, -2147483648);
        SubtractionInstruction subInstruction("ebx", "eax");
        subInstruction.execute(&ps);
        REQUIRE(ps.getRegister(1) == -2147483648); // eax should contain 8 after subtracting ebx from it
}


// TODO: IMUL test cases
TEST_CASE("MultiplyTwoRegisters", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(0, -2147483648);
        ps.setRegister(1, 4);
        ImulInstruction im("eax", "ebx");
        im.execute(&ps);
        REQUIRE(ps.getRegister(0) == 0); // R1 should contain 15 after multiplying R1 and R2
        REQUIRE(ps.getRegister(1) == 4);
}

TEST_CASE("MultiplyRegisterAndConstant", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(0, 7);
        ImulInstruction imulInstruction("eax", "10");
        imulInstruction.execute(&ps);
        REQUIRE(ps.getRegister(0) == 70); // R1 should contain 70 after multiplying it by 10
}

TEST_CASE("MultiplyRegisterContainingZero", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(0, 10);
        ImulInstruction imulInstruction("eax", "edx"); // Attempt to multiply with register containing 0
        imulInstruction.execute(&ps);
        REQUIRE(ps.getRegister(0) == 0); // R1 should remain unchanged as the source register is invalid
}

TEST_CASE("MultiplyNegativeConstant", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(0, 8);
        ImulInstruction imulInstruction("eax", "-2"); // Attempt to multiply by a negative constant
        imulInstruction.execute(&ps);
        REQUIRE(ps.getRegister(0) == -16); // R1 should contain -16 after multiplying it by -2
}


// TODO: CMP test cases
TEST_CASE("CompareConstantsGreaterThan", "[PersonalTests]") {
        ProgramState ps;
        CmpInstruction cmpInstruction("2147483647", "-2147483648");
        cmpInstruction.execute(&ps);
        REQUIRE(ps.getCondition() == 3); // 10 > 5
}

TEST_CASE("CompareConstantsLessThan", "[PersonalTests]") {
        ProgramState ps;
        CmpInstruction cmpInstruction("-2147483648", "2147483647");
        cmpInstruction.execute(&ps);
        REQUIRE(ps.getCondition() == 1); // -3 < 2
}

TEST_CASE("CompareConstantsEqualTo", "[PersonalTests]") {
        ProgramState ps;
        CmpInstruction cmpInstruction("-2147483648", "-2147483648");
        cmpInstruction.execute(&ps);
        REQUIRE(ps.getCondition() == 2); // -5 = -5
}

TEST_CASE("CompareRegistersGreaterThan", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(0, 2147483647);
        ps.setRegister(1, -1);

        CmpInstruction cmpInstruction("eax", "ebx");
        cmpInstruction.execute(&ps);
        REQUIRE(ps.getCondition() == 3); // 8 > -6
}

TEST_CASE("CompareRegistersLessThan", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(0, -1);
        ps.setRegister(1, 2147483647);

        CmpInstruction cmpInstruction("eax", "ebx");
        cmpInstruction.execute(&ps);
        REQUIRE(ps.getCondition() == 1); // -2 < -6
}

TEST_CASE("CompareRegistersEqualTo", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(0, 2147483647);
        ps.setRegister(1, 2147483647);

        CmpInstruction cmpInstruction("eax", "ebx");
        cmpInstruction.execute(&ps);
        REQUIRE(ps.getCondition() == 2); // 3 = 3
}



// TODO: INC test cases

TEST_CASE("IncrementRegister", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(0, -2147483648);
        IncInstruction incInstruction("eax");
        incInstruction.execute(&ps);
        REQUIRE(ps.getRegister(0) == -2147483647); // R1 should be incremented to 6
}

TEST_CASE("IncrementNegativeRegister", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(0, -3);
        IncInstruction incInstruction("eax");
        incInstruction.execute(&ps);
        REQUIRE(ps.getRegister(0) == -2); // R1 should be incremented to -2
}

TEST_CASE("IncrementZeroRegister", "[PersonalTests]") {
        ProgramState ps;
        // register eax should be 0 by default
        IncInstruction incInstruction("eax");
        incInstruction.execute(&ps);
        REQUIRE(ps.getRegister(0) == 1); // R1 should be incremented to 1
}

// TODO: MOVE test cases

TEST_CASE("MoveConstantToRegister", "[PersonalTests]") {
        ProgramState ps;
        MoveInstruction moveInstruction("eax", "15");
        moveInstruction.execute(&ps);
        REQUIRE(ps.getRegister(0) == 15); // R1 should contain 15 after moving a constant
}

TEST_CASE("MoveRegisterToRegister", "[PersonalTests]") {
        ProgramState ps;
        ps.setRegister(1, 10);
        MoveInstruction moveInstruction("eax", "ebx");
        moveInstruction.execute(&ps);
        REQUIRE(ps.getRegister(0) == 10); // R1 should contain the value of R2 (10) after moving
}

TEST_CASE("MoveNegativeValueToRegister", "[PersonalTests]") {
        ProgramState ps;
        MoveInstruction moveInstruction("eax", "-5");
        moveInstruction.execute(&ps);
        REQUIRE(ps.getRegister(0) == -5); // R1 should contain -5 after moving a negative constant
}

TEST_CASE("MoveToAllRegister", "[PersonalTests]") {
        ProgramState ps;
        std::string regName = "eax";
        for (size_t i = 0; i < 16; i++){
                char mid = 'a' + i;
                //std::string conv = mid;
                // std::string regName = 'e' + conv + 'x';
                regName[1] = mid;
                MoveInstruction moveInstruction(regName, "-2147483648");
                moveInstruction.execute(&ps);
                SubtractionInstruction inc(regName, "1");
                inc.execute(&ps);
                REQUIRE(ps.getRegister(i) == 2147483647);
        }
        ps.printRegisters();
}


// TODO: END test cases
TEST_CASE("EndInstructionTerminatesProgram", "[PersonalTests]") {
        ProgramState ps;
        EndInstruction endInstruction;
        endInstruction.execute(&ps);
        REQUIRE(ps.done()); // Program should be terminated after encountering EndInstruction
}

TEST_CASE("EndInstructionDoesNotIncrementCounter", "[PersonalTests]") {
        ProgramState ps;
        //size_t initialCounter = ps.getCounter();
        EndInstruction endInstruction;
        endInstruction.execute(&ps);
        REQUIRE(ps.getCounter() == 1); // Counter should not be incremented after EndInstruction
}

                        
} // end namespace

