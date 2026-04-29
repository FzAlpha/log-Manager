# Developer Logs - CP Log Manager

## Date: 28 April 2026
### Log 0: CLI Integration & RAM-Disk Data Persistence

**The Problem:** The tracker worked as a one-off script. It lost all memory of previous problems the moment it was closed, and taking user inputs with spaces caused the entire program to crash into an infinite loop.

**The Solution:**
1. Built an interactive Command Line Interface (CLI) using a `do-while` loop and `switch` case system for continuous operation.
2. Engineered the `loadFromFile()` function to read `files.txt` at program startup, parse the data, and automatically rebuild the Doubly Linked List in RAM.

**Key Traps Handled (The "Aha!" Moments):**
* **The Input Buffer Trap (`cin` vs `getline`):** Discovered that `cin` leaves a hidden newline character (`\n`, ASCII 10) in the buffer. This caused the next `getline()` to instantly skip. Fixed it by explicitly using `cin.ignore()` to clear the buffer.
* **The Infinite Loop Crash:** Realized that `cin >>` stops reading at spaces (e.g., "Two Sum" breaks it), putting the stream in a fail state. Shifted strictly to `std::getline()` for string inputs.
* **Append vs. Overwrite Architecture:** Using `ios::app` for file saving was duplicating the entire list every time I saved. Changed the logic to the "Persistence Cycle": Load full file to RAM on startup -> Add new node to RAM -> Overwrite the entire updated RAM list back to the file. 
* **String Parsing:** Used `line.find("-")` and `substr()` to cleanly slice the text file lines back into separate `problem` and `difficulty` variables.
*

## Date: 29 April 2026
### Log 1: Monolithic to Modular Architecture Refactoring

**The Problem:** Initially, the entire logic (structs, file handling, linked list operations, and CLI menu) was written in a single `tracker.cpp` file. As the codebase grew, it became hard to maintain, debug, and scale. It was essentially a "script" rather than a software system.

**The Solution:**
Refactored the monolithic code into a standard C++ multi-file architecture:
1. `tracker.h`: Acts as the blueprint. Contains struct definitions, header guards, and function prototypes.
2. `tracker.cpp`: The core engine. Contains the actual implementation of the linked list and file I/O logic.
3. `main.cpp`: The control room. Only handles the user CLI menu and triggers functions.

**Key Traps Handled (The "Aha!" Moments):**
* **Header Guards:** Learned the hard way that without `#ifndef`, the compiler includes the header multiple times, causing definition errors.
* **Namespace Pollution:** Realized why `using namespace std;` is a sin in header files. Replaced it with explicit `std::string` to keep the blueprint clean.
* **One Definition Rule (ODR):** Faced the linker crash (`collect2.exe: error: ld returned 1 exit status`) because `head` and `tail` pointers were defined in the header. Fixed it by using the `extern` keyword in `.h` and allocating memory only in `.cpp`.

**Compilation Command Upgraded:**
Shifted from single-file execution to multi-file linking:
`g++ main.cpp tracker.cpp -o manager`