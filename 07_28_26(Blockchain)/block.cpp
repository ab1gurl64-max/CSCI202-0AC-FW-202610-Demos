#include "block.h"

/* Block::Block(int blockNum, std::string data, size_t prevHash) : blockNum(blockNum), prevHash(prevHash), data(data)
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
} */

Block::Block(int blockNum, std::string data, const unsigned char *prevHash) : blockNum(blockNum), data(data)
{
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        this->prevHash[i] = prevHash[i];
    }
    this->nonce = time(NULL);
    currentHash = calculateHash();
}

Block::Block(const Block &other)
{
    copyBlock(other);
}

bool Block::validateHash()
{
    bool valid = true;
    unsigned char *hash = calculateHash();
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        if (currentHash[i] != hash[i])
        {
            valid = false;
            break;
        }
    }
    delete[] hash;
    return valid;
}

Block::~Block()
{
    delete[] currentHash;
}

unsigned char *Block::calculateHash()
{
    std::string phash(prevHash, prevHash + sizeof(prevHash) / sizeof(prevHash[0]));
    std::string hashString = std::to_string(blockNum) + std::to_string(nonce) + data + phash;
    unsigned char *hash = new unsigned char[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)hashString.c_str(), hashString.length(), hash);
    return hash;
}

void Block::copyBlock(const Block &other)
{
    this->blockNum = other.blockNum;
    this->nonce = other.nonce;
    this->data = other.data;
    currentHash = new unsigned char[SHA256_DIGEST_LENGTH];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        this->prevHash[i] = other.prevHash[i];
        this->currentHash[i] = other.currentHash[i];
    }
}
