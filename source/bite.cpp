#include "bite.h"

StackElement_t* TextConvertToBite(const char* filename) {

    BufferBin struct_buffer = CreateBufferBinary(filename);

    StackElement_t* buffer = struct_buffer.buff;
    assert(buffer);

    return buffer;
}