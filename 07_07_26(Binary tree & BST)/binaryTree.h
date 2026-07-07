#ifndef BINARY_H
#define BINARY_H

#include <sstream>
#include "node.h"

template <class t>
class BinaryTree
{
public:
    BinaryTree();
    BinaryTree(const BinaryTree<t> &treeToCopy);
    const BinaryTree &operator=(const BinaryTree<t> &treeToCopy);
    ~BinaryTree();
    std::string inorderTraversal() const;
    std::string preorderTraversal() const;
    std::string postorderTraversal() const;

protected:
    BinaryNode<t> *root;

private:
    void copyTree(BinaryNode<t> *&myTreeNode, BinaryNode<t> *treeToCopyNode);
    void inorder(BinaryNode<t> *currentNode, std::ostringstream &out) const;
    void preorder(BinaryNode<t> *currentNode, std::ostringstream &out) const;
    void postorder(BinaryNode<t> *currentNode, std::ostringstream &out) const;
};
#endif

template <class t>
inline std::string BinaryTree<t>::inorderTraversal() const
{
    std::ostringstream out;
    inorder(root, out);
    return out.str();
}

template <class t>
inline void BinaryTree<t>::inorder(BinaryNode<t> *currentNode, std::ostringstream &out) const
{
    /*  Traverse the left subtree
        Visit the node
        Traverse the right subtree */
    if (currentNode != nullptr)
    {
        inorder(currentNode->lLink, out);
        out << currentNode->data << " ";
        inorder(currentNode->rLink, out);
    }
}
