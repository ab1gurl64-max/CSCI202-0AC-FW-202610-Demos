#ifndef SEARCH_H
#define SEARCH_H

#include <fstream>
#include "unorderedLinkedList.h"

template <class t>
LinkedListIterator<t> seqSearch(UnorderedLinkedList<t> &list, const t &item, int &count)
{
    count = 0;
    bool found = false;
    LinkedListIterator<t> itRet;
    for (LinkedListIterator<t> it = list.begin(); it != list.end() && !found; ++it)
    {
        count++;
        if (*(*it) == item) //(*it) gives us a t*
        {
            found = true;
            itRet = it;
        }
    }
    return itRet;
}

//======================== Sort Algorithms ===========================
template <class t>
void bubbleSort(UnorderedLinkedList<t> &list)
{
    for (int iteration = 1; iteration < list.length(); iteration++)
    {
        LinkedListIterator<t> it1;
        for (LinkedListIterator<t> it = it1 = list.begin(); ++it1 != list.end(); ++it)
        {
            if (*(*it) > *(*it1))
            {
                swap(it, it1);
            }
        }
    }
}

template <class t>
void swap(LinkedListIterator<t> &first, LinkedListIterator<t> &second)
{
    t *temp = *first;
    *first = *second;
    *second = temp;
}

template <class t>
LinkedListIterator<t> findSmallest(UnorderedLinkedList<t> &list, LinkedListIterator<t> &begin)
{
    t smallest = *(*begin);
    LinkedListIterator<t> ret = begin;
    LinkedListIterator<t> it = begin;
    for (++it; it != list.end(); ++it)
    {
        if (*(*it) < smallest)
        {
            smallest = *(*it);
            ret = it;
        }
    }
    return ret;
}

template <class t>
void selectionSort(UnorderedLinkedList<t> &list)
{
    LinkedListIterator<t> unsort = list.begin();
    int i = 1;
    for (unsort; unsort != list.end(); ++unsort)
    {
        LinkedListIterator<t> smallest = findSmallest(list, unsort);
        if (smallest != unsort)
        {
            swap(unsort, smallest);
        }
        i++;
    }
}

template <class t>
void insertionSort(t list[], int length)
{
    for (int firstOutOfOrder = 1; firstOutOfOrder < length; ++firstOutOfOrder)
    {
        t temp = list[firstOutOfOrder];
        int location = firstOutOfOrder;
        while (location > 0 && list[location - 1] > temp)
        {
            list[location] = list[location - 1];
            location--;
        }
        list[location] = temp;
    }
}

#endif