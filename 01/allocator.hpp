#ifndef ALLOCATOR
#define ALLOCATOR


#include <cstddef>

class Allocator
{
	char *data;
	size_t offset;
	size_t max_size;
public:
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator();
    Allocator();
};

#endif
