using namespace std;

#include <iostream>
#include "stack.h"

class board
{
private:
public:
    board();
    ~board();

    // pegs for tower of hanoi puzzle
    stack left;
    stack middle;
    stack right;

    // display board, with 3 pegs and disks
    void printBoard();

    // change position of a disk
    void changePeg(stack &curr, stack &target);

    // find a disk on the peg, el_t is the element number of the disk
    string find(board &b, el_t x);

    // determine if move is safe
    bool safemove(stack &curr, stack &target);
};