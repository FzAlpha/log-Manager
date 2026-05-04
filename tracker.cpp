#include <iostream>

#include<fstream>
#include<algorithm>


#include "tracker.h"

using std::string,std::cout,std::cin,std::endl;




Node* head = nullptr;
Node* tail = nullptr;

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

void addProblemFile(string name,string tag , time_t savedTime){
    Node* newNode = new Node(name,tag , savedTime);
    if(head == NULL){
        head = tail = newNode;
    }else{
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void ramLogChecker(){
    if(head == NULL){
        std::cout<<"Log is empty"<<std::endl;
        return;
    }
    Node* temp = head; 
    while(temp != NULL){
        
        std::cout<<temp->problem<<" - "<<temp->difficulty<<" | Added on = "<<dateConverter(temp->date)<<"\n";
        temp = temp->next;
    }
    std::cout<<"log ended"<<std::endl;
}

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

void fileSaver(){
    std::ofstream out("files.txt");
    
    if(!out){
        cout<<"file not opened"<<endl;
        return;
    }
    Node* temp = head;
    
    while(temp != NULL){
        out<<temp->problem<<"-"<<temp->difficulty<< "|" << temp->date<<endl;
        temp= temp->next;
    }
    out.close();
    return;
}

void addProblemHelperFunction(){
    string problem,tag;
    cout<<"Enter the Problem name"<<endl;
    cin.ignore();
    std::getline(cin,problem);
    cout<<"Enter the difficulty"<<endl;
    std::getline(cin,tag);
    tag = toLowerCase(tag);

    addProblem(problem,tag);
    cout<<"problem added"<<endl;
}

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
        cout<<"9.save according to order"<<endl;

       
        cin>>choice;

        if(choice<1 || choice>9){
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
            case 8:{
                cout<<"enter the problem you want to update"<<endl;
                string s;
                cin.ignore();
                std::getline(cin,s);
                updateProblem(s);
                break;
            }
            case 9:{
                head = sortProblems(head);
                if (head != NULL) {
                    Node* temp = head;
                    while (temp->next != NULL) {
                        temp = temp->next;
                    }
                    tail = temp; 
                }
                fileSaver();
                break;
            }
        }
    }while(choice != 5);
}


void displayFromFile(){
    std::ifstream in("files.txt");
    if (!in.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return;
    }
    std::string line;
    while (std::getline(in, line)) {
        size_t pos1 = line.find("|");
        if(pos1 != std::string::npos){
            
            std::string problemData = line.substr(0, pos1); 
            
           
            time_t pTime = std::stoll(line.substr(pos1+1));
            
            std::cout << problemData << " | Added on: " << dateConverter(pTime) << std::endl;
        }
    }
    in.close();
}


void loadFromFile(){
    std::ifstream in("files.txt");

    if (!in.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return;
    }
    string line;

    while(std::getline(in,line)){
        size_t pos1 = line.find("-");
        size_t pos2 = line.find("|");
        if(pos1 != string::npos && pos2 != string::npos){
            string pName = line.substr(0,pos1);
            string pDiff = line.substr(pos1+1 , pos2-(pos1+1));
            time_t pTime = std::stoll(line.substr(pos2+1));
            addProblemFile(pName,pDiff,pTime);
        }
    }
    in.close();
}


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
        if(lowerDifficulty.find("easy") == 0){
            countEasy++;
        }else if(lowerDifficulty.find("medium") == 0){
            countMedium++;
        }else if(lowerDifficulty.find("hard") == 0){
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
    s.erase(std::find_if(s.rbegin() , s.rend() ,[](unsigned char ch){return !std::isspace(ch);}).base() , s.end());
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
            cout<<temp->problem<<"-"<<temp->difficulty<<"| Added on ="<<dateConverter(temp->date)<<endl;
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
    std::vector<Node*> matches = getMatches(query);
    if(matches.empty()){
        cout<<"no problem found"<<endl;
        return;
    }
    cout<<"Choose which one to upadate\n";
    for(int i= 0 ; i<matches.size() ; i++){
        cout<<i<<". "<<matches[i] ->problem<<" - "<< matches[i] ->difficulty<<endl;
    }
    int c;
    cin>>c;
    cin.ignore();
    Node* target = head;
    target = matches[c];
    cout<<"what do you want to update"<<endl;
    cout<<"1.problem\n";
    cout<<"2.Difficulty\n";
    cout<<"3.Both\n";
    int choice;
    cin>>choice;
    cin.ignore();
    if(c<0 || c>=matches.size()){
        std::cerr<<"Invalid choice\n";
        return;
    }
    string problemName ="";
    string problemDIfficulty = "";
    if(choice == 1 || choice == 3){
        cout<<"Enter problem name\n";
        std::getline(cin, problemName);
    }
    if(choice == 2 || choice == 3){
        cout<<"Enter difficulty name\n";
        std::getline(cin, problemDIfficulty);
    }
    updateNode(target , problemName , problemDIfficulty);
    fileSaver();
    return;

}

std::vector<Node*> getMatches(string p){
    std::vector<Node*> ans;
    Node* temp = head;
    string lowerp = toLowerCase(p);
    while(temp != NULL){
        string lowerTemporaryProblem = toLowerCase(temp->problem);
        if(lowerTemporaryProblem.find(lowerp) != string::npos){
            ans.push_back(temp);
        }
        temp = temp->next;
    }
    return ans;
}

void updateNode(Node* target , string problem , string difficulty){
    if(problem != ""){
        target->problem = problem;
    }
    if(difficulty != ""){
        target->difficulty = difficulty;
    }
    return;
}

int getProblemDifficultyWeight(string diff){
    string lowerDiff = toLowerCase(diff);
    if(lowerDiff == "easy"){
        return 1;
    }else if(lowerDiff == "medium"){
        return 2;
    }else if(lowerDiff == "hard"){
        return 3;
    }
    return -1;
}

Node* sortProblems(Node* head){
    if(!head || !head->next){
        return head;
    }
    Node* second = split(head);

    head = sortProblems(head);
    second = sortProblems(second);

    return merge(head , second);
}

Node* split(Node* head){
    Node* fast = head , *slow = head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node* temp = slow->next;
    slow->next = nullptr;
   
    if (temp) {
        temp->prev = nullptr;
    }
    return temp;
}

Node* merge(Node* first, Node* second){
    if (!first) return second;
    if (!second) return first;

    if (getProblemDifficultyWeight(first->difficulty) <= getProblemDifficultyWeight(second->difficulty)) {
        first->next = merge(first->next, second);
        if (first->next) first->next->prev = first;
        first->prev = nullptr;
        return first;
    } else {
        second->next = merge(first, second->next);
        if (second->next) second->next->prev = second;
        second->prev = nullptr;
        return second;
    }
}


string dateConverter(time_t date){
    struct tm* timeinfo = std::localtime(&date);
    char dateBuffer[26];
    std::strftime(dateBuffer , sizeof(dateBuffer) , "%b %d %H:%M" , timeinfo);
    return dateBuffer; 
}

