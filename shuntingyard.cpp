// queue: FIFO, first in first out, take from front, put at back
// stack: LIFO, last in first out, take from top, put on top
// numbers into queue, operators into stack

/*
 * Author: Armaan Hajar
 * Date: March 19, 2023
 * Description: Shunting Yard Algorithm
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

struct BinaryTree {
    char data;
    BinaryTree* right;
    BinaryTree* left;
    BinaryTree(char newData) {
        data = newData;
        right = NULL;
        left = NULL;
    }
};


void resetQueueAndStack(Node* queueHead, Node* stackHead);
void postfixToBinaryTree(Node* queueHead, BinaryTree* &treeRoot);
void treeToInfix(BinaryTree* treeRoot);
void treeToPrefix(BinaryTree* treeRoot);
void treeToPostfix(BinaryTree* treeRoot);

void dequeue(Node* &queueHead);
void enqueue(Node* &queueHead, char character);
void push(Node* &stackHead, char character);
void pop(Node* &stackHead);
char peek(Node* stackHead);

int precedence(char character);

int main() {
    Node* stackHead = NULL;
    Node* queueHead = NULL;
    char* expression = new char[100];

    cout << "----------------------------------------------------------" << endl;
    cout << "Input A Math Expression With No Spaces (Ex: 2+(2*6)-7^4):" << endl;
    cin.get(expression, 100);
    cin.ignore(1, '\n');

    for (int i = 0; i < strlen(expression); i++) {
        if (isdigit(expression[i])) { // if is a number
            enqueue(queueHead, expression[i]);
        }
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '^') { // if is an operator
            int o1 = precedence(expression[i]);
            int o2 = precedence(peek(stackHead));
            while (stackHead != NULL && peek(stackHead) != '(' && (o2 > o1 || (o1 == o2 && expression[i] != '^'))) {
                enqueue(queueHead, peek(stackHead));
                pop(stackHead);
            }
            push(stackHead, expression[i]);
        }
        else if (expression[i] == '(' || expression[i] == ')') {
            if (expression[i] == '(') {
                push(stackHead, expression[i]);
            }
            else if (expression[i] == ')') {
                while (peek(stackHead) != '(') {
                    enqueue(queueHead, peek(stackHead));
                    pop(stackHead);
                }
                pop(stackHead);
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
    while (stackHead != NULL) {
        enqueue(queueHead, peek(stackHead));
        pop(stackHead);
    }
    BinaryTree* treeRoot = NULL;
    postfixToBinaryTree(queueHead, treeRoot);

    cout << "Infix: ";
    treeToInfix(treeRoot);
    cout << endl;

    cout << "Prefix: ";
    treeToPrefix(treeRoot);
    cout << endl;

    cout << "Postfix: ";
    treeToPostfix(treeRoot);
    cout << endl;

    cout << "----------------------------------------------------------" << endl;

    return 0;
}

void postfixToBinaryTree(Node* queueHead, BinaryTree* &treeRoot) {
    if (queueHead == NULL) {
        return;
    }
    else {
        if (isdigit(queueHead->data)) {
            BinaryTree* newNode = new BinaryTree(queueHead->data);
            treeRoot = newNode;
        }
        else {
            BinaryTree* newNode = new BinaryTree(queueHead->data);
            treeRoot = newNode;
            postfixToBinaryTree(queueHead->getNext(), treeRoot->left);
            postfixToBinaryTree(queueHead->getNext()->getNext(), treeRoot->right);
        }
    }
}

void treeToInfix(BinaryTree* treeRoot) {
    if (treeRoot == NULL) {
        return;
    }
    if (treeRoot->data == '+' || treeRoot->data == '-' || treeRoot->data == '*' || treeRoot->data == '/' || treeRoot->data == '^') {
        cout << "(";
    }
    treeToInfix(treeRoot->left);
    cout << treeRoot->data;
    treeToInfix(treeRoot->right);
    if (treeRoot->data == '+' || treeRoot->data == '-' || treeRoot->data == '*' || treeRoot->data == '/' || treeRoot->data == '^') {
        cout << ")";
    }
}

void treeToPrefix(BinaryTree* treeRoot) {
    if (treeRoot != NULL) {
        cout << treeRoot->data;
        treeToPrefix(treeRoot->left);
        treeToPrefix(treeRoot->right);
    }
}

void treeToPostfix(BinaryTree* treeRoot) {
    if (treeRoot != NULL) {
        treeToPostfix(treeRoot->left);
        treeToPostfix(treeRoot->right);
        cout << treeRoot->data;
    }
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
        dequeue(queueHead);
    }
    while (stackHead->getNext() != NULL) {
        pop(stackHead);
    }
    dequeue(queueHead);
    pop(stackHead);
}

void dequeue(Node* &queueHead) { // remove first data value in queue
    if (queueHead == NULL) {
        cout << "Queue is empty" << endl;
    }
    else if (queueHead->getNext() != NULL) {
       queueHead = queueHead->getNext();
    }
    else if (queueHead->getNext() == NULL) {
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
    Node* newNode = new Node(character);
    if (stackHead == NULL) {
        stackHead = newNode;
    }
    else {
        Node* temp = stackHead;
        stackHead = newNode;
        stackHead->next = temp;
    }
}

void pop(Node* &stackHead) { // remove last data value in stack
    if (stackHead == NULL) {
        return;
    }
    Node* next = stackHead->getNext();
    delete stackHead;
    stackHead = next;
}

char peek(Node* stackHead) { // look at top data value in stack
    if (stackHead == NULL) {
        return 0;
    }
    return stackHead->data;
}