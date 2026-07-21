
#include "map.h"
#include "donut.h"
#include <iostream>
#include <random>
#include <chrono>
#include <string>
#include <iomanip>
#include <fstream>
// link to spring demos (alternate map and pair)
// https://github.com/CSCI202FW/CSCI202-0AC-FW-202530-Demos

// M06 A lab
//  write a new main to test the map. use any key value pair you like (insert change and delete items)

int main()
{
    Map<int, std::string> hobbits;
    Map<std::string, Donut *> hobbitDonuts;

    //new map testing 
    Map<int, std::string> myMap; 

    //inserting item 
    myMap.insert(1,"Apple");
    myMap.insert(2,"Banana");
    myMap.insert(3,"Orange");
    myMap.insert(4,"Grape");

     for (auto it = myMap.begin(); it != myMap.end(); ++it)
    {
        Pair<int, std::string> p = *it;
        std::cout << p.getKey() << " --- " << p.getVaule() << std::endl;
    }

    //changing items 
    myMap[2] = "Strawberry";
    std:cout << myMap[2] << std::endl;

    //adding item 
    myMap[5] = "watermelon"
    std::cout << myMap[5] << std::endl;

    myMap.deleteItem(3);

    for (auto it = myMap.begin(); it != myMap.end(); ++it)
    {
        Pair<int, std::string> p = *it;
        std::cout << p.getKey() << " --- " << p.getVaule() << std::endl;
    }

    std::cout << "Preorder traversal:" << std::endl;
    std::cout << myMap.preorder() << std::endl;
    

    std::random_device rd;
    std::uniform_int_distribution<int> icingDist(0, static_cast<int>(icingType::NOICE));
    std::uniform_int_distribution<int> toppingDist(0, static_cast<int>(Donut::toppingType::NOTOP));
    std::uniform_int_distribution<int> drizzleDist(0, static_cast<int>(drizzleType::NODRIZZLE));
    std::default_random_engine generator(rd()); // alternatively use code in block below
    /*auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
      std::default_random_engine generator(static_cast<unsigned int>(seed));
    */
    // int num = distribution(generator);

    std::ifstream name("names.txt");
    for (int i = 1; !name.eof(); i++)
    {
        std::string in;
        std::getline(name >> std::ws, in);
        hobbits.insert(i, in);
        hobbitDonuts.insert(in, new Donut(Donut::iceToStr.at(static_cast<icingType>(icingDist(generator))), Donut::topToStr.at(static_cast<Donut::toppingType>(toppingDist(generator))), Donut::drizzleToStr.at(static_cast<drizzleType>(drizzleDist(generator)))));
    }
    for (auto it = hobbits.begin(); it != hobbits.end(); ++it)
    {
        Pair<int, std::string> p = *it;
        std::cout << p.getValue() << " --- " << *hobbitDonuts.at(p.getValue()) << std::endl;
    }

    std::cout << std::endl
              << std::endl;
    std::cout << hobbits[6] << std::endl;
    std::cout << std::setw(40) << std::setfill('-') << "-" << std::endl;
    hobbits[1] = "Tasha Oakbottom";
    std::cout << hobbits[1] << std::endl;
    hobbits[15] = "Brianna Button";
    std::cout
        << std::setw(40) << std::setfill('-') << "-" << std::endl;
    for (auto it = hobbits.begin(); it != hobbits.end(); ++it)
    {
        Pair<int, std::string> p = *it;
        std::cout << p.getValue() << std::endl;
    }
    std::cout << std::endl
              << std::endl;
    std::cout << "\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\nBegin Delete test:\n\n";
    std::cout << "Notes about the delete debugger:\nType -1 to exit\nType -2 to print map\n";
    while (true)
    {
        std::cout << "\n  *** \n";
        int ind;
        std::cout << "Enter index of node to be deleted: ";
        std::cin >> ind;
        if (ind == -1)
        {
            for (auto it = hobbitDonuts.begin(); it != hobbitDonuts.end(); ++it)
            {
                std::cout << it->getKey() << " --- " << *it->getValue() << std::endl;
                delete it->getValue();
            }
            break;
        }
        if (ind == -2)
        {
            std::cout << hobbits.preorder() << std::endl;
            for (auto it = hobbits.begin(); it != hobbits.end(); ++it)
            {
                Pair<int, std::string> p = *it;

                std::cout << p.getValue() << " --- ";
                try
                {
                    std::cout << *hobbitDonuts.at(p.getValue()) << std::endl;
                }
                catch (std::out_of_range e)
                {
                    std::cout << std::endl;
                }
            }
        }
        else
        {
            try
            {

                std::cout << "Deleting " << hobbits.at(ind) << "\n";
                std::string n = hobbits.deleteItem(ind);
                Donut *d = hobbitDonuts.deleteItem(n);
                std::cout << *d << " ";
                std::cout << n
                          << std::endl;
                delete d;
            }
            catch (const std::out_of_range &e)
            {
                std::cout << e.what() << '\n';
            }
        }
    }

    /* std::random_device rd;
    std::uniform_int_distribution<int> distribution(5, 100);
    std::default_random_engine generator(rd()); // alternatively use code in block below
    /*auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
      std::default_random_engine generator(static_cast<unsigned int>(seed));
    */
    /*int num = distribution(generator);
    Map<int, int> numMap;
    numMap.insert(num, 7);
    std::cout << numMap.at(num) << std::endl;
    numMap[num] = 10;
    std::cout << numMap[num] << std::endl;
    numMap[0] = 12;
    std::cout << numMap[0] << std::endl; */
}
