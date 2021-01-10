#pragma once

#include "Transition.h"
#include "Tape.h"

#include <vector>
#include <tuple>
#include <set>
#include <map>

namespace TuringMachine
{

class TuringMachine
{

  public:

    /**
     * Constructs a Turing machine from a vector of transitions
     * 
     * @param[in] transitions
     *  The vector of transitions.
     */
    TuringMachine(
        std::vector<Transition> const& transitions
    );

    /**
     * Executes the Turing machine on the given tape
     * 
     * @param[in] tape
     *  The tape on which to execute the Turing machine
     * 
     * @return 
     * 1. bool - tells if the execution ended successfully
     * 2. Tape - the tape after the machine's execution.
     */
    std::tuple<
        bool,
        Tape
    > ExecuteOn(Tape const&);

  private:

    // The set of states of the machine
    std::set<std::string> _states;

    // The transitions of the machine
    // as a map from a symbol and a state to a symbol, a state, and a move
    std::map<
        std::tuple<char, std::string>,
        std::tuple<char, std::string, Move>
    > _transitions;
};

} // namespace TuringMachine