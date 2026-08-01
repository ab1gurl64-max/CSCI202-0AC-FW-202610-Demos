#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include "linkedStack.h"
#include <iostream>

class BlockChain
{
private:
//a stack that will store every block 
//new always on top
    LinkedStack<Block> chain;
    int nextBlock;

public:
    BlockChain();

 
    void addMessage(const std::string& message);

    bool verify();

  
};

#endif