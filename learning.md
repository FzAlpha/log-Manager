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

---
## Date: 30 April 2026
### Log 2: Smart Search Engine & Analytics Dashboard

**The Problem:** As the log size grows, finding specific problems manually becomes impossible. Needed a way to query problems case-insensitively and track overall CP progress, all without relying on external databases to keep the tool lightweight and portable.

**The Solution:**
1. **Search Engine (`searchProblem`):** Implemented an in-memory linear search traversing the doubly linked list. Used string manipulation to allow partial and case-insensitive matching.
2. **Analytics Dashboard (`showStatus`):** Built a traversal counter to aggregate total problems solved and categorize them by difficulty (Easy, Medium, Hard).
3. **Separation of Concerns:** Abstracted the input handling into a `searchProblemHelper()` to keep the main switch-case clean.

**Key Traps Handled (The "Aha!" Moments):**
* **The "Exact Match" Trap:** Replaced the `==` operator with C++ `std::string::find()` to allow partial substring matching (e.g., typing "sum" finds "Two Sum").
* **Case-Insensitivity & Lambdas:** Wrote a robust `toLowerCase` helper function using `std::transform` and a lambda function `[](unsigned char c){ return std::tolower(c); }` to normalize strings before comparing.
* **The Logical Flow (`&&` vs `||`):** Initially used `&&` which required the query to be in BOTH the problem name and difficulty. Fixed this by switching to `||` (OR) to allow flexible searching.
* **State Management (The Flag Logic):** Used a boolean flag (`isPresent`) to track if a match was found during the entire list traversal, preventing premature exits and ensuring the "not found" message only triggers after checking every node.
* **The Empty String Bug:** Discovered that an empty `getline` input `""` matches everything when using `.find()`, causing the entire log to print. Added an explicit `if(query == "")` check to block invalid empty searches.
* **Directory Path Glitch:** Handled terminal execution errors (`CommandNotFoundException`) by realizing the compiler needs to be in the exact working directory (`cd log-Manager`) to link multiple files correctly.
*