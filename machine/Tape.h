#pragma once

#include <list>
#include <string>

namespace TuringMachine
{

/**
 * A class representing a tape for a Turing machine.
 * Such tape is infinite and we have finite memory
 * so we will keep in memory only the active part of the tape.
 * "Active part" meaning the part that has been iterated.
 * That active is extended to the right or to the left when needed.
 */
class Tape
{
  public:

    /**
     * Creates a tape with blank symbols only
     */
    Tape();

    /**
     * Creates a tape with the given string written in the active part
     * 
     * @param[in] tape
     *  The string that will be written to the active part
     */
    Tape(std::string const&);

    /**
     * A class for tape iterator.
     * An object needed to iterate through the tape,
     * read and write to cells,
     * and the tape will extend itself
     * when the iterator goes beyond the active part.
     */
    class Iterator
    {

      public:

        /**
         * Creates an iterator for the given tape.
         * Tape iterators initially point to the first cell
         * of the active part of the tape.
         * 
         * @param[in] tape
         *  The tape which the iterator will iterate
         */
        Iterator(Tape&);

        /**
         * Moves the iterator to the next cell of the tape
         */
        void Next();

        /**
         * Moves the iterator to the previous cell of the tape
         */
        void Prev();

        /**
         * Returns the character in the current cell of the tape
         * 
         * @return current character
         */
        char Get() const;

        /**
         * Sets the current cell to the given character
         * 
         * @param[in] target
         *  The value that we want to set to the current cell
         */
        void Set(char);

      private:

        /**
         * Checks if the iterator points to the first cell of the active part.
         * 
         * @return true for leftmost, false for not leftmost
         */
        bool IsLeftmost() const;

        /**
         * Checks if the iterator points to the last cell of the active part.
         * 
         * @return true for rightmost, false for not rightmost
         */
        bool IsRightmost() const;

        // Pointer to the tape that the iterator iterates
        Tape* _tape;

        // Iterator to the active part of the tape
        std::list<char>::iterator _iterator;
    };

    /**
     * Returns an iterator for the tape.
     * 
     * @return the iterator
     */
    Iterator GetIterator();

    /**
     * Returns the active part of the tape as a string
     * 
     * @return string - the active part
     */
    std::string ToString() const;

  private:

    // The active part of the tape
    std::list<char> _activePart;
};

} // namespace TuringMachine