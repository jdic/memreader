#ifndef PROCESS_MEMORY_H
#define PROCESS_MEMORY_H

#include <vector>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>

class ProcessMemory
{
  public:
    ProcessMemory(pid_t pid);

    void readMemory();

  private:
    pid_t pid;

    void readProcessMaps();
    void printMemory(const std::vector<unsigned char>& buffer, std::size_t startAddress);
};

#endif
