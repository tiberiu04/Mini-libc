// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size) {
    // Calling mmap to allocate memory, allowing to be readable, writable
    // ensuring the the memory is not backed by any file and the modifications
    // will not be visible to other processes
    void *mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    // Failure handling
    if (mem == MAP_FAILED)
        return NULL;
    if (mem_list_add(mem, size) == -1) {
        munmap(mem, size);
        return NULL;
    }

    return mem;
}

void *calloc(size_t nmemb, size_t size) {
	void *mem = malloc(nmemb * size);
    // Setting everything to 0
    memset(mem, 0, size);

    return mem;
}

void free(void *ptr) {
    struct mem_list *item;
    // Checking if free cand be called and unmapping if yes
    if (ptr && (item = mem_list_find(ptr))) {
        munmap(item->start, item->len);
        mem_list_del(item->start);
    }
}

void *realloc(void *ptr, size_t size) {
    // Allocating new block
    void *dest = malloc(size);

    memset(dest, 0, size);
    // Zeroing out new memory and copying the old data
    if (dest)
        memcpy(dest, ptr, size);
    // Freeing old block
    free(ptr);
    return (dest);
}

void *reallocarray(void *ptr, size_t nmemb, size_t size) {
    // Allocating new memory
    void *new = malloc(nmemb * size);
    if (!new)
        return NULL;

    size_t oldSize = *((size_t *)((char *)ptr - sizeof(size_t)));
    // Checking if the reallocation size if smaller than the old one
    if (oldSize > nmemb * size)
        oldSize = nmemb * size;

    // Copying the old data
    memcpy(new, ptr, oldSize);

    free(ptr);

    return new;
}
