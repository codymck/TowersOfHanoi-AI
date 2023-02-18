#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h> /* to use exit */
#include "board.h"

using namespace std;

// Tower of Hanoi Solved using A* Search Algorithm
//--------------------------------------------------
// Author: Cody McKinney
// Tested using g++
//--------------------------------------------------

class state
{
public:
    board current;
    board camefrom;
    int g;
    int h;
    int f;
};

// Major data structures:
vector<state> frontier;  // Frontier nodes - will pick one of these to expand
vector<state> beenThere; // already expanded nodes

// ========== Utility Functions ===================

// add x to the beenthere
void addtoBeenThere(state x)
{
    beenThere.push_back(x);
}

// add x to the frontier
void addtoFrontier(state x)
{
    frontier.push_back(x);
}

// determine if boards are the same
bool isSame(board &lhs, board &rhs)
{
    for (int i = 0; i < 3; i++)
    {
        if (lhs.left.returnElement(i) != rhs.left.returnElement(i))
        {
            return false;
        }
        if (lhs.middle.returnElement(i) != rhs.middle.returnElement(i))
        {
            return false;
        }
        if (lhs.right.returnElement(i) != rhs.right.returnElement(i))
        {
            return false;
        }
    }
    return true;
}

// to remove state x from the frontier when it has been expanded
void removefromFrontier(state x)
{
    vector<state> newfrontier;
    for (int k = 0; k < frontier.size(); k++)
        if (!isSame(frontier[k].current, x.current))
            newfrontier.push_back(frontier[k]);

    frontier = newfrontier;
}

// Trace and display the solution path from goal to initial.
void tracePath(state goal)
{
    state parent;
    board temp;

    if (isSame(goal.current, temp)) // if goal items are the starting state return
    {
        return;
    }
    else // trace parent path
    {
        for (int i = 0; i < beenThere.size(); i++)
        {

            if (isSame(goal.camefrom, beenThere[i].current)) // if goal came from a state in beenThere
            {
                parent = beenThere[i]; // assign parent to beenThere state at i
                cout << "came from\n";
                beenThere[i].current.printBoard(); // print beenThere items
            }
        }
        tracePath(parent); // trace path from parent
    }
} // end of tracePath

//======= For Generating a new state to add to Frontier  =============

// Check to see if next's items is already in frontier and return true or false.
//   If it is already in frontier,
//   and if the next's f is better,
//   update the frontier node to next.  (called from generate)
bool inFrontier(state next)
{
    // the same frontier node with next if f is better.
    // Please cout a message in that case.
    // Return true or false.
    for (int i = 0; i < frontier.size(); i++)
    {
        if (isSame(next.current, frontier[i].current))
        {
            cout << " already in frontier" << endl;
            if (next.f < frontier[i].f)
            {
                frontier[i] = next;
            }
            else
            {
                cout << " f not better" << endl;
            }
            return true;
        }
    }
    cout << " not in frontier" << endl;
    return false;
} // end of inFrontier

// make Goal board for comparison
board makeGoal()
{
    el_t x;

    board goal;
    goal.left.pop(x);
    goal.left.pop(x);
    goal.left.pop(x);

    goal.right.push(3);
    goal.right.push(2);
    goal.right.push(1);

    return goal;
}

// Try to add next to frontier but stop if goal is reached (called from generateAll)
void generate(state next)
{
    board goal = makeGoal();

    cout << "Trying to add: " << endl;
    next.current.printBoard();

    if (isSame(next.current, goal)) // the goal is reached
    {
        cout << "\n>>Reached<< " << endl;
        next.current.printBoard();
        tracePath(next); // display the solution path
        exit(0);
    } // done
    bool add = true;

    // if been there before, do not add to frontier.
    for (int i = 0; i < beenThere.size(); i++)
    {
        // if current board has been in frontier, do not add
        if (!beenThere.empty())
        {
            if (isSame(next.current, beenThere[i].current))
            {
                cout << " been there already" << endl;
                add = false;
            }
        }
    }

    int h = 0;

    // count how many disks are on the left and middle pegs for heuristic evaluation
    for (int i = 0; i < 3; i++)
    {
        if ((next.current.left.returnElement(i) > 0 && next.current.left.returnElement(i) < 4) && !next.current.left.isEmpty())
        {
            h++;
        }
        if ((next.current.middle.returnElement(i) > 0 && next.current.middle.returnElement(i) < 4) && !next.current.middle.isEmpty())
        {
            h++;
        }
    }
    next.f = next.g + h;
    next.h = h;

    if (add)
        if (!inFrontier(next))
            addtoFrontier(next); // add next to Frontier

} // end of generate

// Generate all new states from current (called from main)
void generateAll(state old)
{
    state next; // a generated one

    // each next will be modified from current for ease
    old.g = old.g + 1; // to update g to be used for next
    // storing the parent so that we can produce the solution path
    old.camefrom = old.current;
    next = old;

    // ONE DISK
    // One is the smallest number and can go anywhere
    // One is on the left peg, shift to right peg
    if (old.current.find(old.current, 1) == "left")
    {
        if (next.current.safemove(next.current.left, next.current.right))
        {
            next.current.changePeg(next.current.left, next.current.right);
            generate(next);
        }
    }
    next = old;

    // One is on the left peg, shift to middle peg
    if (old.current.find(old.current, 1) == "left")
    {
        if (next.current.safemove(next.current.left, next.current.middle))
        {
            next.current.changePeg(next.current.left, next.current.middle);
            generate(next);
        }
    }
    next = old;

    // One is on the middle peg, shift to right peg
    if (old.current.find(old.current, 1) == "middle")
    {
        if (next.current.safemove(next.current.middle, next.current.right))
        {
            next.current.changePeg(next.current.middle, next.current.right);
            generate(next);
        }
    }
    next = old;

    // One is on the middle peg, shift to left peg
    if (old.current.find(old.current, 1) == "middle")
    {
        if (next.current.safemove(next.current.middle, next.current.left))
        {
            next.current.changePeg(next.current.middle, next.current.left);
            generate(next);
        }
    }
    next = old;

    // One is on the right pet, move to the left peg
    if (old.current.find(old.current, 1) == "right")
    {
        if (next.current.safemove(next.current.right, next.current.left))
        {
            next.current.changePeg(next.current.right, next.current.left);
            generate(next);
        }
    }
    next = old;

    // One is on the right peg, move to the middle peg
    if (old.current.find(old.current, 1) == "right")
    {
        if (next.current.safemove(next.current.right, next.current.middle))
        {
            next.current.changePeg(next.current.right, next.current.middle);
            generate(next);
        }
    }
    next = old;
    // END OF DISK ONE

    // TWO DISK
    // Two is on the left peg, shift to middle peg
    if (old.current.find(old.current, 2) == "left" && old.current.find(old.current, 1) != "left")
    {
        if (next.current.safemove(next.current.left, next.current.middle))
        {
            next.current.changePeg(next.current.left, next.current.middle);
            generate(next);
        }
    }
    next = old;

    // Two is on the left peg, shift to right peg
    if (old.current.find(old.current, 2) == "left" && old.current.find(old.current, 1) != "left")
    {
        if (next.current.safemove(next.current.left, next.current.right))
        {
            next.current.changePeg(next.current.left, next.current.right);
            generate(next);
        }
    }
    next = old;

    // Two is on the middle peg, shift to right peg
    if (old.current.find(old.current, 2) == "middle" && old.current.find(old.current, 1) != "middle")
    {
        if (next.current.safemove(next.current.middle, next.current.right))
        {
            next.current.changePeg(next.current.middle, next.current.right);
            generate(next);
        }
    }
    next = old;

    // Two is on the middle peg, shift to left peg
    if (old.current.find(old.current, 2) == "middle" && old.current.find(old.current, 1) != "middle")
    {
        if (next.current.safemove(next.current.middle, next.current.left))
        {
            next.current.changePeg(next.current.middle, next.current.left);
            generate(next);
        }
    }
    next = old;

    // Two is on the right peg, shift to left peg
    if (old.current.find(old.current, 2) == "right" && old.current.find(old.current, 1) != "right")
    {
        if (next.current.safemove(next.current.right, next.current.left))
        {
            next.current.changePeg(next.current.right, next.current.left);
            generate(next);
        }
    }
    next = old;

    // Two is on the right peg, shift to middle peg
    if (old.current.find(old.current, 2) == "right" && old.current.find(old.current, 1) != "right")
    {
        if (next.current.safemove(next.current.right, next.current.middle))
        {
            next.current.changePeg(next.current.right, next.current.middle);
            generate(next);
        }
    }
    next = old;
    // END OF DISK TWO

    // THIRD DISK
    // Three is on the left peg, shift to middle peg
    if (old.current.find(old.current, 3) == "left" && old.current.find(old.current, 2) != "left" && old.current.find(old.current, 1) != "left")
    {
        if (next.current.safemove(next.current.left, next.current.middle))
        {
            next.current.changePeg(next.current.left, next.current.middle);
            generate(next);
        }
    }
    next = old;

    // Three is on the left peg, shift to right peg
    if (old.current.find(old.current, 3) == "left" && old.current.find(old.current, 2) != "left" && old.current.find(old.current, 1) != "left")
    {
        if (next.current.safemove(next.current.left, next.current.right))
        {
            next.current.changePeg(next.current.left, next.current.right);
            generate(next);
        }
    }
    next = old;

    // Three is on the middle peg, shift to right peg
    if (old.current.find(old.current, 3) == "middle" && old.current.find(old.current, 2) != "middle" && old.current.find(old.current, 1) != "middle")
    {
        if (next.current.safemove(next.current.middle, next.current.right))
        {
            next.current.changePeg(next.current.middle, next.current.right);
            generate(next);
        }
    }
    next = old;

    // Three is on the middle peg, shift to left peg
    if (old.current.find(old.current, 3) == "middle" && old.current.find(old.current, 2) != "middle" && old.current.find(old.current, 1) != "middle")
    {
        if (next.current.safemove(next.current.middle, next.current.left))
        {
            next.current.changePeg(next.current.middle, next.current.left);
            generate(next);
        }
    }
    next = old;

    // Three is on the right peg, shift to left peg
    if (old.current.find(old.current, 3) == "right" && old.current.find(old.current, 1) != "right" && old.current.find(old.current, 2) != "right")
    {
        if (next.current.safemove(next.current.middle, next.current.left))
        {
            next.current.changePeg(next.current.right, next.current.left);
            generate(next);
        }
    }
    next = old;

    // Three is on the right peg, shift to middle peg
    if (old.current.find(old.current, 3) == "right" && old.current.find(old.current, 1) != "right" && old.current.find(old.current, 2) != "right")
    {
        if (next.current.safemove(next.current.middle, next.current.left))
        {
            next.current.changePeg(next.current.right, next.current.middle);
            generate(next);
        }
    }
    next = old;
} // end of generate all

state bestofFrontier()
{
    state temp;
    temp.f = 100000; // set comparison mark using arbitrary number

    // go through frontier and find state with smallest f
    for (int i = 0; i < frontier.size(); i++)
    {
        if (frontier[i].f < temp.f)
        {
            temp = frontier[i];
        }
    }
    cout << "Best is: " << endl;
    temp.current.printBoard();
    return temp;
} // end of bestofFrontier

// Display the states in the frontier  (called from main)
void displayFrontier()
{
    for (int k = 0; k < frontier.size(); k++)
    {
        frontier[k].current.printBoard();
        cout << "g = " << frontier[k].g << " ";
        cout << "h = " << frontier[k].h << " ";
        cout << "f = " << frontier[k].f << endl;
    }
}
// end of displayFrontier

int main()
{

    state s;
    s.g = 0;
    s.h = 3;
    s.f = 3;

    addtoFrontier(s);

    char ans;
    cout << "enter any key to continue, \'n\' to close     ";

    while (ans != 'n') // (true) // (ans != 'n') use this to generate state by state
    {
        removefromFrontier(s);
        addtoBeenThere(s);

        cout << "\n>>Expand<<" << endl;
        s.current.printBoard();
        generateAll(s);

        cout << "Frontier is: " << endl;
        displayFrontier();

        s = bestofFrontier();
        // cout << endl; //
        cin >> ans; // use cin to generate state by state if while condition is matched
    }
}
