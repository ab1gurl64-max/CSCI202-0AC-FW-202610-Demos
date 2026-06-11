#include "order.h"

Order::Order()
{
    donutList = nullptr;
    numDonuts = 0;
}
Order::Order(const Order &otherOrder)
{
    donutList = nullptr;
    numDonuts = 0;
    copyOrder(otherOrder);
}

const Order &Order::operator=(const Order &otherOrder)
{
    if (this != &otherOrder)
    {
        copyOrder(otherOrder);
    }
    return *this;
}

void Order::operator+(const Donut &d)
{
    numDonuts++;
    if (donutList == nullptr)
    {
        donutList = new Donut[numDonuts];
    }
    else
    {
        Donut *temp = donutList;
        donutList = new Donut[numDonuts];
        for (int i = 0; i < numDonuts - 1; i++)
        {
            donutList[i] = temp[i];
        }
        delete[] temp;
    }
    donutList[numDonuts - 1] = d;
}
Order::~Order()
{
    destroyList();
}

void Order::destroyList()
{
    delete[] donutList;
    donutList = nullptr;
}

void Order::copyOrder(const Order &otherOrder)
{
    if (this->donutList != nullptr) //*(this).
    {
        destroyList();
    }
    this->numDonuts = otherOrder.numDonuts;
    this->donutList = new Donut[this->numDonuts];
    for (int i = 0; i < this->numDonuts; i++)
    {
        donutList[i] = otherOrder.donutList[i];
    }
}

std::ostream &operator<<(std::ostream &out, const Order &o)
{
    for (int i = 0; i < o.numDonuts; i++)
    {
        out << o.donutList[i] << std::endl;
    }
    return out;
}
