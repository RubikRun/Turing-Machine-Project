#pragma once

namespace TuringMachine
{

// A type for possible moves of a Turing machine's tape
enum Move
{
    Left, // Moves the tape to the left
    Right, // Moves the tape to the right
    Stay // Doesn't move the tape
};

} // namespace TuringMachine