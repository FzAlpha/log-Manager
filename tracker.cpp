#include <iostream>
#include<string>
#include<fstream>

using std::string;

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
void logChecker(){
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
    if(head == NULL){
        out.close();
        return;
    }
    if(head == tail){
        out<<head->problem<<"-"<<head->difficulty<<std::endl;
        out.close();
        return;
    }
    Node* temp = head;
    while(temp != NULL){
        out<<temp->problem<<"-"<<temp->difficulty<<std::endl;
        temp= temp->next;
    }
    out.close();
    return;
}
int main() {
    addProblem("Two sum","Easy");
    addProblem("Three sum","Medium");
    addProblem("Merge k sorted List","Hard");


    undoLast();

    logChecker();
    fileSaver();
    return 0;
}