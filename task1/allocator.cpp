#include <iostream>
#include "allocator.hpp"

using std::cin;
using std::cout;
using std::endl;

Allocator::~Allocator()
{
    delete [] data;
}

Allocator::Allocator()
{
    data = nullptr;
    offset = 0;
    max_size = 0;
}

void Allocator::makeAllocator(size_t maxSize)
{
    if (maxSize == 0)
        throw "Error!!! Not right maxSize";
    
    if (data == nullptr){
        data = new char [maxSize];
        max_size = maxSize;
        offset = 0;
    } else {
        delete [] data;
        data = new char [maxSize];
        offset = 0;
        max_size = maxSize;
    }
}

char* Allocator::alloc(size_t size)
{
    if (data == nullptr)
        throw "Error!!! makeAllocator not done yet";
    if (size == 0)
        throw "Error!!! Not right size";
    
    if (size + offset > max_size)
        return nullptr;
    else{
        offset += size;
        return data + offset - size;
    }
}

void Allocator::reset()
{
    offset = 0;
}
