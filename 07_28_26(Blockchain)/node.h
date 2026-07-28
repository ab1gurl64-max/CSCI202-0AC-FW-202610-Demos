#ifndef NODE_H
#define NODE_H

template <class t>
struct BinaryNode
{
    t data;
    BinaryNode<t> *lLink;
    BinaryNode<t> *rLink;
    int bfactor;

    BinaryNode();
    BinaryNode(t data);
};

template <class t>
BinaryNode<t>::BinaryNode()
{
    lLink = nullptr;
    rLink = nullptr;
    bfactor = 0;
}
template <class t>
BinaryNode<t>::BinaryNode(t d) : data(d)
{
    rLink = nullptr;
    lLink = nullptr;
    bfactor = 0;
}

template <class t>
struct node
{
    t data;
    node<t> *link;

    node(t data, node<t> *link = nullptr);
};

template <class t>
node<t>::node(t d, node<t> *link) : data(d)
{
    this->link = link;
}
#endif