#include <stdio.h>
#include "memallocator.h"
#include <math.h>
#include <stdbool.h>

#define VALID 1
#define INVALID -1
#define FAIL 0


void* memStart = NULL;

int allSize = 0;

void* emptyBlocksHead = NULL;

int* SizeStart(void* descriptor)
{
    return (int*)descriptor;   //size in the beggining of descriptor
}

void** PointerToEmptyBlocks(void* descriptor)
{
    return (void**)((char*)descriptor + sizeof(int));  
}

int* SizeEnd(void* descriptor)
{
    return (int*)((char*)descriptor + abs(*SizeStart(descriptor)) - sizeof(int));   //size int the end of descriptor
}

int memgetminimumsize()
{
    return 2 * sizeof(int) + sizeof(void*);    
}

int memgetblocksize()
{
    return 2 * sizeof(int) + sizeof(void*); 
}

int meminit(void* memory, int size)
{
    if (!memory || (size < memgetminimumsize()))
    {
        return INVALID;
    }
    void* descriptor = memory;
    *SizeStart(descriptor) = size;
    *PointerToEmptyBlocks(descriptor) = NULL;
    *SizeEnd(descriptor) = size;
    emptyBlocksHead = descriptor;
    memStart = memory;
    allSize = size;
    return VALID;
}

void* memalloc(int size)
{
    if ((size > allSize - memgetblocksize()) || (size < 1))
    {
        return NULL;
    }
    void* prevBlock = NULL;
    void* currentBlock = emptyBlocksHead;
    void* firstCorrect = NULL;
    void* freeNextBlock = NULL;
    int fullBlock = memgetblocksize() + size;
    while (currentBlock)
    {
        if (*SizeStart(currentBlock) >= fullBlock)
        {
            firstCorrect = currentBlock;
            break;
        }
        prevBlock = currentBlock;
        currentBlock = *PointerToEmptyBlocks(currentBlock);
    }
    if (!firstCorrect)
    {
        return NULL;
    }
    if (*SizeStart(firstCorrect) > fullBlock + memgetblocksize())
    {
        freeNextBlock = (void*)((char*)firstCorrect + fullBlock);
        *SizeStart(freeNextBlock) = *SizeStart(firstCorrect) - fullBlock;
        *PointerToEmptyBlocks(freeNextBlock) = *PointerToEmptyBlocks(firstCorrect);
        *SizeEnd(freeNextBlock) = *SizeStart(freeNextBlock);
        if (!prevBlock)
        {
            emptyBlocksHead = freeNextBlock;
        }
        else
        {
            *PointerToEmptyBlocks(prevBlock) = freeNextBlock;
        }
        *SizeStart(firstCorrect) = fullBlock;
    }
    else
    {
        if (!prevBlock)
        {
            emptyBlocksHead = *PointerToEmptyBlocks(firstCorrect);
        }
        else
        {
            *PointerToEmptyBlocks(prevBlock) = *PointerToEmptyBlocks(firstCorrect);
        }
    }
    *SizeStart(firstCorrect) = -*SizeStart(firstCorrect);
    *SizeEnd(firstCorrect) = *SizeStart(firstCorrect);
    *PointerToEmptyBlocks(firstCorrect) = NULL;
    return (void*)((char*)firstCorrect + sizeof(int) + sizeof(void*));
}

bool MergeWithNext(void* currentBlock, void* nextBlock, bool merged_with_left)   //This function is created to make it easier to understand "free" function
{
    if ((((char*)nextBlock < (char*)memStart + allSize)) && ((*SizeStart(nextBlock) > 0)))
    {
        if (!merged_with_left)
        {
            *PointerToEmptyBlocks(currentBlock) = emptyBlocksHead;
            emptyBlocksHead = currentBlock;
        }
        void* nextBlockPrev = emptyBlocksHead;
        void* tmp = emptyBlocksHead;
        while (tmp)
        {
            if (*PointerToEmptyBlocks(tmp) == nextBlock)
            {
                nextBlockPrev = tmp;
                break;
            }
            tmp = *PointerToEmptyBlocks(tmp);
        }
        if (nextBlockPrev != nextBlock)
        {
            *PointerToEmptyBlocks(nextBlockPrev) = *PointerToEmptyBlocks(nextBlock);
        }
        else
        {
            emptyBlocksHead = *PointerToEmptyBlocks(nextBlock);
        }
        *SizeStart(currentBlock) += *SizeStart(nextBlock);
        *SizeEnd(currentBlock) = *SizeStart(currentBlock);
        return VALID;
    }
    else
    {
        return FAIL;
    }
}

void memfree(void* p)
{
    void* prevBlock = NULL, * currentBlock = NULL, * nextBlock = NULL;
    currentBlock = (void*)((char*)p - sizeof(void*) - sizeof(int));
    nextBlock = (void*)((char*)currentBlock + abs(*SizeEnd(currentBlock)));
    if ((char*)currentBlock - (char*)memStart > memgetblocksize())
    {
        prevBlock = (void*)((char*)currentBlock - abs(*((int*)currentBlock - 1)));
    }
    bool resMergeWithPrev = 0, resMergeWithNext = 0;
    *SizeStart(currentBlock) *= -1;
    *SizeEnd(currentBlock) = *SizeStart(currentBlock);
    if ((prevBlock >= memStart) && (*SizeStart(prevBlock) > 0))   //merge currentBlock with pervBlock(if it's empty)
    {
        resMergeWithPrev = 1;
        *SizeStart(prevBlock) += *SizeStart(currentBlock);
        *SizeEnd(prevBlock) = *SizeStart(prevBlock);
        currentBlock = prevBlock;
    }
    resMergeWithNext = MergeWithNext(currentBlock, nextBlock, resMergeWithPrev);   //function, which merge currentBlock with nextBlock(if it's empty) 
    if (!resMergeWithPrev && !resMergeWithNext)
    {
        *PointerToEmptyBlocks(currentBlock) = emptyBlocksHead;
        emptyBlocksHead = currentBlock;
    }
}

void memdone()
{
    void* tmp = memStart;
    while ((char*)tmp < (char*)memStart + allSize)
    {
        if (*SizeStart(tmp) < 0)
        {
            fprintf(stderr, "ERROR at 0x%p\n", (char*)tmp + sizeof(int) + sizeof(void*));
        }
        tmp = (void*)((char*)tmp + abs(*SizeStart(tmp)));
    }
}