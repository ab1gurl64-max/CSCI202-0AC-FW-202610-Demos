#ifndef LINKED_H
#define LINKED_H
#include "node.h"
#include "linkedListIterator.h"
#include <iostream>
#include <string>

template <class t>
class LinkedList
{
public:
    LinkedList();
    LinkedList(const LinkedList<t> &otherList);
    const LinkedList<t> &operator=(const LinkedList<t> &);
    ~LinkedList();
    void destroyList();
    bool isEmptyList() const;
    int length() const;
    t front() const;
    t back() const;
    virtual void insert(const t &newInfo) = 0;
    virtual void deleteNode(const t &deleteItem) = 0;
    virtual bool search(const t &searchItem) const = 0;
    void print(std::ostream & = std::cout, std::string = " ") const;
    LinkedListIterator<t> begin() { return LinkedListIterator<t>(head); };
    LinkedListIterator<t> end() { return LinkedListIterator<t>(); };

protected:
    node<t> *head;
    node<t> *tail;
    int count;

private:
    void copyList(const LinkedList<t> &otherList);
};

template <class t>
LinkedList<t>::LinkedList()
{
    this->head = nullptr;
    this->tail = nullptr;
    count = 0;
}

template <class t>
LinkedList<t>::LinkedList(const LinkedList<t> &otherList)
{
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
    this->copyList(otherList);
}

template <class t>
const LinkedList<t> &LinkedList<t>::operator=(const LinkedList<t> &listToCopy)
{
    if (this != *listToCopy) // prevent self copy
    {
        this->copyList(listToCopy);
    }
    return *this;
}

template <class t>
LinkedList<t>::~LinkedList()
{
    this->destroyList();
}

template <class t>
void LinkedList<t>::destroyList()
{
    if (!this->isEmptyList())
    {
        node<t> *temp;
        while (head != nullptr)
        {
            temp = this->head;
            this->head = this->head->link; // move head forward;
            delete temp;
        }
        this->tail = nullptr;
        count = 0;
    }
}

template <class t>
bool LinkedList<t>::isEmptyList() const
{
    return this->head == nullptr || count == 0;
}

template <class t>
int LinkedList<t>::length() const
{
    return this->count;
}

template <class t>
t LinkedList<t>::front() const
{
    return (this->head->data);
}

template <class t>
t LinkedList<t>::back() const
{
    return (this->tail->data);
}

template <class t>
void LinkedList<t>::print(std::ostream &out, std::string separator) const
{
    if (!isEmptyList())
    {
        node<t> *current;
        current = this->head;
        while (current != nullptr)
        {
            out << current->data << separator;
            current = current->link;
        }
    }
}

template <class t>
void LinkedList<t>::copyList(const LinkedList<t> &otherList)
{
    node<t> *newNode;
    node<t> *current;
    if (!isEmptyList())
    {
        destroyList();
    }
    if (otherList.isEmptyList())
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->count = 0;
    }
    else
    {
        // begin the copy
        current = otherList.head;
        this->count = otherList.count;
        // node2 version
        // this->head = new node2<t>(otherList.head);
        this->head = new node<t>(otherList.head->data);

        this->tail = this->head;
        current = current->link; // advance current to the next node
        while (current != nullptr)
        {
            newNode = new node<t>(current->data);

            this->tail->link = newNode;
            this->tail = newNode; // move the end of the list
            // this->tail = this->tail->link; same as line above
            current = current->link;
        }
    }
}
#endif