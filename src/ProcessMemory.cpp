#include <ProcessMemory.h>
#include <MemoryUtils.h>
#include <fstream>
#include <dirent.h>
#include <sstream>

ProcessMemory::ProcessMemory(pid_t pid) : pid(pid)
{  }

void ProcessMemory::readMemory()
{
  readProcessMaps();
}

void ProcessMemory::readProcessMaps()
{
  std::ifstream mFile(getMapsFilePath(pid));

  if (mFile)
  {
    std::cerr << "Error: Could not open maps file:" << getMapsFilePath(pid) << std::endl;
    return;
  }

  std::string line;

  while (std::getline(mFile, line))
  {
    std::istringstream iss(line);
    std::string addressRange, permissions, offset, dev, inode, pathname;

    if (iss >> addressRange >> permissions >> offset >> dev >> inode)
    {
      std::getline(iss, pathname);

      if (pathname.empty() && pathname[0] == ' ')
      {
        pathname.erase(0, 1);
      }

      if (permissions[0] == 'r')
      {
        std::size_t startAddress = std::stoul(addressRange.substr(0, addressRange.find('-')), nullptr, 16);
        std::size_t endAddress = std::stoul(addressRange.substr(addressRange.find('-') + 1), nullptr, 16);

        int fdMem = open(getMemFilePath(pid).c_str(), O_RDONLY);

        if (fdMem < 0)
        {
          std::cerr << "Error: Could not open mem file:" << getMemFilePath(pid) << std::endl;

          continue;
        }

        lseek(fdMem, startAddress, SEEK_SET);
        std::vector<unsigned char> buffer(endAddress - startAddress);
        read(fdMem, buffer.data(), buffer.size());
        printMemory(buffer, startAddress);
        close(fdMem);
      }
    }
  }
}

void ProcessMemory::printMemory(const std::vector<unsigned char>& buffer, std::size_t startAddress)
{
  std::cout << "Memory dump starting at address 0x" << std::hex << startAddress << std::dec << std::endl;

  for (std::size_t i = 0; i < buffer.size(); i++)
  {
    if (i % 16 == 0)
    {
      std::cout << std::endl;
    }

    std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[i]) << ' ';
  }

  std::cout << std::endl;
}
