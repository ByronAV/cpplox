#ifndef cpplox_chunk_h
#define cpplox_chunk_h

#include <vector>

#include "common.hpp"

enum class OpCode {
    OP_RETURN // Return from the current function
};

class Chunk {
  public:
    Chunk() = default;
    void writeChunk(uint8_t byte);
    std::vector<uint8_t> code; // Instructions
};

#endif