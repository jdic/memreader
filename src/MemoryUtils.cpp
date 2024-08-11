#include <MemoryUtils.h>

std::string getMapsFilePath(pid_t pid)
{
  return "/proc/" + std::to_string(pid) + "/maps";
}

std::string getMemFilePath(pid_t pid)
{
  return "/proc/" + std::to_string(pid) + "/mem";
}
