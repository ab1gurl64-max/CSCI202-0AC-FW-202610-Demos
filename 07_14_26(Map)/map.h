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
        Iterator(typename AVLTree<Pair<k, v>>::Iterator it);
        Iterator operator++();
        Pair<k, v> operator*();
        bool operator==(const Iterator oth) const;
        bool operator!=(const Iterator oth) const;

    private:
        AVLTree<Pair<k, v>>::Iterator it;
    };

    Pair<bool, Iterator> insert(const k &, const v &);
    Iterator begin() { return Iterator(tree.begin()); };
    Iterator end() { return Iterator(tree.end()); };
    bool deleteItem(const k &key);
    std::string preorder();

protected:
    AVLTree<Pair<k, v>> tree;
};

#endif

template <class k, class v>
inline Map<k, v>::Map()
{
}

template <class k, class v>
inline v Map<k, v>::at(const k &key) const
{
    Pair<k, v> pairForComp(key);
    typename AVLTree<Pair<k, v>>::Iterator item = tree.find(pairForComp);
    if (item == tree.end())
    {
        throw std::out_of_range("The item is not in the map.");
    }
    return (*item).getValue();
}

template <class k, class v>
inline v &Map<k, v>::operator[](const k &key)
{
    Pair<k, v> pairforComp(key);
    typename AVLTree<Pair<k, v>>::Iterator item = tree.find(pairforComp);
    if (item == tree.end())
    {
        typename AVLTree<Pair<k, v>>::Iterator it = tree.insertAVL(pairforComp);
        return (*it).getValue();
    }
    return (*item).getValue();
}

template <class k, class v>
inline Pair<bool, typename Map<k, v>::Iterator> Map<k, v>::insert(const k &key, const v &value)
{
    bool insert = true;
    Iterator it(tree.end());
    Pair<k, v> p(key, value);
    try
    {
        it = Iterator(tree.insertAVL(p));
    }
    catch (std::invalid_argument e)
    {
        insert = false;
        it = Iterator(tree.find(p));
    }
    return Pair<bool, Iterator>(insert, it);
}

template <class k, class v>
inline bool Map<k, v>::deleteItem(const k &key)
{
    Pair<k, v> deleteItem(key);
    tree.deleteNode(deleteItem);
    return tree.isBalanced();
}

template <class k, class v>
inline std::string Map<k, v>::preorder()
{
    return tree.preorderTraversal();
}

template <class k, class v>
inline Map<k, v>::Iterator::Iterator(typename AVLTree<Pair<k, v>>::Iterator it)
{
    this->it = it;
}

template <class k, class v>
Pair<k, v> Map<k, v>::Iterator::operator*()
{
    return *it;
}
