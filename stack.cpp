#include <iostream>
#include "stack.h"

using namespace std;

// PURPOSE:  Constructor must initialize top to be -1 to begin with.
stack::stack()
{
    top = -1; // indicate an empty stack
}

// PURPOSE:  Destructor does not have to do anything since this is a static array.
stack::~stack()
{ // nothing
}

// PURPOSE:  checks top and returns true if empty, false otherwise.
bool stack::isEmpty()
{
    if (top == -1)
        return true;
    else
        return false;
}

// PURPOSE: checks top and returns true if full, false otherwise.
bool stack::isFull()
{
    if (top == MAX - 1)
        return true;
    else
        return false;
}

// PURPOSE: calls isFull and if true, throws an exception (Overflow)
//    Otherwise, adds an element to el after incrementing top.
// PARAMETER: pass the element (elem) to be pushed
void stack::push(el_t elem)
{
    if (isFull())
        throw Overflow();
    else
    {
        top++;
        el[top] = elem;
    }
}

// PURPOSE: calls isEmpty and if true, throws an exception (Underflow)
//   Otherwise, removes an element from el and gives it back.
// PARAMETER: provide a holder (elem) for the element popped (pass by ref)
void stack::pop(el_t &elem)
{
    if (isEmpty())
        throw Underflow();
    else
    {
        elem = el[top];
        el[top] = 0;
        top--;
    }
}

// PURPOSE: calls isEmpty and if true, throws an exception (underflow)
//    Otherwise, gives back the top element from el.
// PARAMETER: provide a holder (elem) for the element (pass by ref)
void stack::topElem(el_t &elem)
{
    if (isEmpty())
        throw Underflow();
    else
    {
        elem = el[top];
    }
}

// PURPOSE: dislayAll calls isEmpty and if true, displays [ empty ].
//          Otherwise, diplays the elements vertically.
void stack::displayAll()
{
    cout << "STACK:---------" << endl;
    if (isEmpty())
        cout << "[ empty ]" << endl;
    else
        for (int i = top; i >= 0; i--)
        {
            cout << el[i] << endl;
        }
    cout << "--------------" << endl;
}

// PURPOSE: pops all elements from the stack until
//  it is empty using a while loop
void stack::clearIt()
{
    el_t temp; // temp variable of type int to pop all elements of the stack

    while (!isEmpty()) // do not do top = -1, use a while loop
    {
        pop(temp); // pop el_t type from stack
    }
}

// return an element at the index for a stack
el_t stack::returnElement(int i)
{
    el_t value;

    if (isEmpty())
        return 0;
    else
    {
        value = el[i];
        return value;
    }
}