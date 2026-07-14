#ifndef SEARCH_H
#define SEARCH_H

#include "binaryTree.h"
#include <stdexcept>

template <class t>
int cmp(const t &item1, const t &item2)
{
    if (item1 > item2)
    {
        return 1;
    }
    if (item1 == item2)
    {
        return 0;
    }
    if (item1 < item2)
    {
        return -1;
    }
    return 0;
}

template <class t>
class BinarySearchTree : public BinaryTree<t>
{
public:
    BinarySearchTree(int (*comp)(const t &, const t &) = cmp);
    void insert(const t &insertItem);
    bool search(const t &searchItem) const;
    void deleteNode(const t &deleteItem);

protected:
    int (*compare)(const t &item1, const t &item2);

private:
    void deleteFromTree(BinaryNode<t> *&currentNode);
    bool search(const t &searchItem, BinaryNode<t> *currentNode) const;
    void insert(BinaryNode<t> *&insertItem, BinaryNode<t> *&currentNode);
};

template <class t>
inline BinarySearchTree<t>::BinarySearchTree(int (*comp)(const t &, const t &))
{
    this->compare = comp;
}
template <class t>
inline void BinarySearchTree<t>::insert(const t &insertItem)
{
    BinaryNode<t> *newNode = new BinaryNode<t>(insertItem);
    insert(newNode, this->root);
}
template <class t>
inline bool BinarySearchTree<t>::search(const t &searchItem) const
{
    return search(searchItem, this->root);
}
template <class t>
inline void BinarySearchTree<t>::deleteNode(const t &deleteItem)
{
    BinaryNode<t> *current;
    BinaryNode<t> *currentParent;
    bool found = false;
    if (this->isEmpty())
    {
        throw std::invalid_argument("Cannot delete from an empty tree");
    }
    current = this->root;
    currentParent = current;
    int comparison;
    while (current != nullptr && !found)
    {
        comparison = compare(deleteItem, current->data);
        if (comparison == 0)
        {
            found = true;
        }
        else
        {
            currentParent = current;
            if (comparison == -1)
            {
                current = current->lLink;
            }
            else
            {
                current = current->rLink;
            }
        }
    }
    if (!found)
    {
        throw std::invalid_argument("The item to be deleted is not in the tree");
    }
    else
    {
        if (current == this->root)
        {
            deleteFromTree(this->root);
        }
        else if (compare(deleteItem, currentParent->data) == -1)
        {
            deleteFromTree(currentParent->lLink);
        }
        else
        {
            deleteFromTree(currentParent->rLink);
        }
    }
}
template <class t>
inline void BinarySearchTree<t>::deleteFromTree(BinaryNode<t> *&currentNode)
{
    BinaryNode<t> *replace;
    BinaryNode<t> *replaceParent;
    BinaryNode<t> *temp;
    if (currentNode == nullptr)
    {
        throw std::invalid_argument("The item to be deleted is not in the tree");
    }
    if (currentNode->lLink == nullptr && currentNode->rLink == nullptr)
    {
        temp = currentNode;
        currentNode = nullptr;
        delete temp;
    }
    else if (currentNode->lLink == nullptr)
    {
        temp = currentNode;
        currentNode = temp->rLink;
        delete temp;
    }
    else if (currentNode->rLink == nullptr)
    {
        temp = currentNode;
        currentNode = temp->lLink;
        delete temp;
    }
    else
    {
        replace = currentNode->lLink;
        replaceParent = nullptr;
        while (replace->rLink != nullptr)
        {
            replaceParent = replace;
            replace = replace->rLink;
        }
        t tempData;
        tempData = currentNode->data;
        currentNode->data = replace->data;
        replace->data = tempData;
        if (replaceParent == nullptr)
        {
            currentNode->lLink = replace->lLink;
        }
        else
        {
            replaceParent->rLink = replace->lLink;
        }
        delete replace;
        replace = nullptr;
    }
}
template <class t>
inline bool BinarySearchTree<t>::search(const t &searchItem, BinaryNode<t> *currentNode) const
{
    if (currentNode == nullptr)
    {
        return false;
    }
    int comparison = compare(searchItem, currentNode->data);
    if (comparison == 0)
    {
        return true;
    }
    if (comparison == -1)
    {
        return search(searchItem, currentNode->lLink);
    }
    else
    {
        return search(searchItem, currentNode->rLink);
    }
}
template <class t>
inline void BinarySearchTree<t>::insert(BinaryNode<t> *&insertItem, BinaryNode<t> *&currentNode)
{
    if (currentNode == nullptr)
    {
        currentNode = insertItem;
    }
    else
    {
        int comparison = compare(insertItem->data, currentNode->data);
        if (comparison == 0)
        {
            delete insertItem;
            throw std::invalid_argument("The item to be inserted is already in the tree -- duplicates are not allowed");
        }
        if (comparison == -1)
        {
            insert(insertItem, currentNode->lLink);
        }
        else
        {
            insert(insertItem, currentNode->rLink);
        }
    }
}
#endif