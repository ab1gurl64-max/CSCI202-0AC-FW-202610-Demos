#ifndef NODE_H
#define NODE_H

template <class t>
struct BinaryNode
{
    t data;
    BinaryNode<t> *lLink;
    BinaryNode<t> *rLink;
    BinaryNode();
    BinaryNode(t data);
};

template <class t>
BinaryNode<t>::BinaryNode()
{
    lLink = nullptr;
    rLink = nullptr;
}
template <class t>
BinaryNode<t>::BinaryNode(t d) : data(d)
{
    rLink = nullptr;
    lLink = nullptr;
}
#endif