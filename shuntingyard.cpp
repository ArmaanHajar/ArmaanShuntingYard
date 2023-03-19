// queue: FIFO, first in first out, take from front, put at back
// stack: LIFO, last in first out, take from top, put on top
// numbers into queue, operators into stack

/*
 * Author: Armaan Hajar
 * Date: March 17, 2023
 * Description: This program will take a math expression and convert it to postfix notation, aka the shunting yard algorithm
 */

#include <iostream>
#include <cstring>

using namespace std;

struct Node {
    char data;
    Node* next;
    Node(char nextData) {
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

void resetQueueAndStack(Node* queueHead, Node* stackHead);
void printPostfix(Node* queueHead, Node* stackHead);

void dequeue(Node* &queueHead, char character);
void enqueue(Node* &queueHead, char character);
void push(Node* &stackHead, char character);
void pop(Node* &stackHead, char character);
char peek(Node* stackHead);

int precedence(char character);

int main() {
    Node* stackHead = NULL;
    Node* queueHead = NULL;
    char* expression = new char[100];

    cout << "Input A Math Expression With No Spaces (Ex: 2+(2*6)-7^4):" << endl;
    cin.get(expression, 100);
    cin.ignore(1, '\n');

    for (int i = 0; i < strlen(expression); i++) {
        if (isdigit(expression[i])) { // if is a number
            enqueue(queueHead, expression[i]);
            cout << "queued " << expression[i] << endl;
        }
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '^') { // if is an operator
            while((stackHead != NULL) && //if there is something in the stack and
            ((precedence(peek(stackHead)) > precedence(expression[i])) || //if it takes precedence over the top of the stack or
            ((precedence(peek(stackHead)) == precedence(expression[i])) && expression[i] != '^')) && //if it has equal precedence and it's not power
            (peek(stackHead) != '(')){//and it's not an opening parenthesis
                enqueue(queueHead, peek(stackHead));
                pop(stackHead, peek(stackHead));
            }
            push(stackHead, expression[i]);
            cout << "pushed " << expression[i] << endl;
        }
        else if (expression[i] == '(' || expression[i] == ')') {
            if (expression[i] == '(') {
                push(stackHead, expression[i]);
                cout << "pushed " << expression[i] << endl;
            }
            else if (expression[i] == ')') {
                while (peek(stackHead) != '(') {
                    enqueue(queueHead, peek(stackHead));
                    pop(stackHead, peek(stackHead));
                }
                pop(stackHead, peek(stackHead));
            }
        }
        else {
            cout << "Invalid Input" << endl;
            for (int i = 0; i < strlen(expression); i++) {
                expression[i] = NULL;
            }
            resetQueueAndStack(queueHead, stackHead);
        }
    }
    cout << "Postfix: "; 
    printPostfix(queueHead, stackHead);
    cout << endl;
    return 0;
}

int precedence(char character) {
    if (character == '^') {
        return 3;
    }
    else if (character == '*' || character == '/') {
        return 2;
    }
    else if (character == '+' || character == '-') {
        return 1;
    }
    else {
        return 0;
    }
}

void resetQueueAndStack(Node* queueHead, Node* stackHead) {
    while (queueHead->getNext() != NULL) {
        dequeue(queueHead, queueHead->data);
    }
    while (stackHead->getNext() != NULL) {
        pop(stackHead, stackHead->data);
    }
    dequeue(queueHead, queueHead->data);
    pop(stackHead, stackHead->data);
}

void printPostfix(Node* queueHead, Node* stackHead) {
    char* outputPostfix = new char[100];
    int index = 0;
    while (queueHead->getNext() != NULL) {
        outputPostfix[index] = queueHead->data;
        index++;
    }
    for (int i = 0; i < strlen(outputPostfix); i++) {
        cout << outputPostfix[i];
    }
    cout << endl;
}

void dequeue(Node* &queueHead, char character) { // remove first data value in queue
    if (queueHead == NULL) {
        cout << "dequeue Queue is empty" << endl;
    }
    else if (queueHead->getNext() != NULL) {
       queueHead = queueHead->getNext();
    }
    else if (queueHead->getNext() == NULL) {
        cout << "dequeue The first data value in the queue is: " << queueHead->data << endl;
    }
    else {
        Node* temp = queueHead;
        while (temp->getNext() != NULL) {
            temp = temp->getNext();
        }
        cout << temp->data << endl;
    }
}

void enqueue(Node* &queueHead, char character) { // put at back of the queue
    Node* newCharacter = new Node(character);
    if (queueHead == NULL) {
        queueHead = newCharacter;
    }
    else {
        Node* temp = queueHead;
        while (temp->getNext() != NULL) {
            temp = temp->getNext();
        }
        temp->setNext(newCharacter);
    }
}

void push(Node* &stackHead, char character) { // put at the top of the stack
    Node* newCharacter = new Node(character);
    if (stackHead == NULL) {
        stackHead = newCharacter;
    }
    else {
        Node* temp = stackHead;
        while (temp->getNext() != NULL) {
            temp = temp->getNext();
        }
        temp->setNext(newCharacter);
    }
}

void pop(Node* &stackHead, char character) { // remove last data value in stack
    if (stackHead == NULL) {
        cout << "pop Stack is empty" << endl;
        return;
    }
    if (stackHead->getNext() != NULL) {
        stackHead = stackHead->getNext();
    }
    else stackHead = NULL;
}

char peek(Node* stackHead) { // look at top data value in stack
    char lastInStack = NULL;

    if (stackHead == NULL) {
        cout << "peek Stack is empty" << endl;
    }
    else {
        Node* temp = stackHead;
        while (temp->getNext() != NULL) {
            temp = temp->getNext();
        }
        lastInStack = temp->data;
        cout << "peek The top data value in the stack is: " << lastInStack << endl;
    }
    return lastInStack;
}