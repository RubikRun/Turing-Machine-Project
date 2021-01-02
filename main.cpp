#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <fstream>

int const TAPE_LEN = 100;
std::string const HALT_STATE = "halt";
std::string const INITIAL_STATE = "initial";
char const BLANK_SYMBOL = '^';

struct SymbolStatePair
{
    char symbol;
    std::string state;

    bool operator<(SymbolStatePair const& other) const
    {
        if (this->symbol != other.symbol)
        {
            return (this->symbol < other.symbol);
        }
        return this->state < other.state;
    }
};

struct SymbolStateMoveTuple
{
    char symbol;
    std::string state;
    char move;
};

struct Transition
{
    char aSymbol, bSymbol;
    std::string aState, bState;
    char move;
};

class TuringMachine
{

  public:

    TuringMachine(
        std::vector<Transition> const& transitions
    );

    std::string ExecuteOn(
        std::string const& tape
    );

  private:

    std::set<std::string> _states;
    std::map<SymbolStatePair, SymbolStateMoveTuple> _transitions;

    std::string _tape;
    int _head;

    std::string _state;
};

TuringMachine::TuringMachine(
    std::vector<Transition> const& transitions)
{
    _states.insert(HALT_STATE);

    for (Transition const& t : transitions)
    {
        _states.insert(t.aState);
        _states.insert(t.bState);

        _transitions[{t.aSymbol, t.aState}] = {
            t.bSymbol,
            t.bState,
            t.move
        };
    }
}

std::string TuringMachine::ExecuteOn(
    std::string const& tape)
{
    _tape = tape;
    _head = 0;

    _state = INITIAL_STATE;

    while (_state != HALT_STATE)
    {
        if (_transitions.find({_tape[_head], _state})
            == _transitions.end())
        {
            std::cout << "Error: Failed execution." << std::endl;
            return _tape;
        }

        SymbolStateMoveTuple t = _transitions[{_tape[_head], _state}];

        _tape[_head] = t.symbol;
        _state = t.state;
        if (t.move == 'L')
        {
            _head++;
        }
        else if (t.move == 'R')
        {
            _head--;
        }
    }

    std::cout << "Success: Execution ended in halt state." << std::endl;
    return _tape;
}

Transition ParseTransition(
    std::string const& str)
{
    int aOpen = 1;
    int aClose = str.find('}');

    int bOpen = str.rfind('{');
    int bClose = str.length() - 2;

    Transition t;

    t.aSymbol = str[0];
    t.aState = str.substr(aOpen + 1, aClose - aOpen - 1);
    t.bSymbol = str[bOpen - 1];
    t.bState = str.substr(bOpen + 1, bClose - bOpen - 1);
    t.move = str.back();

    return t;
}

void ReadTransitionsFromFile(
    std::vector<Transition>& transitions,
    std::string const& filename)
{
    std::ifstream f(filename);
    if (!f.is_open())
    {
        throw "Error: Cannot open file.";
    }

    std::string line;
    while (f >> line)
    {
        transitions.push_back(
            ParseTransition(line)
        );
    }

    f.close();
}

int main()
{
    std::vector<Transition> transitions;
    ReadTransitionsFromFile(transitions, "example-0");

    TuringMachine machine(transitions);

    std::string tape = "01101^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
    std::string afterTape = machine.ExecuteOn(tape);
    std::cout << "Tape after execution: " << afterTape << std::endl;

    return 0;
}