#include <iostream>
#include <string>
#include <limits>
#include "donut.h"
#include "order.h"

// screenshot of your group on the people page in IvyLearn
void codeGradeLoopFix(std::string errLocation); // fixes infinite loops
void resetStream();
std::string getIcing();
std::string getTopping(std::string);
std::string getDrizzle();
void icingPrompt();
void drizzlePrompt();
void toppingPrompt(std::string);

void referencePointers(Donut *&, Donut *);

int main()
{
    std::string icing = getIcing();
    std::string topping = getTopping(icing);
    std::string drizzle = getDrizzle();

    Donut *pointer1;
    Donut myDonut(icing, topping, drizzle);
    pointer1 = new Donut();
    referencePointers(pointer1, &myDonut);
    Order donutOrder;
    donutOrder + myDonut;
    donutOrder + *pointer1;
    std::cout << donutOrder;

    return 0;
}

void codeGradeLoopFix(std::string errLocation)
{
    if (std::cin.eof())
    {
        std::cout << "There was a problem and there is no more input! @" + errLocation << std::endl;
        throw std::invalid_argument(errLocation);
    }
}

std::string getIcing()
{
    std::string ice;
    icingPrompt();
    std::cin >> std::ws;
    std::getline(std::cin, ice);
    std::string icingLower = ice;
    std::transform(icingLower.begin(), icingLower.end(), icingLower.begin(), ::tolower);
    while (!Donut::strToice.count(icingLower))
    {
        codeGradeLoopFix("main.cpp::getIcing()");
        // resetStream();
        std::cout << ice << " is not a valid choice. " << std::endl;
        icingPrompt();
        std::cin >> std::ws;
        std::getline(std::cin, ice);
        icingLower = ice;
        std::transform(icingLower.begin(), icingLower.end(), icingLower.begin(), ::tolower);
    }
    return ice;
}

std::string getTopping(std::string icing)
{
    std::string top;
    std::transform(icing.begin(), icing.end(), icing.begin(), ::tolower);
    toppingPrompt(icing);
    std::cin >> std::ws;
    std::getline(std::cin, top);
    std::string topCopy = top;
    std::transform(topCopy.begin(), topCopy.end(), topCopy.begin(), ::tolower);
    if (icing == "none")
    {
        while (topCopy != "cinnamon sugar" && topCopy != "powdered sugar" && topCopy != "none")
        {
            codeGradeLoopFix("main.cpp::getTopping(\"none\")");
            std::cout << top << "is not valid for icing " << icing << std::endl;
            toppingPrompt(icing);
            std::getline(std::cin, top);
            topCopy = top;
            std::transform(topCopy.begin(), topCopy.end(), topCopy.begin(), ::tolower);
        }
    }
    else
    {
        while (!Donut::strToTop.count(topCopy))
        {
            codeGradeLoopFix("main.cpp::getTopping()");
            std::cout << top << " is not a valid topping." << std::endl;
            toppingPrompt(icing);
            std::getline(std::cin, top);
            topCopy = top;
            std::transform(topCopy.begin(), topCopy.end(), topCopy.begin(), ::tolower);
        }
    }
    return top;
}

void icingPrompt()
{
    std::cout << "Choose your icing from the choices below: " << std::endl;
    for (std::map<Donut::icingType, std::string>::const_iterator it = Donut::iceToStr.begin(); it != Donut::iceToStr.end(); ++it)
    {
        std::cout << it->second << std::endl;
    }
}

std::string getDrizzle()
{
    std::string drizzle;
    drizzlePrompt();
    std::cin >> std::ws;
    std::getline(std::cin, drizzle);
    std::string drizzleLower = drizzle;
    std::transform(drizzleLower.begin(), drizzleLower.end(), drizzleLower.begin(), ::tolower);
    while (!Donut::strToDrizzle.count(drizzleLower))
    {
        codeGradeLoopFix("main.cpp::getDrizzle()");
        std::cout << drizzle << " is not a valid drizzle choice." << std::endl;
        drizzlePrompt();
        std::cin >> std::ws;
        std::getline(std::cin, drizzle);
        drizzleLower = drizzle;
        std::transform(drizzleLower.begin(), drizzleLower.end(), drizzleLower.begin(), ::tolower);
    }
    return drizzle;
}

void drizzlePrompt()
{
    std::cout << "Choose your drizzle from the choices below:" << std::endl;
    for (std::map<Donut::drizzleType, std::string>::const_iterator it = Donut::drizzleToStr.begin(); it != Donut::drizzleToStr.end(); ++it)
    {
        std::cout << it->second << std::endl;
    }
}

void toppingPrompt(std::string icing)
{
    std::cout << "Choose your topping from the choices below:" << std::endl;
    if (icing == "none")
    {
        std::cout << "Cinnamon Sugar" << std::endl;
        std::cout << "Powdered Sugar" << std::endl;
        std::cout << "None" << std::endl;
    }
    else
    {
        for (auto it = Donut::topToStr.begin(); it != Donut::topToStr.end(); ++it)
        {
            std::cout << it->second << std::endl;
        }
    }
}

void referencePointers(Donut *&p, Donut *d)
{
    Donut *temp = p;
    p = d;
    d->setTopping("chocolate chips");

    d = temp;
    // delete temp;
}
