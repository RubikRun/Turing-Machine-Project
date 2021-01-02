#pragma once

#include "../machine/Transition.h"

#include <stdexcept>

namespace TuringMachine
{

/**
 * Parses a Move enum from a char.
 * Accepted chars are:
 *  L for Left,
 *  R for Right,
 *  S for Stay
 * 
 * @param[in] moveChar
 *  The character that we want to parse to a Move enum
 * 
 * @return the parsed Move enum
 */
Move ParseMove(char moveChar);

/**
 * Checks if a string is a valid representation of a Transition object of the form:
 *  <aSymbol>{<aState>}-><bSymbol>{<bState>}<move>
 * 
 * @param[in] str
 *  The string that we want to check
 * 
 * @return true/false - the validity of the string
 */
bool IsValidTransitionStr(
    std::string str
);

/**
 * Parses a Transition object from a string.
 * The strings are expected to be of the form:
 *  <aSymbol>{<aState>}-><bSymbol>{<bState>}<move>
 * 
 * @param[in] str
 *  The string that we want to parse to a Transition object
 * 
 * @return the parsed Transition object
 */
Transition ParseTransition(
    std::string str
);

} // TuringMachine