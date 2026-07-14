#ifndef MAP_H
#define MAP_H

#include "pair.h"
#include "AVLTree.h"

template <class k, class v>
class Map
{
public:
    Map();
    v at(const k &) const;
    v &operator[](const k &);
    class Iterator
    {
    public:
        Iterator(AVLTree<Pair<k, v>>::Iterator it);
        Iterator operator++();
        Pair<k, v> operator*();
        bool operator==(const Iterator oth) const;
        bool operator!=(const Iterator oth) const;

    private:
        AVLTree<Pair<k, v>>::Iterator it;
    };

    pair<bool, Iterator> insert(const k &, const v &);
    Iterator begin() { return Iterator(tree.begin()); };
    Iterator end() { return Iterator(tree.end()); };
    bool deleteItem(const k &key);
    std::string preorder();

protected:
    AVLTree<Pair<k, v>> tree;
};

#endif