#ifndef AVLTREE_H
#define AVLTREE_H
#include "binarySearchTree.h"
#include "linkedStack.h"
#include <sstream>
#include <iostream>

template <class t>
class AVLTree : public BinarySearchTree<t>
{
public:
    AVLTree(int (*comp)(const t &, const t &) = cmp);
    void deleteNode(const t &deleteItem);
    class Iterator
    {
    public:
        Iterator(BinaryNode<t> *currentNode = nullptr, bool pushSmaller = true);
        bool hasNext();
        Iterator operator++();
        t &operator*();
        bool operator==(const Iterator &other) const;
        bool operator!=(const Iterator &other) const;

    private:
        LinkedStack<BinaryNode<t> *> nodeStack;
        void pushLeftNodes(BinaryNode<t> *node, bool pushSmaller);
    };
    void insert(const t &insertItem);
    Iterator insertAVL(const t &insertItem);
    Iterator begin() { return Iterator(this->root); };
    Iterator end() { return Iterator(nullptr); };
    Iterator find(const t &searchItem) const;
    bool isBalanced();

private:
    void balanceFromLeft(BinaryNode<t> *&currentNode);
    void balanceFromRight(BinaryNode<t> *&currentNode);
    void rotateToLeft(BinaryNode<t> *&currentNode);
    void rotateToRight(BinaryNode<t> *&currentNode);
    void insertIntoAVL(BinaryNode<t> *&currentNode, BinaryNode<t> *newNode, bool &isTaller, Iterator &it);
    Iterator find(const t &searchItem, BinaryNode<t> *currentNode) const;
    int calculateBalance(BinaryNode<t> *currentNode);
    bool isBalanced(BinaryNode<t> *currentNode);
    void balanceTree(BinaryNode<t> *&currentNode);
    void deleteFromTree(BinaryNode<t> *&currentNode, const t &key);
    BinaryNode<t> *findMin(BinaryNode<t> *node) const;
};

template <class t>
AVLTree<t>::AVLTree(int (*comp)(const t &, const t &)) : BinarySearchTree<t>(comp) {}

template <class t>
void AVLTree<t>::deleteNode(const t &deleteItem)
{
    try
    {
        deleteFromTree(this->root, deleteItem);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
    }
}

template <class t>
void AVLTree<t>::insert(const t &insertItem)
{
    insertAVL(insertItem);
}

template <class t>
AVLTree<t>::Iterator AVLTree<t>::insertAVL(const t &insertItem)
{
    bool isTaller = false;
    BinaryNode<t> *newNode = new BinaryNode<t>(insertItem);
    Iterator it;
    insertIntoAVL(this->root, newNode, isTaller, it);

    return it;
}

template <class t>
AVLTree<t>::Iterator AVLTree<t>::find(const t &searchItem) const
{
    Iterator it = find(searchItem, this->root);
    return it;
}

template <class t>
bool AVLTree<t>::isBalanced()
{
    return isBalanced(this->root);
}

template <class t>
void AVLTree<t>::balanceFromLeft(BinaryNode<t> *&currentNode)
{
    BinaryNode<t> *lChild;
    BinaryNode<t> *lChild_rChild;
    lChild = currentNode->lLink;
    switch (lChild->bfactor)
    {
    case 0:
    case -1:
        currentNode->bfactor = 0;
        lChild->bfactor = 0;
        rotateToRight(currentNode);
        break;
    case 1:
        lChild_rChild = lChild->rLink;
        switch (lChild_rChild->bfactor)
        {
        case -1:
            currentNode->bfactor = 1;
            lChild->bfactor = 0;
            break;
        case 0:
            currentNode->bfactor = 0;
            lChild->bfactor = 0;
            break;
        case 1:
            currentNode->bfactor = 0;
            lChild->bfactor = -1;
            break;
        }
        lChild_rChild->bfactor = 0;
        rotateToLeft(currentNode->lLink);
        rotateToRight(currentNode);
        break;
    }
}

template <class t>
void AVLTree<t>::balanceFromRight(BinaryNode<t> *&currentNode)
{
    BinaryNode<t> *rChild;
    BinaryNode<t> *rChild_lChild;
    rChild = currentNode->rLink;
    switch (rChild->bfactor)
    {
    case 0:
    case 1:
        currentNode->bfactor = 0;
        rChild->bfactor = 0;
        rotateToLeft(currentNode);
        break;
    case -1:
        rChild_lChild = rChild->lLink;
        switch (rChild_lChild->bfactor)
        {
        case -1:
            currentNode->bfactor = 0;
            rChild->bfactor = 1;
            break;
        case 0:
            currentNode->bfactor = 0;
            rChild->bfactor = 0;
            break;
        case 1:
            currentNode->bfactor = -1;
            rChild->bfactor = 0;
            break;
        }
        rChild_lChild->bfactor = 0;
        rotateToRight(currentNode->rLink);
        rotateToLeft(currentNode);
        break;
    }
}

template <class t>
void AVLTree<t>::rotateToLeft(BinaryNode<t> *&currentNode)
{
    BinaryNode<t> *newRootNode;
    if (currentNode == nullptr || currentNode->rLink == nullptr)
    {
        throw std::out_of_range("Cannot rotate empty node.");
    }
    newRootNode = currentNode->rLink;
    currentNode->rLink = newRootNode->lLink;
    newRootNode->lLink = currentNode;
    currentNode = newRootNode;
}

template <class t>
void AVLTree<t>::rotateToRight(BinaryNode<t> *&currentNode)
{
    BinaryNode<t> *newRootNode;
    if (currentNode == nullptr || currentNode->lLink == nullptr)
    {
        throw std::out_of_range("Cannot rotate empty node.");
    }
    newRootNode = currentNode->lLink;
    currentNode->lLink = newRootNode->rLink;
    newRootNode->rLink = currentNode;
    currentNode = newRootNode;
}

template <class t>
void AVLTree<t>::insertIntoAVL(BinaryNode<t> *&currentNode, BinaryNode<t> *newNode, bool &isTaller, Iterator &it)
{
    if (currentNode == nullptr)
    {
        currentNode = newNode;
        isTaller = true;
        it = Iterator(currentNode, false);
    }
    else
    {
        int compareValue = this->compare(newNode->data, currentNode->data);
        if (compareValue == 0)
        {
            throw std::invalid_argument("No Duplicates Allowed");
        }
        else if (compareValue == -1)
        {
            insertIntoAVL(currentNode->lLink, newNode, isTaller, it);
            if (isTaller)
            {
                switch (currentNode->bfactor)
                {
                case -1:
                    balanceFromLeft(currentNode);
                    isTaller = false;
                    break;
                case 0:
                    currentNode->bfactor = -1;
                    isTaller = true;
                    break;
                case 1:
                    currentNode->bfactor = 0;
                    isTaller = false;
                }
            }
        }
        else
        {
            insertIntoAVL(currentNode->rLink, newNode, isTaller, it);
            if (isTaller)
            {
                switch (currentNode->bfactor)
                {
                case -1:
                    currentNode->bfactor = 0;
                    isTaller = false;
                    break;
                case 0:
                    currentNode->bfactor = 1;
                    isTaller = true;
                    break;
                case 1:
                    balanceFromRight(currentNode);
                    isTaller = false;
                    break;
                }
            }
        }
    }
}

template <class t>
AVLTree<t>::Iterator AVLTree<t>::find(const t &searchItem, BinaryNode<t> *currentNode) const
{
    if (currentNode == nullptr)
    {
        return AVLTree<t>::Iterator(); // empty iterator because we didn't find it
    }
    int compareValue = this->compare(searchItem, currentNode->data);
    if (compareValue == 0)
    {
        return AVLTree<t>::Iterator(currentNode, false);
    }
    else if (compareValue == 1)
    {
        return find(searchItem, currentNode->rLink);
    }
    else
    {
        return find(searchItem, currentNode->lLink);
    }
}

template <class t>
int AVLTree<t>::calculateBalance(BinaryNode<t> *currentNode)
{
    if (currentNode == nullptr)
        return 0;
    calculateBalance(currentNode->lLink);
    calculateBalance(currentNode->rLink);
    currentNode->bfactor = this->height(currentNode->rLink) - this->height(currentNode->lLink);
    return currentNode->bfactor;
}

template <class t>
bool AVLTree<t>::isBalanced(BinaryNode<t> *currentNode)
{
    if (currentNode == nullptr)
    {
        return true;
    }
    bool balance = !(currentNode->bfactor > 1 || currentNode->bfactor < -1);
    return balance && isBalanced(currentNode->lLink) && isBalanced(currentNode->rLink);
}

template <class t>
void AVLTree<t>::balanceTree(BinaryNode<t> *&currentNode)
{
    if (currentNode != nullptr)
    {
        int balance = this->height(currentNode->rLink) - this->height(currentNode->lLink);
        if (balance > 1)
        {
            balanceFromRight(currentNode);
        }
        else if (balance < -1)
        {
            balanceFromLeft(currentNode);
        }
    }
}

template <class t>
void AVLTree<t>::deleteFromTree(BinaryNode<t> *&currentNode, const t &key)
{
    BinaryNode<t> *temp;
    BinaryNode<t> *replace;
    if (currentNode == nullptr)
    {
        throw std::invalid_argument("The item to be deleted is not in the tree.");
    }
    int compareValue = this->compare(key, currentNode->data);
    if (compareValue == -1)
    {
        deleteFromTree(currentNode->lLink, key);
    }
    else if (compareValue == 1)
    {
        deleteFromTree(currentNode->rLink, key);
    }
    else
    {
        temp = currentNode;
        if (currentNode->lLink == nullptr && currentNode->rLink == nullptr)
        {
            currentNode = nullptr;
            delete temp;
        }
        else if (currentNode->lLink == nullptr)
        {
            currentNode = currentNode->rLink;
            delete temp;
        }
        else if (currentNode->rLink == nullptr)
        {
            currentNode = currentNode->lLink;
            delete temp;
        }
        else
        {
            temp = findMin(currentNode->rLink);
            t tmp = currentNode->data;
            currentNode->data = temp->data;
            temp->data = tmp;
            deleteFromTree(currentNode->rLink, key);
        }
    }
    balanceTree(currentNode);
    calculateBalance(currentNode);
}

template <class t>
BinaryNode<t> *AVLTree<t>::findMin(BinaryNode<t> *node) const
{
    BinaryNode<t> *min = node;
    while (min && min->lLink != nullptr) // pointer as a bool is false when nullptr
    {
        min = min->lLink;
    }
    return min;
}

template <class t>
AVLTree<t>::Iterator::Iterator(BinaryNode<t> *currentNode, bool pushSmaller)
{
    pushLeftNodes(currentNode, pushSmaller);
}

template <class t>
bool AVLTree<t>::Iterator::hasNext()
{
    return !nodeStack.isEmptyStack();
}

template <class t>
AVLTree<t>::Iterator AVLTree<t>::Iterator::operator++()
{
    if (!nodeStack.isEmptyStack())
    {

        BinaryNode<t> *node = nodeStack.pop();
        if (node->rLink != nullptr)
        {
            pushLeftNodes(node->rLink, true);
        }
    }
    return *this;
}

template <class t>
t &AVLTree<t>::Iterator::operator*()
{
    if (nodeStack.isEmptyStack())
    {
        throw std::out_of_range("No more elements");
    }
    BinaryNode<t> *node = nodeStack.top();
    return node->data;
}

template <class t>
bool AVLTree<t>::Iterator::operator==(const Iterator &other) const
{
    if (nodeStack.isEmptyStack() && other.nodeStack.isEmptyStack()) // if both are empty
    {
        return true;
    }
    else if (nodeStack.isEmptyStack() || other.nodeStack.isEmptyStack()) // if one is empty but not both (else)
    {
        return false;
    }
    BinaryNode<t> *myNode = nodeStack.peek();
    BinaryNode<t> *theirNode = other.nodeStack.peek();
    return myNode == theirNode; // comparing pointer addresses
}

template <class t>
bool AVLTree<t>::Iterator::operator!=(const Iterator &other) const
{
    return !(*this == other);
}

template <class t>
void AVLTree<t>::Iterator::pushLeftNodes(BinaryNode<t> *node, bool pushSmaller)
{
    if (node != nullptr)
    {
        nodeStack.push(node);
        node = node->lLink;
    }
    if (pushSmaller) // layer smaller nodes on top
    {
        while (node != nullptr)
        {
            nodeStack.push(node);
            node = node->lLink;
        }
    }
}
#endif