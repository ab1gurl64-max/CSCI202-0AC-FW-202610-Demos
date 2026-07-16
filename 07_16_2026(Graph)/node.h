#ifndef NODE_H
#define NODE_H

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