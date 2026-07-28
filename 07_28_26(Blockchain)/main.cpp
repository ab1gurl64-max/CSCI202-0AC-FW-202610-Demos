#include "block.h"
#include "linkedStack.h"

// M08 lab create a block chain class using your choice of linkedQueue, linkedStack, or unorderedLinkedList
// have a method to add a message
// have a method to go through and verify the blocks
// use the sha256 block

int main()
{
    std::string message = "Space star ordering is based on the twin scientific principles of star-maths and wishy thinking.";
    std::string message2 = "Prepare to put mustard on those words, for you will soon be consuming them along with this slice of humble pie that comes direct from the oven of shame, set at gas mark 'egg on your face'.";
    std::string message3 = "prepare to put mustard on those words, for you will soon be consuming them along with this slice of humble pie that comes direct from the oven of shame, set at gas mark 'egg on your face'.";
    LinkedStack<Block> blockChain;
    unsigned char hash[SHA256_DIGEST_LENGTH] = {0};
    Block genesis(1, "Genesis Block", hash);
    blockChain.push(genesis);
    Block block1(2, message, blockChain.peek().getHash());
    blockChain.push(block1);

    return 0;
}
// 17374467124495395714
// 17374467124495395714
// 7500794420939243409