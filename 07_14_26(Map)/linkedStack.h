#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H
#include "stackADT.h"
#include "node.h"
#include <stdexcept>

template <class t>
class LinkedStack : public StackADT<t>
{
public:
    LinkedStack();
    LinkedStack(const LinkedStack<t> &);
    const LinkedStack<t> &operator=(const LinkedStack<t> &);
    void initializeStack();
    bool isFullStack() const;
    bool isEmptyStack() const;
    void push(const t &);
    t peek() const;
    t &top();
    t pop();
    ~LinkedStack();

private:
    void copyStack(const LinkedStack<t> &);
    node<t> *stackTop;
    int count;
};

template <class t>
LinkedStack<t>::LinkedStack()
{
    stackTop = nullptr;
    count = 0;
}
template <class t>
LinkedStack<t>::LinkedStack(const LinkedStack<t> &stackToCopy)
{
    stackTop = nullptr;
    count = 0;
    copyStack(stackToCopy);
}
template <class t>
const LinkedStack<t> &LinkedStack<t>::operator=(const LinkedStack<t> &stackToCopy)
{
    if (this != &stackToCopy)
    {
        copyStack(stackToCopy);
    }
    return *this;
}
template <class t>
void LinkedStack<t>::initializeStack()
{
    node<t> *temp;
    while (stackTop != nullptr)
    {
        temp = stackTop;
        stackTop = stackTop->link;
        delete temp;
    }
    count = 0;
}

template <class t>
LinkedStack<t>::~LinkedStack()
{
    initializeStack();
}

template <class t>
void LinkedStack<t>::copyStack(const LinkedStack<t> &stackToCopy)
{
    node<t> *newNode;
    node<t> *current;
    node<t> *last;
    if (!isEmptyStack())
    {
        initializeStack();
    }
    if (stackToCopy.isEmptyStack())
    {
        this->stackTop = nullptr;
        count = 0;
    }
    else
    {
        current = stackToCopy.stackTop;
        this->stackTop = new node<t>(current->data);
        last = this->stackTop;
        current = current->link;
        while (current != nullptr)
        {
            newNode = new node<t>(current->data);
            last->link = newNode;
            last = newNode;
            current = current->link;
        }
        this->count = stackToCopy.count;
    }
}

template <class t>
bool LinkedStack<t>::isFullStack() const
{
    return false;
}

template <class t>
bool LinkedStack<t>::isEmptyStack() const
{
    return stackTop == nullptr;
}

template <class t>
void LinkedStack<t>::push(const t &newItem)
{
    node<t> *newNode;
    newNode = new node<t>(newItem);
    newNode->link = stackTop;
    stackTop = newNode;
    count++;
}

template <class t>
t LinkedStack<t>::peek() const
{
    if (isEmptyStack())
    {
        throw std::out_of_range("Empty Stack");
    }
    return stackTop->data;
}

template <class t>
t &LinkedStack<t>::top()
{
    if (isEmptyStack())
    {
        throw std::out_of_range("Empty Stack");
    }
    return stackTop->data;
}

template <class t>
t LinkedStack<t>::pop()
{
    if (isEmptyStack())
    {
        throw std::underflow_error("Stack underfow. Cannot remove from an empty stack.");
    }
    t copy = stackTop->data;
    node<t> *temp = stackTop;
    stackTop = stackTop->link;
    delete temp;
    count--;
    return copy;
}
#endif