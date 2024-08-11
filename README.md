# Memory Reader

This C++ project is a tool for reading the memory of processes on a Linux-based system. The tool scans the `/proc` directory for information about running processes and then reads and displays the memory of those processes.

## Project Structure

The project is organized into the following directories and files:

```
├── include.
│ ├─── MemoryReader.h
│ ├─── MemoryUtils.h
│ └└─── ProcessMemory.h
├─── src.
│ ├─── MemoryReader.cpp
│ ├─── MemoryUtils.cpp
│ └└── ProcessMemory.cpp
└└── main.cpp
```

## Functionality

### Main Classes and Functions

1. **MemoryReader**
   - **Method `readAllProcMem()`**: Traverses the `/proc` directory, reads the process list and for each process, creates an instance of `ProcessMemory` and calls its `readMemory()` method.

2. **ProcessMemory**
   - **Method `readMemory()`**: Calls the `readProcessMaps()` method to read the memory maps of the process.
   - **Method `readProcessMaps()`**: Reads the process memory maps file (`/proc/[pid]/maps`), identifies readable memory regions, and then reads the contents of those regions.
   - Method `printMemory()`**: Prints the contents of the memory read in a hexadecimal format.

3. **Utility Functions**
   - **`getMapsFilePath(pid_t pid)`**: Returns the path to the process map file.
   - **`getMemFilePath(pid_t pid)`**: Returns the path to the process memory file.

## Compilation and Execution

To compile and run the project, follow these steps:

1. **Compile the Project**.

   Make sure you have a C++ compiler such as `g++` installed. Use the following command to compile the project:

   ```bash
   g++ -o memreader main.cpp src/MemoryReader.cpp src/MemoryUtils.cpp src/ProcessMemory.cpp -Iinclude
   ```

1. **Run the Program**

   Once compiled, run the program with:

   ```bash
   sudo ./memreader
   ```

   The program will traverse the /proc directory, read the memory of the processes and display the contents in hexadecimal format.

## Notes and Considerations.

- Permissions: To read memory from other processes, you may need superuser (sudo) permissions. Depending on your configuration, you may be able to run the program with `sudo ./memreader`.

- `/proc` files: The `/proc` directory is a virtual file system that provides information about processes and system status. The contents of `/proc/[pid]/maps` and `/proc/[pid]/mem` may vary depending on system configuration and user permissions.

- Common Errors: If the program cannot open the necessary files or reads data incorrectly, check the permissions and make sure the process you are trying to read is running.

- Future Implementations: The current project is designed to read and display process memory. You can extend it to include more detailed analysis, data filtering or support for other output formats.
