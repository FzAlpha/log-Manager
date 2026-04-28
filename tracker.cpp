#include <iostream>
#include<string>
#include<fstream>

using std::string,std::cout,std::cin,std::endl;

//defining all the functions
void addProblem(string name,string tag);
void ramLogChecker();
void undoLast();
void fileSaver();
void addProblemHelperFunction();
void welcomeMenu();
void displayFromFile();
void loadFromFile();
void logCheckerHelperFunction();


struct Node{
    string problem;
    string difficulty;
    Node* next;
    Node* prev;

    Node(string problem , string difficulty){
        this->problem = problem;
        this->difficulty = difficulty;
        next = prev = NULL;
    }
};

Node* head = nullptr;
Node* tail = nullptr;
//Adding problems
void addProblem(string name,string tag){
    Node* newNode = new Node(name,tag);
    if(head == NULL){
        head = tail = newNode;
    }else{
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

//prints the linked list
void ramLogChecker(){
    if(head == NULL){
        std::cout<<"Log is empty"<<std::endl;
        return;
    }
    Node* temp = head; 
    while(temp != NULL){
        std::cout<<temp->problem<<"-"<<temp->difficulty<<std::endl;
        temp = temp->next;
    }
    std::cout<<"log ended"<<std::endl;
}

//deletes last node of linked list
void undoLast(){
    if(head == NULL){
        std::cout<<"Log is empty.Enter something"<<std::endl;
        return;
    }
    if(head == tail){
        delete head;
        head = tail = NULL;
        return;
    }
    Node* temp = head;
    head = head->next;
    head->prev = NULL;
    temp->next = NULL;
    delete temp;
    return;
}

//saves the files
void fileSaver(){
    std::ofstream out("files.txt");
    
    if(!out){
        cout<<"file not opened"<<endl;
        return;
    }
    Node* temp = head;
    while(temp != NULL){
        out<<temp->problem<<"-"<<temp->difficulty<<endl;
        temp= temp->next;
    }
    out.close();
    return;
}

//helper functions for addproblem
void addProblemHelperFunction(){
    string problem,tag;
    cout<<"Enter the Problem name"<<endl;
    cin.ignore();
    std::getline(cin,problem);
    cout<<"Enter the difficulty"<<endl;
    std::getline(cin,tag);

    addProblem(problem,tag);
    cout<<"problem added"<<endl;
}


//display menu
void welcomeMenu(){
    int choice;
    do{
        cout<<"welcome to Log Manager"<<endl;
        cout<<"---Choose from the Menu---"<<endl;
        cout<<"1.Add problem"<<endl;
        cout<<"2.Delete last problem"<<endl;
        cout<<"3.Check the log"<<endl;
        cout<<"4.Save to File"<<endl;
        cout<<"5.Return"<<endl;

       
        cin>>choice;

        if(choice<1 || choice>5){
            std::cerr<<"Error invalid input"<<endl;
            cin.clear();
            cin.ignore(1000,'\n');
        }
        
        switch(choice){
            case 1 :
                addProblemHelperFunction();
                break;
            case 2:
                undoLast();
                cout<<"last checkout deleted"<<endl;
                break;
            case 3:
                logCheckerHelperFunction();
                break;
            case 4:
                fileSaver();
                cout<<"file saved"<<endl;
                break;
            
        }
    }while(choice != 5);
}

//displays the content of the file
void displayFromFile(){

    std::ifstream in("files.txt");

    
    if (!in.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        
        std::cout << line << std::endl;
    }

    
    in.close();
}

//loads the files contents and breaks them and adds to the linked list 
void loadFromFile(){
    std::ifstream in("files.txt");

    if (!in.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return;
    }
    string line;

    while(std::getline(in,line)){
        size_t pos = line.find("-");
        if(pos != string::npos){
            string pName = line.substr(0,pos);
            string pDiff = line.substr(pos+1);
            addProblem(pName,pDiff);
        }
    }
    in.close();
}

//helper function for log checker
void logCheckerHelperFunction(){
    cout<<"dou You want to see the unsaved version or saved version(Not Applicable if already saved)"<<endl;
    cout<<"1.saved version"<<endl;
    cout<<"2.unsaved version"<<endl;
    int n;
    cin.ignore();
    cin>> n;
    if(n==1){
        displayFromFile();
    }else if(n==2){
        ramLogChecker();
    }else{
        cout<<"enter a valid option"<<endl;
    }
}

int main() {
    loadFromFile();
    welcomeMenu();

    return 0;
}