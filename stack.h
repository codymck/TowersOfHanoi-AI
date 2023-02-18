//----- Globally setting up the aliases ----------------

const int MAX = 3; // The MAX number of elements for the stack
                   // MAX is unknown to the client

typedef int el_t; // the el_t type is int for now
                  // el_t is unknown to the client
//-------------------------------------------------------

class stack
{

private:          // to be hidden from the client
    el_t el[MAX]; // el is  an array of el_t's
    int top;      // top is index to the top of stack

public: // available to the client
        // exception handling classes
    class Overflow
    {
    };

    class Underflow
    {
    };
    // prototypes to be used by the client
    // Note that no parameter variables are given

    stack();  // constructor to create an object
    ~stack(); // destructor  to destroy an object

    // PURPOSE: if not full, enters an element at the top;
    //          otherwise throws an exception - Overflow
    // PARAMETER: pass the element to be pushed
    void push(el_t);

    // PURPOSE: if not empty, removes and gives back the top element;
    //          otherwise throws an exception - Underflow
    // PARAMETER: provide variable to receive the popped element (by ref)
    void pop(el_t &);

    // PURPOSE: if not empty, gives the top element without removing it;
    //          otherwise, throws an exception - Underflow
    // PARAMETER: int being passed by reference
    void topElem(el_t &);

    // PURPOSE: check to see if the stack is empty, returns true or false
    bool isEmpty();

    // PURPOSE: check to see if the stack is full, returns true or false
    bool isFull();

    // PURPOSE: prints all elements in the stack
    //  throws exception if there is nothing to display
    void displayAll();

    // PURPOSE: clears all elements in the stack
    //   throws exception if the stack is already empty
    void clearIt();

    // PURPOSE: return an element in the stack ast index i
    // PARAM: pass the integer of index
    el_t returnElement(int i);
};