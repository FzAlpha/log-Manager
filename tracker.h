#ifndef tracker_h
#define tracker_h
#include<string>
#include<ctime>
#include<vector>

//STRUCTURE OF THER NODE//
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

//HELPER FUNCTIONS//
/*FOR CLI*/
void addProblemHelperFunction();//for adding problem
void logCheckerHelperFunction();//for checking the logs from the files
void deleteHelper();//for deleting a node
void searchProblemHelper();//for searching a problem

/*FOR CUSTOM HELP*/
std::string toLowerCase(std::string s);//converts a given function to lowercase
int getProblemDifficultyWeight(std::string diff);//gives weight based on difficulty
std::string dateConverter(time_t date);//for convertimg long long time interger to readable format
std::vector<Node*> getMatches(std::string p);//returns a vector of same problem from the list
void updateNode(Node* target , std::string problem , std::string difficulty);//renames the problem and difficulty the given target node

//MAIN FUNCTIONS//

void addProblem(std::string name,std::string tag);//adds problem to the linked list
void ramLogChecker();//checks the linked list and prints its elements
void undoLast();//deletes the last elements of the lnked list
void fileSaver();//saves the linked list to the file
void displayFromFile();//prints the lines from the files
void loadFromFile();//** an important function** loads the lines to linked list before the program starts
void searchProblem(std::string query);//searches a users query
void showStatus();//countd the number of problem a user has done
void customDelete(std::string query);//for deleteing a selecteed node from the list
void updateProblem(std::string query);//for updating a problem
void addProblemFile(std::string name,std::string tag , time_t savedTime);//adds problem from the file


//MERGE SORTING//
Node* sortProblems(Node* head);
Node* split(Node* head);
Node* merge(Node* first, Node* second);

//CLI INTERFACE//
void welcomeMenu();//cli interface
#endif