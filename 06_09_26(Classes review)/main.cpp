#include "donut.h"
#include <iostream>

int main()
{
    Donut::toppingType t = Donut::BACON;
    icingType i = CHOCOLATEICING;
    drizzleType d = drizzleType::CARAMELDRIZZLE;
    Donut don("Maple", "Reeses Pieces", "Special");
    std::cout << don << std::endl;
    return 0;
}