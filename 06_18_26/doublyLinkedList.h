#ifndef DOUBLE_H
#define DOUBLE_H
#include "unorderedLinkedList.h"
template <class t>
class DoublyLinkedList : public UnorderedLinkedList<t>
{
public:
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList &listToCopy);
    const DoublyLinkedList<t> &operator=(const DoublyLinkedList<t> &listToCopy);
    void insert(const t &newInfo);
    void deleteNode(const t &deleteItem);
    void reversePrint(std::ostream &out = std::cout, std::string separator = " ") const;

private:
    void
    copyList(const DoublyLinkedList<t> &listToCopy);
};

template <class t>
DoublyLinkedList<t>::DoublyLinkedList()
{
}

template <class t>
DoublyLinkedList<t>::DoublyLinkedList(const DoublyLinkedList &listToCopy)
{
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
    copyList(listToCopy);
}

template <class t>
const DoublyLinkedList<t> &DoublyLinkedList<t>::operator=(const DoublyLinkedList<t> &listToCopy)
{
    if (this != &listToCopy)
    {
        copyList(listToCopy);
    }
    return *this;
}

template <class t>
void DoublyLinkedList<t>::insert(const t &newInfo)
{
    node<t> *newNode;
    newNode = new node<t>;
    newNode->data = new t(newInfo); // avoid shallow copy
    newNode->link = nullptr;
    newNode->back = this->tail;
    if (this->isEmptyList())
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        this->tail->link = newNode;
        this->tail = newNode;
    }
    this->count++;
}

template <class t>
void DoublyLinkedList<t>::deleteNode(const t &deleteItem)
{
    node<t> *current;
    bool found;
    if (this->isEmptyList())
    {
        throw std::out_of_range("Cannot delete from an empty list.");
    }
    if (*(this->head->data) == deleteItem)
    {
        current = this->head;
        this->head = this->head->link; // move head forward

        if (this->head == nullptr)
        {
            this->tail = nullptr;
        }
        else
        {
            this->head->back = nullptr; // remove back reference to old head
        }
    }
    else
    {
        found = false;
        current = this->head->link;
        while (current != nullptr && !found)
        {
            if (*(current->data) != deleteItem)
            {
                current = current->link; // move current ahead by 1
            }
            else
            {
                found = true;
            }
        }
        if (found)
        {
            current->back->link = current->link; // remove current from the navigation
            current->link->back = current->back;
            if (this->tail == current)
            {
                this->tail = current->back;
            }
        }
        else
        {
            throw std::out_of_range("Item to be deleted not found in the list");
        }
    }
    delete current;
    this->count--;
}

template <class t>
void DoublyLinkedList<t>::reversePrint(std::ostream &out, std::string separator) const
{
    node<t> *current;
    current = this->tail;
    while (current != nullptr)
    {
        out << *current->data << separator;
        current = current->back;
    }
}

template <class t>
void DoublyLinkedList<t>::copyList(const DoublyLinkedList<t> &listToCopy)
{
    node<t> *newNode;
    node<t> *current;
    if (!this->isEmptyList())
    {
        this->destroyList();
    }
    if (listToCopy.isEmptyList())
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->count = 0;
    }
    else
    {
        // begin the copy
        current = listToCopy.head;
        this->count = listToCopy.count;
        // node2 version
        // this->head = new node2<t>(listToCopy.head);
        this->head = new node<t>;
        // dont do this->head->data = listToCopy.head->data; this will produce a shallow copy
        this->head->data = new t(*(listToCopy.head->data));
        this->head->link = nullptr;
        this->head->back = nullptr;
        this->tail = this->head;
        current = current->link; // advance current to the next node
        while (current != nullptr)
        {
            newNode = new node<t>;
            newNode->data = new t(*(current->data));
            newNode->link = nullptr;
            newNode->back = this->tail;
            this->tail->link = newNode;
            this->tail = newNode; // move the end of the list
            // this->tail = this->tail->link; same as line above
            current = current->link;
        }
    }
}
#endif