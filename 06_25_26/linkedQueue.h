#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H
#include "queueADT.h"
#include "node.h"

template <class t>
class LinkedQueue : public QueueADT<t>
{
public:
    LinkedQueue();
    LinkedQueue(const LinkedQueue<t> &);
    const LinkedQueue<t> &operator=(const LinkedQueue<t> &);
    ~LinkedQueue();
    bool isEmptyQueue() const;
    bool isFullQueue() const;
    void initializeQueue();
    t front() const;
    t back() const;
    void enqueue(const t &queueElement);
    t dequeue();

private:
    node<t> *queueFront;
    node<t> *queueRear;
    void copyQueue(const LinkedQueue<t> &);
};

#endif

template <class t>
inline LinkedQueue<t>::LinkedQueue()
{
    queueFront = nullptr;
    queueRear = nullptr;
}

template <class t>
inline LinkedQueue<t>::LinkedQueue(const LinkedQueue<t> &queueToCopy)
{
    queueFront = nullptr;
    queueRear = nullptr;
    copyQueue(queueToCopy);
}

template <class t>
inline const LinkedQueue<t> &LinkedQueue<t>::operator=(const LinkedQueue<t> &queueToCopy)
{
    if (this != &queueToCopy)
    {
        copyQueue(queueToCopy);
    }
    return *this;
}

template <class t>
inline LinkedQueue<t>::~LinkedQueue()
{
    initializeQueue();
}

template <class t>
inline bool LinkedQueue<t>::isEmptyQueue() const
{
    return queueFront == nullptr;
}

template <class t>
inline bool LinkedQueue<t>::isFullQueue() const
{
    return false;
}

template <class t>
inline void LinkedQueue<t>::initializeQueue()
{
    if (!isEmptyQueue())
    {
        node<t> *temp;
        while (this->queueFront != nullptr)
        {
            temp = queueFront;
            queueFront = queueFront->link;
            delete temp;
        }
        queueRear = nullptr;
    }
}

template <class t>
inline t LinkedQueue<t>::front() const
{
    if (isEmptyQueue())
    {
        throw std::out_of_range("Cannot get the first item of an empty queue");
    }
    return queueFront->data;
}

template <class t>
inline t LinkedQueue<t>::back() const
{
    if (isEmptyQueue())
    {
        throw std::out_of_range("Cannot get the last item of an empty queue");
    }
    return queueRear->data;
}

template <class t>
inline void LinkedQueue<t>::enqueue(const t &queueElement)
{
    node<t> *newNode;
    newNode = new node<t>(queueElement);
    if (isEmptyQueue())
    {
        queueFront = newNode;
        queueRear = newNode;
    }
    else
    {
        queueRear->link = newNode;
        queueRear = newNode;
    }
}

template <class t>
inline t LinkedQueue<t>::dequeue()
{
    if (isEmptyQueue())
    {
        throw std::out_of_range("Cannot delete from an empty queue");
    }
    node<t> *temp;
    temp = queueFront;
    queueFront = queueFront->link;
    t copy(temp->data);
    delete temp;
    return copy;
}

template <class t>
inline void LinkedQueue<t>::copyQueue(const LinkedQueue<t> &queueToCopy)
{
    node<t> *newNode;
    node<t> *current;
    if (!isEmptyQueue())
    {
        initializeQueue();
    }
    if (queueToCopy.isEmptyQueue())
    {
        queueFront = nullptr;
        queueRear = nullptr;
    }
    else
    {
        current = queueToCopy.queueFront;
        queueFront = new node<t>(current->data);
        queueRear = queueFront;
        current = current->link;
        while (current != nullptr)
        {
            newNode = new node<t>(current->data);
            queueRear->link = newNode;
            queueRear = newNode;
            current = current->link;
        }
    }
}
