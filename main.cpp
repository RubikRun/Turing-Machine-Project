#include "machine/TuringMachine.h"
#include "utils/parsingUtils.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace TuringMachine;

std::string const TRANSITIONS_FILE = "examples/transitions-0";
std::string const TAPE_FILE = "examples/tape-0";

void ReadTransitions(
    std::vector<Transition>& transitions)
{
    // Open input file
    std::ifstream inputFile(TRANSITIONS_FILE);
    if (!inputFile.is_open())
    {
        throw "Error: Cannot open transitions input file.";
    }

    /* Read lines from the file.
       Each line is a transition of a Turing machine */
    std::string transitionStr;
    while (inputFile >> transitionStr)
    {
        // Add the parsed Transition object to the vector of transitions
        transitions.emplace_back(
            // Parse the transition string to a Transition object
            ParsingUtils::ParseTransition(transitionStr)
        );
    }

    inputFile.close();
}

void ReadTape(
    Tape& tape)
{
    // Open input file
    std::ifstream inputFile(TAPE_FILE);
    if (!inputFile.is_open())
    {
        throw "Error: Cannot open tape input file.";
    }

    // Read the active part of the tape from the file
    std::string tapeActivePart;
    inputFile >> tapeActivePart;

    // Create a tape with that active part written
    tape = Tape(tapeActivePart);

    inputFile.close();
}

int main()
{
    std::vector<Transition> transitions;
    // Read transitions of a Turing machine from an input file
    ReadTransitions(transitions);

    Tape tape;
    // Read tape from an input file
    ReadTape(tape);

    // Create a Turing machine with the read transitions
    TuringMachine::TuringMachine machine(transitions);

    // Execute the machine on the read tape
    std::tuple<bool, Tape> execResult =
        machine.ExecuteOn(tape);

    // Get the tape after execution
    tape = std::get<1>(execResult);

    // If the execution ended successfully
    if (std::get<0>(execResult))
    {
        std::cout << "Successful execution." << std::endl;
    }
    else
    {
        std::cout << "Failed execution." << std::endl;
    }
    std::cout << "Tape: " << tape.ToString() << std::endl;

    return 0;
}