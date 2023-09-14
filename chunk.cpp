#include "chunk.hpp"

#define GROW_CAPACITY(capacity) \
        ((capacity) < 8 ? 8 : (capacity) * 2)

void Chunk::writeChunk(uint8_t byte)
{
    if (this->code.capacity() < this->code.size() + 1)
    {
        this->code.reserve(GROW_CAPACITY(this->code.capacity()));
    }
    this->code.push_back(byte);
}