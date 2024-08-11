#include <MemoryReader.h>
#include <iostream>
#include <cstdlib>

void MemoryReader::readAllProcMem()
{
  DIR* dir = opendir("/proc");
  struct dirent* entry;

  if (dir == nullptr)
  {
    std::cerr << "Error: Could not open /proc" << std::endl;
    return;
  }

  while ((entry = readdir(dir)) != nullptr)
  {
    pid_t pid = std::atoi(entry->d_name);

    if (pid > 0)
    {
      ProcessMemory processMemory(pid);
      processMemory.readMemory();
    }
  }

  closedir(dir);
}
