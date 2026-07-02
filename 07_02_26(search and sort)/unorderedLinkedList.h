#ifndef UNORDERED_H
#define UNORDERED_H
#include <stdexcept>
#include "linkedlist.h"

template <class t>
class UnorderedLinkedList : public LinkedList<t>
{
public:
    enum class directionType
    {
        FORWARD,
        BACKWARD
    };
    UnorderedLinkedList(directionType = directionType::FORWARD);
    void insert(const t &newInfo);
    void deleteNode(const t &deleteItem);
    bool search(const t &searchItem) const;
    void mergeSort();

private:
    directionType direction;
    void insertFirst(node<t> *newNode);
    void insertLast(node<t> *newNode);
    void recMergeSort(node<t> *&start);
    void divideList(node<t> *left, node<t> *&right);
    node<t> *mergeList(node<t> *left, node<t> *right);
};

template <class t>
UnorderedLinkedList<t>::UnorderedLinkedList(directionType d)
{
    direction = d;
}

template <class t>
void UnorderedLinkedList<t>::insert(const t &newInfo)
{
    node<t> *newNode;
    newNode = new node<t>;
    newNode->data = new t(newInfo); // avoid shallow copy
    newNode->link = nullptr;
    if (this->isEmptyList())
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else if (direction == directionType::FORWARD)
    {
        insertLast(newNode);
    }
    else
    {
        insertFirst(newNode);
    }
    this->count++;
}

template <class t>
void UnorderedLinkedList<t>::deleteNode(const t &deleteItem)
{
    node<t> *current;
    node<t> *trailCurrent;
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
    }
    else
    {
        found = false;
        trailCurrent = this->head;
        current = this->head->link;
        while (current != nullptr && !found)
        {
            if (*(current->data) != deleteItem)
            {
                trailCurrent = current;  // move the pointer trailing current ahead by 1
                current = current->link; // move current ahead by 1
            }
            else
            {
                found = true;
            }
        }
        if (found)
        {
            trailCurrent->link = current->link; // remove current from the navigation
            if (this->tail == current)
            {
                this->tail = trailCurrent;
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
bool UnorderedLinkedList<t>::search(const t &searchItem) const
{
    node<t> *current;
    bool found = false;
    current = this->head;
    while (current != nullptr && !found)
    {
        if (*(current->data) == searchItem)
        {
            found = true;
        }
        else
        {
            current = current->link;
        }
    }
    return found;
}

template <class t>
void UnorderedLinkedList<t>::insertFirst(node<t> *newNode)
{
    newNode->link = this->head; // put new item on front of list
    this->head = newNode;       // move head to the new first node
}

template <class t>
void UnorderedLinkedList<t>::insertLast(node<t> *newNode)
{
    this->tail->link = newNode; // put the new item on the end of the list
    this->tail = newNode;       // move tail to the new last node
}

template <class t>
inline void UnorderedLinkedList<t>::mergeSort()
{
    recMergeSort(this->head);
    if (this->head == nullptr)
    {
        this->tail = nullptr;
    }
    else
    {
        this->tail = this->head;
        while (this->tail->link != nullptr)
        {
            this->tail = this->tail->link;
        }
    }
}
template <class t>
inline void UnorderedLinkedList<t>::recMergeSort(node<t> *&start)
{
    node<t> *otherStart;
    if (start != nullptr)
    {
        if (start->link = nullptr)
        {
            divideList(start, otherStart);
            recMergeSort(start);
            recMergeSort(otherStart);
            start = mergeList(start, otherStart);
        }
    }
}
template <class t>
inline void UnorderedLinkedList<t>::divideList(node<t> *left, node<t> *&right)
{
    node<t> *middle;
    node<t> *current;
    if (left == nullptr || left->link == nullptr)
    {
        right = nullptr;
    }
    else
    {
        middle = left;
        current = left->link;
        if (current != nullptr)
        {
            current = current->link;
        }
        while (current != nullptr)
        {
            middle = middle->link;
            current = current->link;
            if (current != nullptr)
            {
                current = current->link;
            }
        }
        right = middle->link;
        middle->link = nullptr;
    }
}
template <class t>
inline node<t> *UnorderedLinkedList<t>::mergeList(node<t> *left, node<t> *right)
{
    node<t> *lastSmall;
    node<t> *newHead;
    if (left == nullptr)
    {
        return right;
    }
    if (right == nullptr)
    {
        return left;
    }
    if (*(left->data) <= *(right->data))
    {
        newHead = left;
        left = left->link;
    }
    else
    {
        newHead = right;
        right = right->link;
    }
    lastSmall = newHead;
    while (left != nullptr && right != nullptr)
    {
        if (*(left->data) <= *(right->data))
        {
            lastSmall->link = left;
            left = left->link;
        }
        else
        {
            lastSmall->link = right;
            right = right->link;
        }
        lastSmall = lastSmall->link;
    }
    if (left == nullptr)
    {
        lastSmall->link = right;
    }
    else
    {
        lastSmall->link = left;
    }
    return newHead;
}
#endif