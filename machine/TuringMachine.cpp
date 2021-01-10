#include "TuringMachine.h"

namespace
{

// The state at which the machine is at the beginning
constexpr auto INITIAL_STATE = "initial";

// The state for stopping the machine's execution
constexpr auto HALT_STATE = "halt";

} // namespace

namespace TuringMachine
{

TuringMachine::TuringMachine(
    std::vector<Transition> const& transitions)
{
    // Insert initial and halt states,
    // in case they are not present in any of the given transitions
    _states.insert(INITIAL_STATE);
    _states.insert(HALT_STATE);

    // Handle each of the given transitions
    for (Transition const& t : transitions)
    {
        // Insert the first and second state of the transition
        // to the set of all states
        _states.insert(t.aState);
        _states.insert(t.bState);

        // Add transition to the transitions map of the machine
        _transitions[std::make_tuple(t.aSymbol, t.aState)]
            = std::make_tuple(t.bSymbol, t.bState, t.move);
    }
}

std::tuple<bool, Tape> TuringMachine::ExecuteOn(
    Tape const& inputTape)
{
    /* Copy the input tape to a temporary Tape object
       that we are going to modify during execution */
    Tape tape = inputTape;

    /* The head of the machine is just a tape iterator
       that starts at the beginning of the active part of the tape */
    Tape::Iterator head = tape.GetIterator();

    std::string state = INITIAL_STATE;

    // Running the execution until we reach the halt state
    while (state != HALT_STATE)
    {
        // If there is no transition for our current symbol and state
        if (_transitions.find(std::make_tuple(head.Get(), state))
            == _transitions.end())
        {
            // then we fail the execution with a false and return the tape
            return std::make_tuple(false, tape);
        }

        // Otherwise we do what the transition says

        /* Transition's target:
            1. the character that we should set on the current tape cell
            2. the state that we should go to
            3. the move that we should do to the tape */
        std::tuple<char, std::string, Move> transTarget;
        
        // Set the character under the machine's head
        head.Set(std::get<0>(transTarget));
        // Change to the new state
        state = std::get<1>(transTarget);
        // Do the tape move
        head.DoMove(std::get<2>(transTarget));
    }

    /* When we end in a halt state the execution is successful
       so we end the execution with a true and return the tape */
    return std::make_tuple(true, tape);
}

} // namespace TuringMachine