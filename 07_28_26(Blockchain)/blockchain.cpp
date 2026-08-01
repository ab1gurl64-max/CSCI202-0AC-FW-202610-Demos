#include "blockchain.h"
#include <cstring>

BlockChain::BlockChain()
{
    
    nextBlock = 1;

    //no previous hash, array full of 0 
    unsigned char hash[SHA256_DIGEST_LENGTH] = {0};

    //create 1st block
    Block genesis(nextBlock, "Genesis Block", hash);

    //pushed onto blockchain
    chain.push(genesis);

    
    nextBlock++;
}

void BlockChain::addMessage(const std::string& message)
{
    //new block, previous hash from block, on top of the stack
    Block newBlock(nextBlock, message, chain.peek().getHash());

    chain.push(newBlock);

    nextBlock++;
}

bool BlockChain::verify()
{
    //making a copy
    LinkedStack<Block> temp = chain;

    //go till every block is checked
    while (!temp.isEmptyStack())
    {
        //newest block
        Block current = temp.pop();

        // Verify the block's own hash
        if (!current.validateHash())
        {
            return false; //hash don't match
        }
    }

    return true;
}

