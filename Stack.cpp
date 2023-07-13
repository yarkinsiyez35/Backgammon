#include "Stack.h"

Stack::Stack()
{
    head = nullptr;
    size = 0;
}

Stack::Stack(const Stack &stk)
{
    head = nullptr;
    size = 0;

    int stkSize = stk.getSize();
    char ch = stk.getContent();
    for (int i = 0; i< stkSize; i++)                //adds the character of the stk to stkSize many times to the stack
    {
        this->Push(ch);
    }
}

Stack::~Stack()
{
    while(head!= nullptr)           //deletes every node starting from the head
    {
        Node * temp = head;
        head = temp->next;
        delete temp;
    }
}

const Stack & Stack::operator =(const Stack & rhs)
{
    if (this != & rhs)
    {
        int SIZE = rhs.size;
        char PIECE = rhs.getContent();
        while(this->getSize() != 0)         //while lhs is not empty
        {
            this->Pop();            //empties the stack
        }
        for (int i = 0; i< SIZE; i++)
        {
            this->Push(PIECE);          //pushes SIZE many pieces to lhs
        }
    }
    return *this;
}

void Stack::Push(const char &c)
{
    Node * added = new Node(c, nullptr);         //creates a new object to add to the stack
    if (head == nullptr)                            //if this is the first node
    {
        head = added;
    }
    else                                            //if there are previously existing nodes
    {
        added->next = head;
        head = added;
    }
    size++;                                         //update the size
}

void Stack::Pop()
{
    if(head != nullptr)                             //if the stack is not empty
    {
        Node * temp = head;                         //creates a temporary object to delete
        head = temp->next;                          //head is updated
        delete temp;
        size--;                                     //updates the size
    }
}

char Stack::getContent()    const
{
    if (head != nullptr)             //returns the character at the head of the stack
    {
        return head->character;
    }
    else                            //returns empty character if the stack is empty
    {
        return ' ';
    }
}

bool Stack::isEmpty() const
{
    return head == nullptr;
}

int Stack::getSize() const
{
    return size;
}