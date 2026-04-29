#ifndef tracker_h
#define tracker_h
#include<string>


void addProblem(std::string name,std::string tag);
void ramLogChecker();
void undoLast();
void fileSaver();
void addProblemHelperFunction();
void welcomeMenu();
void displayFromFile();
void loadFromFile();
void logCheckerHelperFunction();

struct Node{
    std::string problem;
    std::string difficulty;
    Node* next;
    Node* prev;

    Node(std::string problem , std::string difficulty){
        this->problem = problem;
        this->difficulty = difficulty;
        next = prev = NULL;
    }
};

extern Node* head;
extern Node* tail;
#endif