#pragma once

#include "Move.h"

#include <string>

namespace TuringMachine
{

/**
 * A struct for a transition in a Turing machine.
 * Transition from a state to a state, from a symbol to a symbol,
 * and a tape move to execute after the transition
 */
struct Transition
{
    // This symbol should be the current tape symbol for the transition to happen
    char aSymbol;

    // The transition will change the current symbol to this symbol
    char bSymbol;

    // This state should be the current state of the machine for the transition to happen
    std::string aState;

    // The transition will change the current state of the machine to this state
    std::string bState;

    // This tape move will be applied to the tape after the transition
    Move move;
};

} // TuringMachine