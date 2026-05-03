#ifndef tracker_h
#define tracker_h
#include<string>
#include<ctime>


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
int getProblemDifficultyWeight(std::string diff);
void addProblemFile(std::string name,std::string tag , time_t savedTime);



struct Node{
    std::string problem;
    std::string difficulty;
    time_t date;
    Node* next;
    Node* prev;

    Node(std::string problem , std::string difficulty){
        this->problem = problem;
        this->difficulty = difficulty;
        this->date = time(nullptr);
        this->next =this-> prev = nullptr;
    }
    Node(std::string problem , std::string difficulty , time_t savedTime){
        this->problem = problem;
        this->difficulty = difficulty;
        this->date = savedTime;
        this->next =this-> prev = nullptr;
    }
};

extern Node* head;
extern Node* tail;
Node* sortProblems(Node* head);
Node* split(Node* head);
Node* merge(Node* first, Node* second);
#endif