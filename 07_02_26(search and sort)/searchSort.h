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

template <class t>
int partition(t list[], int low, int high, int (*comp)(t &, t &))
{
    t pivot = list[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    {
        t item = list[j];
        if (comp(item, pivot) < 0)
        {
            i++;
            list[j] = list[i];
            list[i] = item;
        }
    }
    i++;
    t temp = list[i];
    list[i] = list[high];
    list[high] = temp;
    return i;
}

template <class t>
void quickSort(t list[], int low, int high, int (*comp)(t &, t &))
{
    if (low < high)
    {
        int pi = partition(list, low, high, comp);
        quickSort(list, low, pi - 1, comp);
        quickSort(list, pi + 1, high, comp);
    }
}

template <class t>
void merge(t array[], int left, int mid, int right)
{
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    t *leftArray = new t[leftSize];
    t *rightArray = new t[rightSize];
    for (int i = 0; i < leftSize; i++)
    {
        leftArray[i] = array[left + i];
    }
    for (int i = 0; i < rightSize; i++)
    {
        rightArray[i] = array[mid + 1 + i];
    }
    int leftIndex = 0;
    int rightIndex = 0;
    int mergeIndex = left;
    while (leftIndex < leftSize && rightIndex < rightSize)
    {
        if (leftArray[leftIndex] <= rightArray[rightIndex])
        {
            array[mergeIndex] = leftArray[leftIndex];
            leftIndex++;
        }
        else
        {
            array[mergeIndex] = rightArray[rightIndex];
            rightIndex++;
        }
        mergeIndex++;
    }
    while (leftIndex < leftSize)
    {
        array[mergeIndex++] = leftArray[leftIndex++];
    }
    while (rightIndex < rightSize)
    {
        array[mergeIndex++] = rightArray[rightIndex++];
    }
    delete[] leftArray;
    delete[] rightArray;
}

template <class t>
void mergeSort(t array[], int begin, int end)
{
    if (begin >= end)
    {
        return;
    }
    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

#endif