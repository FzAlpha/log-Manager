#include <iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<vector>
#include "tracker.h"

using std::string,std::cout,std::cin,std::endl;




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
        cout<<endl;
        cout<<"welcome to Log Manager"<<endl;
        cout<<"---Choose from the Menu---"<<endl;
        cout<<"1.Add problem"<<endl;
        cout<<"2.Delete problem"<<endl;
        cout<<"3.Check the log"<<endl;
        cout<<"4.Save to File"<<endl;
        cout<<"5.Return"<<endl;
        cout<<"6.search a problem"<<endl;
        cout<<"7.view status"<<endl;
        cout<<"8.update a problem"<<endl;

       
        cin>>choice;

        if(choice<1 || choice>8){
            std::cerr<<"Error invalid input"<<endl;
            cin.clear();
            cin.ignore(1000,'\n');
        }
        
        switch(choice){
            case 1 :
                addProblemHelperFunction();
                break;
            case 2:
                
                deleteHelper();
                break;
            case 3:
                logCheckerHelperFunction();
                break;
            case 4:
                fileSaver();
                cout<<"file saved"<<endl;
                break;
            case 6:{
                searchProblemHelper();
                break;
            }
            case 7:
                showStatus();
                break;
            case 8:
                cout<<"enter the problem you want to update"<<endl;
                string s;
                cin.ignore();
                std::getline(cin,s);
                updateProblem(s);
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


void showStatus(){
    int countEasy = 0 , countMedium = 0 , countHard = 0;
    Node* temp = head; 
    while(temp != NULL){
        string lowerDifficulty = toLowerCase(temp->difficulty);
        if(lowerDifficulty == "easy"){
            countEasy++;
        }else if(lowerDifficulty == "medium"){
            countMedium++;
        }else if(lowerDifficulty == "hard"){
            countHard++;
        }
        temp = temp->next;
    }

    cout<<"Easy Problem Solved ="<<countEasy<<endl;
    cout<<"Medium Problem Solved ="<<countMedium<<endl;
    cout<<"Hard Problem Solved ="<<countHard<<endl;

    return;

} 

void searchProblemHelper(){
    string query;
    cout<<"enter your problem or difficulty"<<endl;
    cin.ignore();
    std::getline(cin , query);
    if(query==""){
        cout<<"invalid input"<<endl;
        return;
    }
    searchProblem(query);
    return;
}

string toLowerCase(string s){
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::tolower(c);});
    return s;
}

void searchProblem(string query){
    Node* temp = head;
    bool isPresent = false;
    string lowerQuery = toLowerCase(query);
    while(temp != NULL){
        string lowerTempProblem = toLowerCase(temp->problem);
        string lowerTempDiff = toLowerCase(temp->difficulty);
        if((lowerTempProblem.find(lowerQuery) != string::npos) || (lowerTempDiff.find(lowerQuery) != string::npos)){
            cout<<temp->problem<<"-"<<temp->difficulty<<endl;
            isPresent = true;
        }
        temp = temp->next;
    }

    if(isPresent == false){
        cout<<"problem not found"<<endl;
    }
    
    return;
}

void customDelete(string query){
    Node* temp = head;
    
    string lowerQuery = toLowerCase(query);
    int matchCount =0;
    std::vector<Node*> matches;
    while(temp != NULL){
        string lowerTempProblem = toLowerCase(temp->problem);
        if(lowerTempProblem.find(lowerQuery) != string::npos){
            ++matchCount;
            matches.push_back(temp);
        }
        temp = temp->next;
    }

    if(matchCount == 0){
        cout<<"problem not found"<<endl;
        return;
    }
    Node* target = head;
    if(matchCount == 1){
        target = matches[0];
    }else{
        cout << matches.size() << " matches found!" << endl;
        for(int i = 0; i < matches.size(); i++) {
            cout << i << ". " << matches[i]->problem << " - " << matches[i]->difficulty << endl;
        }
        cout << "Enter the number to delete: ";
        int choice;
        cin >> choice; 
        target = matches[choice];
    }
    if(target == head) {
        head = target->next;
        if(head != NULL) head->prev = NULL; 
    }
    else {
        target->prev->next = target->next;
        if(target->next != NULL) { 
            target->next->prev = target->prev;
        }
    }
    cout << "Deleted: " << target->problem << endl;
    delete target;
    fileSaver();
}

void deleteHelper(){
    cout<<"please select a option from the options given"<<endl;
    cout<<"1.delete the last"<<endl;
    cout<<"2. custom delete"<<endl;
    int choice;
    cin>>choice;
    if(choice == 1){
        undoLast();
        cout<<"last checkout deleted"<<endl;
        return;
    }else if(choice == 2){
        string s;
        cout<<"enter the problem you want to delete"<<endl;
        cin.ignore();
        std::getline(cin,s);
        customDelete(s);
        return;
    }else{
        std::cerr<<"enter valid input"<<endl;
        return;
    }
}

void updateProblem(string query){
    Node* temp = head;
    std::vector<Node*> m;
    string lowerQuery = toLowerCase(query);
    int i =0;
    while(temp != NULL){
        string lowerTempProblem = toLowerCase(temp->problem);
        if(lowerTempProblem.find(lowerQuery) != string::npos){
            m.push_back(temp);
            cout<<i<<". "<<temp->problem<<"-"<<temp->difficulty<<endl;
            i++;
        }
        temp = temp->next;
    }
    Node* target = head;
    if(i==0){
        cout<<"no problem found"<<endl;
        return;
    }
    if(i==1){
        target = m[0];
    }else{
        cout<<"enter the number of problem to update"<<endl;
        int c;
        cin>>c;
        target = m[c];
    }

    cout<<"what do you want to update"<<endl;
    cout<<"1.problem"<<endl;
    cout<<"2.difficulty"<<endl;
    int d;
    cin>>d;
    string a;
    if(d==1){
        cout<<"enter the updated problem"<<endl;
        cin.ignore();
        std::getline(cin,a);
        target->problem = a;
    }else if(d==2){
        cout<<"enter the updated difficulty"<<endl;
        cin.ignore();
        std::getline(cin,a);
        target->difficulty = a;
    }

    fileSaver();

}
