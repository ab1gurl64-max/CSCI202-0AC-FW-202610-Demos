#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H
#include "stackADT.h"
#include <stdexcept>

template <class t>
class ArrayStack : public StackADT<t>
{
public:
    ArrayStack(int = StackADT<t>::DEFAULT_STACK_SIZE);
    ArrayStack(const ArrayStack<t> &);
    const ArrayStack<t> &operator=(const ArrayStack<t> &);
    void initializeStack();
    bool isFullStack() const;
    bool isEmptyStack() const;
    void push(const t &);
    t peek() const;
    t &top();
    t pop();
    ~ArrayStack();

private:
    void copyStack(const ArrayStack<t> &);
    int stackTop;
    int maxStackSize;
    t **list;
};

template <class t>
ArrayStack<t>::ArrayStack(int max)
{
    if (max <= 0)
    {
        max = StackADT<t>::DEFAULT_STACK_SIZE;
    }
    maxStackSize = max;
    stackTop = 0;
    list = new t *[maxStackSize];
    for (int i = 0; i < maxStackSize; i++)
    {
        list[i] = nullptr;
    }
}
template <class t>
ArrayStack<t>::ArrayStack(const ArrayStack<t> &stackToCopy)
{
    stackTop = 0;
    list = nullptr;
    maxStackSize = 0;
    copyStack(stackToCopy);
}
template <class t>
const ArrayStack<t> &ArrayStack<t>::operator=(const ArrayStack<t> &stackToCopy)
{
    if (this != &stackToCopy)
    {
        copyStack(stackToCopy);
    }
    return *this;
}
template <class t>
void ArrayStack<t>::initializeStack()
{
    if (!isEmptyStack())
    {
        for (int i = 0; i < stackTop; i++)
        {
            delete list[i];
            list[i] = nullptr;
        }
    }
    stackTop = 0;
}

template <class t>
ArrayStack<t>::~ArrayStack()
{
    initializeStack();
    delete[] list;
}

template <class t>
void ArrayStack<t>::copyStack(const ArrayStack<t> &stackToCopy)
{
    if (!isEmptyStack())
    {
        initializeStack();
    }
    if (this->maxStackSize < stackToCopy.maxStackSize)
    {
        delete[] this->list;
        this->maxStackSize = stackToCopy.maxStackSize;
        this->list = new t *[this->maxStackSize];
    }
    this->stackTop = stackToCopy.stackTop;
    for (int i = 0; i < stackTop; i++)
    {
        this->list[i] = new t(*(stackToCopy.list[i]));
    }
}

template <class t>
bool ArrayStack<t>::isFullStack() const
{
    return stackTop == maxStackSize;
}

template <class t>
bool ArrayStack<t>::isEmptyStack() const
{
    return stackTop == 0;
}

template <class t>
void ArrayStack<t>::push(const t &newItem)
{
    if (!isFullStack())
    {
        list[stackTop] = new t(newItem);
        stackTop++;
    }
    else
    {
        throw std::overflow_error("Stack Overflow. Cannot add to a full stack");
    }
}

template <class t>
t ArrayStack<t>::peek() const
{
    if (isEmptyStack())
    {
        throw std::out_of_range("Empty Stack");
    }
    return *(list[stackTop - 1]);
}

template <class t>
t &ArrayStack<t>::top()
{
    if (isEmptyStack())
    {
        throw std::out_of_range("Empty Stack");
    }
    return *(list[stackTop - 1]);
}

template <class t>
t ArrayStack<t>::pop()
{
    if (isEmptyStack())
    {
        throw std::underflow_error("Stack underfow. Cannot remove from an empty stack.");
    }
    t copy = *(list[stackTop - 1]);
    delete list[stackTop - 1];
    list[stackTop - 1] = nullptr;
    stackTop--;
    return copy;
}
#endif