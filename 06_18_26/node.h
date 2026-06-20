#ifndef NODE_H
#define NODE_H

template <class t>
struct node
{
    t *data;
    node<t> *link; // forward link
    node<t> *back; // backward link
    ~node()
    {
        delete data;
    }
};

template <class t>
struct node2
{
    t data;
    node2<t> *link;
    node2();
    node2(t data, node2<t> *link = nullptr);
};

template <class t>
node2<t>::node2()
{
    link = nullptr;
}

template <class t>
node2<t>::node2(t d, node2<t> *link) : data(d)
{
    this->link = link;
}
#endif