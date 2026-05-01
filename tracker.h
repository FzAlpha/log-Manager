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
void searchProblem(std::string query);
void showStatus();
std::string toLowerCase(std::string s);
void searchProblemHelper();
void customDelete(std::string query);
void deleteHelper();
void updateProblem(std::string query);


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