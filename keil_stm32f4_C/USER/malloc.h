#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define HEAP_SIZE 64 * 1024  // 64KB heap size

#ifndef BLOCK_TYPE
#define BLOCK_TYPE

typedef struct Block {
    size_t size;
    struct Block* next;
    int free;
} Block;

#endif // BLOCK_TYPE

#define BLOCK_SIZE sizeof(Block)

static char heap[HEAP_SIZE];
static Block* freeList = (Block*)heap;

void init_malloc() {
    freeList->size = HEAP_SIZE - BLOCK_SIZE;
    freeList->next = NULL;
    freeList->free = 1;
}

void* my_malloc(size_t size) {
    Block* curr;
    curr  = freeList;
    while (curr != NULL && !(curr->free && curr->size >= size)) {
        curr = curr->next;
    }

    if (curr == NULL) {
        return NULL;  // No sufficient block found
    }

    if (curr->size > size + BLOCK_SIZE) {
        Block* newBlock = (Block*)((char*)curr + BLOCK_SIZE + size);
        newBlock->size = curr->size - size - BLOCK_SIZE;
        newBlock->next = curr->next;
        newBlock->free = 1;

        curr->size = size;
        curr->next = newBlock;
    }

    curr->free = 0;
    return (char*)curr + BLOCK_SIZE;
}

void my_free(void* ptr) {
    Block* block;
    Block* curr;
    if (ptr == NULL) {
        return;
    }

    block = (Block*)((char*)ptr - BLOCK_SIZE);
    block->free = 1;

    // Coalesce adjacent free blocks
    curr = freeList;
    while (curr != NULL) {
        if (curr->free && curr->next != NULL && curr->next->free) {
            curr->size += BLOCK_SIZE + curr->next->size;
            curr->next = curr->next->next;
        }
        curr = curr->next;
    }
}
