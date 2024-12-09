#include <iostream>
#include <string>
using namespace std;
struct Node{
    int id;
    string name;
    Node(int id, string name)
        : id(id), name(name) {}
    Node() : id(-999), name("") {}
};
class Stack{
    private:
        unsigned int capacity;
        unsigned int count = 0;
        int top = -1;
        Node* q_stack;
    public:
        Stack(unsigned int cap){
            this->capacity = cap;
            this->q_stack = new Node[capacity];
        }
        ~Stack() {delete[] q_stack;}
        bool isFull() {return count == capacity;}
        bool isEmpty() {return count == 0;}
        void push(int id, string name){
            if(isFull()){
                cout <<"The stack is full. Cannot insert.\n";
                return;
            }
            q_stack[++top] = Node(id, name);
            count++;
        }
        Node pop(){
            Node result;
            if(isEmpty()){
                cout <<"The stack is empty. Cannot pop.\n";
                return result;
            }
            result = q_stack[top--];
            count--;
            return result;
        }
        Node peek(){
            Node result;
            if(isEmpty()){
                cout <<"The stack is empty.\n";
                return result;
            }
            result = q_stack[top];
            return result;
        }
        void display(){
            if(isEmpty()){
                cout <<" The stack is empty.\n";
                return;
            }
            cout <<"The stack is:\n";
            for(int i = 0; i < count; i++){
                cout << q_stack[i].id <<" : "<< q_stack[i].name <<'\n';
            }
            cout <<'\n';
        }
};
int main(){
    Stack student(3);
    Node result = student.pop();
    cout << result.id <<" : "<< result.name <<'\n';
    student.display();
    
    return 0;
}