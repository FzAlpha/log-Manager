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

---
## Date: 1 May 2026
### Log 3: Smart Sniper Delete & Interactive Edit System

**The Problem:** 
Needed a way to modify existing logs (deleting specific mistakes or updating typos/difficulty) without wiping the entire list. The biggest challenge was handling "Data Collisions"—how to target one specific problem when there are multiple problems with the exact same name in the Linked List?

**The Solution:**
Built an "Interactive Conflict Resolution" engine (similar to CLI tools like Git) that powers both the **Custom Delete** and **Update** features.
1. **Radar Scan:** Traversed the DLL to find all matches (case-insensitive).
2. **Pointer Caching (The Core Engine):** Instead of traversing the list twice, stored the exact memory addresses of matching nodes in a `std::vector<Node*>`.
3. **Interactive Menu:** If multiple matches are found, displayed them as a numbered list and prompted the user to select the exact node using vector indexing (`m[choice]`).
4. **Execution (Delete/Update):** 
   * **For Delete:** Safely relinked the `prev` and `next` pointers to bypass the targeted node, handled Edge Cases (like deleting the `head` node), and freed the memory using `delete target`.
   * **For Update:** Directly accessed the targeted node via its pointer and modified its string attributes.
5. **Persistence:** Saved the updated RAM data back to the hard drive (`fileSaver()`) after every operation.

**Key Traps Handled (The "Aha!" Moments):**
* **Dynamic Arrays over Raw Arrays:** Used `std::vector` and `.push_back()` for safe memory allocation to store node pointers.
* **SegFault Prevention (Ghost Targets):** Added an explicit check (`if (matches.size() == 0)`) to prevent the code from entering the selection logic when the search yields no results, avoiding a Segmentation Fault.
* **DLL Pointer Manipulation:** Mastered the 3-step deletion logic for Doubly Linked Lists (`target->prev->next = target->next`, etc.), ensuring the chain never breaks.
* **Mastering the Input Buffer:** Successfully implemented `cin.ignore()` immediately after `cin >> choice` to clear the `\n` character before calling `std::getline()`, completely avoiding the empty string trap.

---
## Date: 2 May 2026
### Log 4: In-Place Merge Sort on Doubly Linked List & System Architecture

**The Problem:** Needed a way to sort logged problems logically by difficulty (Easy -> Medium -> Hard) rather than alphabetically. The challenge was to do this entirely in-place within the Doubly Linked List, without using auxiliary space like Vectors or Arrays, while keeping the `next` and `prev` pointers intact.

**The Solution:**
Built an $O(N \log N)$ Merge Sort algorithm custom-designed for Doubly Linked Lists.
1. **The Weightage System:** Created `getProblemDifficultyWeight()` to assign numerical values to strings (Easy=1, Medium=2, Hard=3) for logical comparison during the merge phase.
2. **The Splitter (Tortoise and Hare):** Implemented a fast/slow pointer approach to accurately find the middle of the DLL and sever the connections cleanly.
3. **The Recursive Merge:** Handled complex recursive linking to stitch the two sorted halves back together, carefully relinking both `next` and `prev` pointers for every node to ensure the chain never breaks.
4. **Header Architecture Refactoring:** Solved a critical compilation issue by moving the `struct Node` blueprint to the top of `tracker.h`, ensuring all `.cpp` files understand the custom data type before function declarations.

**Key Traps Handled (The "Aha!" Moments):**
* **The "LowerCase" Illusion:** Realized that case-insensitivity requires comparing the normalized string, not the original raw string.
* **The Comma Operator Trap:** Discovered that C++ interprets `return (head, second)` using the comma operator (ignoring the left value and returning the right), completely bypassing the merge step. Replaced with a proper `return merge(head, second)`.
* **The "Undeclared Type" Header Trap:** Learned that the C++ compiler reads files top-to-bottom. If a function returns a `Node*`, the compiler must see the definition of `Node` earlier in the same header file.
* **Mastering Pointers:** Solidified the mental model of recursive DLL pointer manipulation—the ultimate test of avoiding Segmentation Faults and infinite loops.

# Date: 3 May 2026
**Project:** Log Manager (DSA Tracker)
**Phase:** 3 - Persistence, Time-Stamping & System Integration

### 1. The "Time Traveler" Bug & Constructor Overloading
* **Concept:** When adding a timestamp feature, a single constructor fetching `time(nullptr)` works for *new* problems but overwrites historical dates when loading from a saved file.
* **Solution:** Mastered **Constructor Overloading**. Created two separate constructors in `struct Node`:
  * One for new problems: Generates a fresh timestamp.
  * One for loading files: Accepts a `time_t` parameter to preserve the historical timestamp.

### 2. Time Management in C++ (`<ctime>`)
* **`time_t` vs `std::tm`:** Learned that storing time as a simple integer (`time_t` - Unix timestamp) is highly efficient for Hard Drive storage and linked list node memory.
* **Reverse Engineering Time:** Used `std::localtime()` to convert the raw `time_t` integer back into a human-readable `std::tm` structure.
* **Formatting:** Successfully extracted `tm_mday`, `tm_mon` (needs +1), and `tm_year` (needs +1900) to format dates beautifully in the console.

### 3. Advanced File Parsing & Data Extraction
* **The Delimiter Strategy:** Upgraded the file saving mechanism to use specific symbols (`-` and `|`) to separate data columns (Problem, Difficulty, Time).
* **String Manipulation:** Utilized `std::getline()`, `line.find()`, and `line.substr()` to slice a single text file line into discrete variables.
* **String to Integer:** Used `std::stoll()` to successfully parse the extracted timestamp string back into a `time_t` long integer format.

### 4. The "Invisible Space" Trap (Silent Logic Killers)
* **Concept:** In C++, `"easy"` and `" easy "` are completely different strings.
* **Impact:** A single stray space in the `fileSaver()` function completely broke the `getProblemDifficultyWeight` logic, causing the Merge Sort to fail silently because strings didn't match.
* **Takeaway:** Data formatting consistency in File I/O is just as critical as the algorithm itself. Always sanitize/trim strings or meticulously format the save files.

### 5. Multi-File Compilation & The Linker
* **Concept:** Transitioned from a single monolithic file to a modular `.h` and `.cpp` architecture.
* **The Trap:** Running `g++ main.cpp` results in an `ld returned 1 exit status` (Linker Error) because the compiler doesn't know where the function definitions are.
* **Solution:** Learned to compile the entire project using `g++ *.cpp -o main` to link the data layer, logic layer, and presentation layer together into a single executable.

### 6. Linked List Edge Cases (Circular Lists & Lost Tails)
* **Circular Bug:** Realized that `tail->next = head` accidentally creates a Circular Linked List, causing infinite loops during display/traversal. Fixed by ensuring `tail->next` points to the `newNode`.
* **The Lost Tail:** Learned that after running complex algorithms like Merge Sort, the `tail` pointer must be manually re-traversed and reassigned, otherwise subsequent appends will corrupt the list structure.


---

#  Date: 4 May 2026
**Project:** Log Manager
**Phase:** 4 - Refactoring & System Architecture


### 1. The DRY Principle (Don't Repeat Yourself)
* **Concept:** Identified duplicated code blocks handling Unix timestamp conversions across three different functions.
* **Solution:** Extracted the logic into a single, reusable helper function `dateConverter(time_t)`. This reduced code bloat and created a single source of truth for date formatting.

### 2. Separation of Concerns (The "Waiter & Chef" Model)
* **Concept:** A robust system should never mix User Interface (UI) logic with Core Engine data manipulation.
* **Refactoring:** Split massive functions (like `updateProblem`) into two distinct layers:
  * **The UI Layer (Waiter):** Handles all `cin` and `cout` operations, gathering input from the terminal.
  * **The Core Logic (Chef):** Pure C++ pointer manipulation that only accepts raw data and executes the update, completely ignorant of the terminal.

### 3. Data Sanitization ("Clean at the Gate")
* **The Flaw:** Delaying data formatting (like converting difficulties to lowercase) until the file-saving or sorting phase leads to inconsistent RAM states and potential segmentation faults.
* **The Fix:** Implemented a data filter directly at the input stage. By running `toLowerCase()` immediately after `getline()`, the system guarantees that only 100% clean, standardized data enters the Doubly Linked List and local storage files.

### 4. File I/O Bug: The Missing Output Stream
* **Issue:** The `fileSaver()` function was clearing `files.txt` but saving zero bytes of data.
* **Root Cause:** Accidentally used `std::cout` instead of the instantiated `std::ofstream out` object within the while loop, which blasted the data to the terminal instead of writing it to the disk.
* **Takeaway:** Always double-check stream targets when working with `<fstream>`.
*

---