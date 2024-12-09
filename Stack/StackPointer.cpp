#include <iostream>
#include <string>
using namespace std;
struct Person{
    int id;
    int age;
    string name;
    string address;
    Person() : id(-99), age(-99), name("No exist"), address("No exist") {}
    Person(int id, int age, string name, string address) 
        : id(id), age(age), name(name), address(address) {}
};
struct Node{
    Person data;
    Node* next = nullptr;
};
class Stack{
    private:
        Node* headerNode = nullptr;
    public:
        ~Stack(){
            while(headerNode){
                Node* temp = headerNode;
                headerNode = headerNode->next;
                delete temp;
            }
        }
        bool isEmpty(){
            return headerNode == nullptr;
        }        
        void push(Person data){
            Node* newNode = new(nothrow) Node;
            if(!newNode){
                cout <<"Cannot allocate.\n";
                return;
            }
            newNode->data = data;
            newNode->next = headerNode;
            headerNode = newNode;
        }
        Person pop(){
            Person result;
            if(!headerNode){
                cout <<"The stack is empty.\n";
                return result;
            }
            Node* temp = headerNode;
            result = headerNode->data;
            headerNode = headerNode->next;
            delete temp;
            return result;
        }
        Person peek(){
            Person result;
            if(!headerNode){
                cout <<"The stack is empty.\n";
                return result;
            }
            result = headerNode->data;
            return result;
        }
        void display(){
            Node* temp = headerNode;
            if(isEmpty()){
                cout <<" The stack is empty.\n";
                return;
            }
            while(temp){
                cout <<temp->data.id <<" : "<< temp->data.name
                     <<" : "<< temp->data.age <<" : "<< temp->data.address <<'\n';
                temp = temp->next;      
            }
        }
};
void display_person(Person& data){
    cout << data.id <<" : "<< data.age <<" : "<< data.name <<" : "<< data.address <<'\n';
}
int main(){
    Stack stack;
    Person p1 = {1, 25, "Shaw", "England"};
    Person p2 = {2, 50, "Luke", "American"};
    Person p3 = {3, 46, "Dominic", "Family"};
    stack.push(p1);
    stack.push(p2);
    stack.push(p3);
    Person p = stack.pop();
    p = stack.pop();
    p = stack.pop();
    p = stack.pop();
    display_person(p);
    cout << endl;
    stack.display();
    return 0;
}