# 🚀 Log Manager (DSA Progress Tracker)

A lightweight, blazing-fast, console-based Data Structures and Algorithms (DSA) progress tracker built entirely in **C++**. 

Unlike standard trackers that rely on standard library containers like `std::vector`, this project is engineered from scratch using a custom **Doubly Linked List (DLL)** architecture, demonstrating a deep understanding of manual memory management, pointer manipulation, and custom sorting algorithms.

## ✨ Key Features

* **Custom Memory Architecture:** Fully powered by a Doubly Linked List. No `std::vector` or arrays used for core storage.
* **In-Place Merge Sort:** Features an $O(N \log N)$ custom Merge Sort algorithm designed specifically for pointers, sorting problems logically by difficulty (Easy $\rightarrow$ Medium $\rightarrow$ Hard) without using extra auxiliary space.
* **Data Persistence (File I/O):** Saves logs to a local text file using custom string delimiters and parsers, ensuring your progress is never lost between sessions.
* **Smart Timestamping:** Automatically stamps each solved problem with the exact date and time using Unix timestamps (`time_t`), converted dynamically for user-friendly console display.
* **Advanced Operations:**
  * **Custom Search & Delete:** Locate and delete specific problems using case-insensitive string matching.
  * **Update:** Modify the name or difficulty of existing logs dynamically.
  * **Analytics:** Instantly view statistics on how many Easy, Medium, and Hard problems have been conquered.

## 🛠️ Tech Stack

* **Language:** C++ (Standard C++11/17/23)
* **Concepts:** Object-Oriented Programming (OOP), Pointers, Doubly Linked Lists, Recursion, File Handling, Time Manipulation (`<ctime>`), Modular Compilation.

## 📂 Project Structure

The project follows a clean, modular, multi-file architecture:

```text
📦 Log-Manager
 ┣ 📜 main.cpp        # The entry point and UI menu loop
 ┣ 📜 tracker.cpp     # Core logic, algorithms, and file handling
 ┣ 📜 tracker.h       # Struct definitions and function declarations
 ┗ 📜 files.txt       # Local database (Auto-generated)
