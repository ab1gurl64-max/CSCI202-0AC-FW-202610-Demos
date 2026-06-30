#ifndef ORDER_H
#define ORDER_H
#include "donut.h"
#include <iostream>

class Order
{
public:
    Order();
    Order(const Order &);
    const Order &operator=(const Order &);
    void operator+(const Donut &);
    int donutCount() const;
    friend std::ostream &operator<<(std::ostream &, const Order &);
    ~Order();

private:
    void copyOrder(const Order &);
    void destroyList();
    Donut *donutList;
    int numDonuts;
};

#endif