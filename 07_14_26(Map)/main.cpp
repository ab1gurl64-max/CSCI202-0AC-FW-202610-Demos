
#include "map.h"
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
    std::ifstream name("names.txt");
    for (int i = 1; !name.eof(); i++)
    {
        std::string in;
        std::getline(name >> std::ws, in);
        hobbits.insert(i, in);
    }
    for (auto it = hobbits.begin(); it != hobbits.end(); ++it)
    {
        Pair<int, std::string> p = *it;
        std::cout << p.getValue() << std::endl;
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
            break;
        }
        if (ind == -2)
        {
            std::cout << hobbits.preorder() << std::endl;
            for (auto it = hobbits.begin(); it != hobbits.end(); ++it)
            {
                Pair<int, std::string> p = *it;
                std::cout << p.getValue() << std::endl;
            }
        }
        else
        {
            try
            {

                std::cout << "Deleting " << hobbits.at(ind) << "\n";
                std::cout << hobbits.deleteItem(ind)
                          << std::endl;
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