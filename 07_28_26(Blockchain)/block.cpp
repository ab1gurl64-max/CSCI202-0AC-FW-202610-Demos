#include "block.h"

Block::Block(int blockNum, std::string data, size_t prevHash) : blockNum(blockNum), prevHash(prevHash), data(data)
{
    this->nonce = time(NULL);
    currentHash = calculateHash();
}

bool Block::validateHash()
{
    // bool valid = true;
    size_t hash = calculateHash();

    return hash == currentHash;
}

size_t Block::calculateHash()
{
    std::hash<std::string> str_hash;
    std::string hashString = std::to_string(blockNum) + std::to_string(nonce) + data + std::to_string(prevHash);
    return str_hash(hashString);
}
