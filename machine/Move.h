#pragma once

namespace TuringMachine
{

// A type for possible moves of a Turing machine's tape
enum Move
{
    Left, // Moves the tape to the left (or the head to the right)
    Right, // Moves the tape to the right (or the head to the left)
    Stay // Doesn't move the tape
};

} // namespace TuringMachine