#ifndef TAVLA_STACK_H
#define TAVLA_STACK_H

struct Node{
    char character;
    Node* next;

    Node(char c = ' ', Node* n = nullptr) : character(c), next(n)           //constructor
    {
    }
};

class Stack {
public:
    Stack();                        //default constructor
    Stack(const Stack & stk);       //copy constructor
    ~Stack();                       //destructor
    const Stack & operator =(const Stack & rhs);            //operator overload for =
    void Push(const char &c);       //adds c to the stack
    void Pop();                     //removes a node from the stack
    char getContent() const;        //returns the character of the head
    bool isEmpty() const;           //returns true if empty
    int getSize() const;            //returns the size

private:
    int size;
    Node* head = nullptr;
};


#endif //TAVLA_STACK_H
