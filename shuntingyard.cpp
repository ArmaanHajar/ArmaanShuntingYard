// queue: FIFO, first in first out, take from front, put at back
// stack: LIFO, last in first out, take from top, put on top
// numbers into queue, operators into stack

#include <iostream>
#include <cstring>

using namespace std;

void dequeue(Node* printHead, char* character);
void enqueue(Node* printHead, char* character);
void push(Node* printHead, Node* stackHead, char* character);
void pop(Node* printHead, Node* stackHead, char* character);
void peek(Node* printHead, Node* stackHead, char* character);

struct Node {
    char* data;
    Node* next;
    Node(char* nextData) {
        data = nextData;
        next = NULL;
    }
    Node* getNext() {
        return next;
    }
    void setNext(Node* nextNode) {
        next = nextNode;
    }
};

int main() {
    Node* stackHead = NULL;
    Node* printHead = NULL;
    int* equation = new int[100];
    cout << "Input A Math Equation With No Spaces (Ex: 2+(2*6)-7^4):"
    cin.get(equation, 50);
    cin.ignore(1, '\n');

    for (int i = 0; i < strlen(equation); i++) {
        if (isdigit[equation[i]]) { // if is a number
            enqueue(equation[i]);
        }
        else if (equation[i] == '+' || equation[i] == '-' || equation[i] == '*' || equation[i] == '/' || equation[i] == '^' || equation[i] == '(' || equation[i] == ')') { // if is an operator
            push(equation[i]);
        }
    }

    return 0;
}

void dequeue(Node* printHead, char* character) { // take from front, stack

}

void enqueue(Node* printHead, char* character) { // put at back, stack
    
}

void push(Node* printHead, Node* stackHead, char* character) { // put on top, stack

}

void pop(Node* printHead, Node* stackHead, char* character) { // take from top, queue

}

void peek(Node* printHead, Node* stackHead, char* character) { // look at top, queue

}