#ifndef ARRAYQ_H
#define ARRAYQ_H
#include "queueADT.h"
#include <iostream>

template <class t>
class ArrayQueue : public QueueADT<t>
{
public:
    ArrayQueue(int = QueueADT<t>::DEFAULT_QUEUE_SIZE);
    ArrayQueue(const ArrayQueue<t> &);
    const ArrayQueue<t> &operator=(const ArrayQueue<t> &);
    ~ArrayQueue();
    bool isEmptyQueue() const;
    bool isFullQueue() const;
    void initializeQueue();
    t front() const;
    t back() const;
    void enqueue(const t &queueElement);
    t dequeue();

private:
    t **list;
    int maxQueueSize;
    int queueFront;
    int queueRear;
    int count;
    void copyQueue(const ArrayQueue<t> &);
};

#endif

template <class t>
inline ArrayQueue<t>::ArrayQueue(int max)
{
    if (max < 1)
    {
        max = QueueADT<t>::DEFAULT_QUEUE_SIZE;
    }
    maxQueueSize = max;
    list = new t *[maxQueueSize];
    for (int i = 0; i < maxQueueSize; i++)
    {
        list[i] = nullptr;
    }
    count = 0;
    queueFront = maxQueueSize - 1;
    queueRear = maxQueueSize - 1;
}

template <class t>
inline ArrayQueue<t>::ArrayQueue(const ArrayQueue<t> &queueToCopy)
{
    maxQueueSize = 0;
    count = 0;
    queueFront = maxQueueSize - 1;
    queueRear = maxQueueSize - 1;
    list = nullptr;
    copyQueue(queueToCopy);
}

template <class t>
inline const ArrayQueue<t> &ArrayQueue<t>::operator=(const ArrayQueue<t> &queueToCopy)
{
    if (this != &queueToCopy)
    {
        copyQueue(queueToCopy);
    }
    return *this;
}

template <class t>
inline ArrayQueue<t>::~ArrayQueue()
{
    initializeQueue();
    delete[] list;
}

template <class t>
inline bool ArrayQueue<t>::isEmptyQueue() const
{
    return queueFront == queueRear || count == 0;
}

template <class t>
inline bool ArrayQueue<t>::isFullQueue() const
{
    return count == maxQueueSize || (queueRear + 1) % maxQueueSize == queueFront;
}

template <class t>
inline void ArrayQueue<t>::initializeQueue()
{
    for (int i = (queueFront + 1) % maxQueueSize; i != queueRear; i = (i + 1) % maxQueueSize)
    {
        delete list[queueFront];
        list[queueFront] = nullptr;
    }
    queueFront = maxQueueSize - 1;
    queueRear = maxQueueSize - 1;
}

template <class t>
inline t ArrayQueue<t>::front() const
{
    if (isEmptyQueue())
    {
        throw std::out_of_range("Cannot get the first item of an empty queue");
    }
    return *(list[(queueFront + 1) % maxQueueSize]);
}

template <class t>
inline t ArrayQueue<t>::back() const
{
    if (isEmptyQueue())
    {
        throw std::out_of_range("Cannot get the first item of an empty queue");
    }
    return *(list[queueRear]);
}

template <class t>
inline void ArrayQueue<t>::enqueue(const t &queueElement)
{
    if (isFullQueue())
    {
        throw std::overflow_error("Cannot add to a full queue.");
    }
    queueRear = (queueRear + 1) % maxQueueSize;
    list[queueRear] = new t(queueElement);
    count++;
}

template <class t>
inline t ArrayQueue<t>::dequeue()
{
    if (isEmptyQueue())
    {
        throw std::out_of_range("Cannot delete from an empty queue");
    }
    queueFront = (queueFront + 1) % maxQueueSize;
    t copy = *(list[queueFront]);
    delete list[queueFront];
    list[queueFront] = nullptr;
    count--;
    return copy;
}

template <class t>
inline void ArrayQueue<t>::copyQueue(const ArrayQueue<t> &queueToCopy)
{
    if (!isEmptyQueue())
    {
        this->initializeQueue();
    }
    if (maxQueueSize < queueToCopy.maxQueueSize)
    {
        delete[] list;
        maxQueueSize = queueToCopy.maxQueueSize;
        list = new t *[maxQueueSize];
        for (int i = 0; i < this->maxQueueSize; i++)
        {
            list[i] = nullptr;
        }
    }
    queueFront = maxQueueSize - 1;
    queueRear = maxQueueSize - 1;
    for (int i = (queueToCopy.queueFront + 1) % queueToCopy.maxQueueSize; i != (queueToCopy.queueRear + 1) % queueToCopy.maxQueueSize; i = (i + 1) % queueToCopy.maxQueueSize)
    {
        enqueue(*(queueToCopy.list[i]));
    }
}
