#include "Tape.h"

#include <iostream>

namespace
{

char const BLANK_SYMBOL = '^';

} // namespace

namespace TuringMachine
{

Tape::Tape()
    // the active part should contain at least one cell
    : _activePart {BLANK_SYMBOL}
{}

Tape::Tape(std::string const& tape)
{
    // copy characters from the string to the active part
    for (char c : tape)
    {
        _activePart.push_back(c);
    }
}

Tape::Iterator::Iterator(
    Tape& tape)
{
    _tape = &tape;
    _iterator = _tape->_activePart.begin();
}

void Tape::Iterator::DoMove(Move const& move)
{
    switch (move)
    {
        case Left: Next(); break;
        case Right: Prev();
        // case Stay: nothing
    };
}

char Tape::Iterator::Get() const
{
    return *_iterator;
}

void Tape::Iterator::Set(char target)
{
    *_iterator = target;
}

void Tape::Iterator::Next()
{
    /* if the iterator is on the rightmost cell of the active part
       and we try to move it to the right
       we have to extend the active part to the right */
    if (IsRightmost())
    {
        _tape->_activePart.push_back(BLANK_SYMBOL);
    }
    _iterator++;
}

void Tape::Iterator::Prev()
{
    /* if the iterator is on the leftmost cell of the active part
       and we try to move it to the left
       we have to extend the active part to the left */
    if (IsLeftmost())
    {
        _tape->_activePart.push_front(BLANK_SYMBOL);
    }
    _iterator--;
}

bool Tape::Iterator::IsLeftmost() const
{
    return (_iterator == _tape->_activePart.begin());
}

bool Tape::Iterator::IsRightmost() const
{
    /* the weird &* is needed because the two iterators
       are of different types - iterator and reverse_iterator.
       So instead of comparing the iterators
       we compare the addresses of the elements that they are pointing to. */
    return (&*_iterator == &*_tape->_activePart.rbegin());
}

Tape::Iterator Tape::GetIterator()
{
    return Tape::Iterator(*this);
}

std::string Tape::ToString() const
{
    /* Initialize the resulting string with the size of the active part,
       so that we don't have to allocate memory more than once */
    std::string result(_activePart.size(), 0);

    int i = 0;
    for (char c : _activePart)
    {
        result[i++] = c;
    }

    return result;
}

} // namespace TuringMachine