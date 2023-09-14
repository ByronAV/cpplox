#include "common.hpp"
#include "chunk.hpp"

int main(int argc, const char* argv[]) {
    Chunk chunk;
    chunk.writeChunk(chunk, OP_RETURN);
    return 0;
}