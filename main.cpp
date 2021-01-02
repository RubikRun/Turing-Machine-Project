#include "utils/parsingUtils.h"

#include <iostream>

using namespace TuringMachine;

int main()
{
    std::string transitionStr;
    std::cin >> transitionStr;

    Transition transition = ParseTransition(
        transitionStr
    );

    std::cout << "First symbol: " << transition.aSymbol << std::endl;
    std::cout << "Second symbol: " << transition.bSymbol << std::endl;
    std::cout << "First state: " << transition.aState << std::endl;
    std::cout << "Second state: " << transition.bState << std::endl;
    std::cout << "Move: " << transition.move << std::endl;

    return 0;
}