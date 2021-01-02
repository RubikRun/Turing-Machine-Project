#include "../utils/parsingUtils.h"

#include <regex>

namespace
{

constexpr auto VALID_TRANSITION_STR_REGEX = "\\w\\{\\w+\\}->\\w\\{\\w+\\}\\w";

} // namespace

namespace TuringMachine
{

Move ParseMove(char moveChar)
{
    switch(moveChar)
    {
        case 'L': return Left;
        case 'R': return Right;
        case 'S': return Stay;
        default: throw std::invalid_argument("Invalid move");
    };
}

bool IsValidTransitionStr(
    std::string str)
{
    return std::regex_match(
        str,
        std::regex(VALID_TRANSITION_STR_REGEX)
    );
}    

Transition ParseTransition(
    std::string str)
{
    if (!IsValidTransitionStr(str))
    {
        throw std::invalid_argument("Invalid transition");
    }
    
    Transition transition;

    // The first state begins right after the first '{' in the string
    int aStateBegin = str.find('{') + 1;
    // and ends right before the first '}' in the string
    int aStateEnd = str.find('}') - 1;
    // The second state begins right after the last '{' in the string
    int bStateBegin = str.rfind('{') + 1;
    // and ends right before the last '}' in the string
    int bStateEnd = str.rfind('}') - 1;

    // The first symbol is just the character at index 0
    transition.aSymbol = str[0];
    // We have ...<bSymbol>{<bState>...
    // so the second symbol is two indecies before the second state's beginning
    transition.bSymbol = str[bStateBegin - 2];
    // The first state is the substring between its beginning and end
    transition.aState = str.substr(aStateBegin, aStateEnd - aStateBegin + 1);
    // The second state is the substring between its beginning and end
    transition.bState = str.substr(bStateBegin, bStateEnd - bStateBegin + 1);
    // The move is the last character
    transition.move = ParseMove(str.back());

    return transition;
}

} // TuringMachine