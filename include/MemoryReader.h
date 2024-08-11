#ifndef MEMORY_READER_H
#define MEMORY_READER_H

#include <dirent.h>
#include <sys/types.h>
#include <ProcessMemory.h>

class MemoryReader
{
  public:
    void readAllProcMem();
};

#endif
