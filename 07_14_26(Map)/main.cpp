#include "binarySearchTree.h"
#include "AVLTree.h"
#include "pair.h"
#include <iostream>
#include <random>
#include <chrono>

// link to spring demos (alternate map and pair)
// https://github.com/CSCI202FW/CSCI202-0AC-FW-202530-Demos

int main()
{

    std::random_device rd;
    std::uniform_int_distribution<int> distribution(5, 100);
    std::default_random_engine generator(rd()); // alternatively use code in block below
    /*auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
      std::default_random_engine generator(static_cast<unsigned int>(seed));
    */
    int num = distribution(generator);
    Pair<int, int> nums(num, num);
    Pair<int, int> nums2(num);
}