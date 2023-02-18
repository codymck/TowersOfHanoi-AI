#include <iostream>
#include "board.h"

using namespace std;

// constructor for board
// sets up initial state of puzzle with all 3 disks on left peg
board::board()
{
    board::left.push(3);
    board::left.push(2);
    board::left.push(1);
}

board::~board()
{
}

// display board with all pegs and disks
void board::printBoard()
{
    cout << "-----------------------" << endl;
    if (board::left.isEmpty() && board::middle.isEmpty() && board::right.isEmpty())
        cout << "[ empty ]" << endl;
    else
    {
        for (int i = 2; i >= 0; i--)
        {
            cout << " | ";
            if (board::left.returnElement(i) > 3 || board::left.returnElement(i) < 1)
                cout << 0;
            else
                cout << board::left.returnElement(i);
            cout << " |   ";

            cout << "| ";
            if (board::middle.returnElement(i) > 3 || board::middle.returnElement(i) < 1)
                cout << 0;
            else
                cout << board::middle.returnElement(i);
            cout << " |   ";

            cout << "| ";
            if (board::right.returnElement(i) > 3 || board::right.returnElement(i) < 1)
                cout << 0;
            else
                cout << board::right.returnElement(i);
            cout << " |   ";

            cout << endl;
        }
    }
    cout << "-----------------------" << endl;
}

// change peg based on target
// does not work for illegal states
// PARAMS: takes current stack and target stack
void board::changePeg(stack &curr, stack &target)
{
    el_t c;
    el_t t;

    if (!curr.isEmpty())
    {
        curr.topElem(c);
        if (!target.isEmpty())
        {
            target.topElem(t);
            // check if move is legal
            if (t > c)
            {
                curr.pop(c);
                target.push(c);
            }
        }
        else
        {
            curr.pop(c);
            target.push(c);
        }
    }
}

// PURPOSE: check if the move is legal
// PARAMS: curr is the current stack, target is where we want to move the disk
bool board::safemove(stack &curr, stack &target)
{
    el_t c;
    el_t t;

    if (!curr.isEmpty())
    {
        curr.topElem(c);
        if (!target.isEmpty())
        {
            target.topElem(t);
            if (t > c)
            {
                return true;
            }
        }
        else
        {
            return true;
        }
    }
    return false;
}

// PURPOSE: find which peg on a board a disk is
// PARAMS: b is the puzzle board, el_t x is the # of disk (1-3) being looked for
string board::find(board &b, el_t x)
{
    for (int i = 0; i < 3; i++)
    {
        if (x == b.left.returnElement(i))
            return "left";

        if (x == b.middle.returnElement(i))
            return "middle";

        if (x == b.right.returnElement(i))
            return "right";
    }
    return "x";
}
