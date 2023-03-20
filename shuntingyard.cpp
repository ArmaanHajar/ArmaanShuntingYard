// queue: FIFO, first in first out
// stack: LIFO, last in first out
// numbers into queue, operators into stack

/*
 * Author: Armaan Hajar
 * Date: March 19, 2023
 * Description: Shunting Yard Algorithm
 * Used the Wikipedia pseudocode for the shunting yard algorithm and binary expression tree
 * Shunting Yard: https://en.wikipedia.org/wiki/Shunting-yard_algorithm
 * Binary Expresion Tree: https://en.wikipedia.org/wiki/Binary_expression_tree
 */

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

// Node struct for queue and stack
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

// Binary Tree struct for binary expression tree
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

// function prototypes
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

    for (int i = 0; i < strlen(expression); i++) { // loop through expression
        if (isdigit(expression[i])) { // if is a number
            enqueue(queueHead, expression[i]);
        }
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '^') { // if is an operator
            int o1 = precedence(expression[i]); // precedence of current operator
            int o2 = precedence(peek(stackHead)); // precedence of operator on top of stack
            while (stackHead != NULL && peek(stackHead) != '(' && (o2 > o1 || (o1 == o2 && expression[i] != '^'))) {
                // while stack is not empty, top of stack is not a left parenthesis, and precedence of top of stack is greater or equal to precedence of current operator and not an exponent
                enqueue(queueHead, peek(stackHead));
                pop(stackHead);
            }
            push(stackHead, expression[i]);
        }
        else if (expression[i] == '(' || expression[i] == ')') { // if is a parenthesis
            if (expression[i] == '(') { // if is a left parenthesis
                push(stackHead, expression[i]);
            }
            else if (expression[i] == ')') { // if is a right parenthesis
                while (peek(stackHead) != '(') {
                    enqueue(queueHead, peek(stackHead));
                    pop(stackHead);
                }
                pop(stackHead);
            }
        }
        else { // if is an invalid character
            cout << "Invalid Input" << endl;
            for (int i = 0; i < strlen(expression); i++) {
                expression[i] = NULL;
            }
            resetQueueAndStack(queueHead, stackHead);
        }
    }
    while (stackHead != NULL) { // put all remaining operators in stack into queue
        enqueue(queueHead, peek(stackHead));
        pop(stackHead);
    }
    
    // initialize binary expression tree
    BinaryTree* treeRoot = NULL;
    postfixToBinaryTree(queueHead, treeRoot);

    // print out results
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

void postfixToBinaryTree(Node* queueHead, BinaryTree* &treeRoot) { // convert postfix expression to binary expression tree
    vector<BinaryTree*> treeStack;
    Node* current = queueHead;
    while (current != NULL) { // loop through queue
        if (isdigit(current->data)) { // if is a number
            treeStack.push_back(new BinaryTree(current->data));
        }
        else { // if is an operator
            BinaryTree* newBinaryTree = new BinaryTree(current->data);
            newBinaryTree->right = treeStack.back();
            treeStack.pop_back();
            newBinaryTree->left = treeStack.back();
            treeStack.pop_back();
            treeStack.push_back(newBinaryTree);
        }
        current = current->getNext(); // move to next node
    }
    treeRoot = treeStack.back(); // set treeRoot to root of binary expression tree
}

void treeToInfix(BinaryTree* treeRoot) { // print out binary expression tree in infix notation
    if (treeRoot == NULL) {
        return;
    }
    if (treeRoot->data == '+' || treeRoot->data == '-' || treeRoot->data == '*' || treeRoot->data == '/' || treeRoot->data == '^') { // if is an operator
        cout << "("; // add left parenthesis
    }
    treeToInfix(treeRoot->left); // print out left subtree
    cout << treeRoot->data; // print out root
    treeToInfix(treeRoot->right); // print out right subtree
    if (treeRoot->data == '+' || treeRoot->data == '-' || treeRoot->data == '*' || treeRoot->data == '/' || treeRoot->data == '^') { // if is an operator
        cout << ")"; // add right parenthesis
    }
}

void treeToPrefix(BinaryTree* treeRoot) { // print out binary expression tree in prefix notation
    if (treeRoot != NULL) { // if tree is not empty
        cout << treeRoot->data; // print out root
        treeToPrefix(treeRoot->left); // print out left subtree
        treeToPrefix(treeRoot->right); // print out right subtree
    }
}

void treeToPostfix(BinaryTree* treeRoot) { // print out binary expression tree in postfix notation
    if (treeRoot != NULL) { // if tree is not empty
        treeToPostfix(treeRoot->left); // print out left subtree
        treeToPostfix(treeRoot->right); // print out right subtree
        cout << treeRoot->data; // print out root
    }
}

int precedence(char character) { // return precedence of operator
    if (character == '^') { // exponents have highest precedence
        return 3;
    }
    else if (character == '*' || character == '/') { // multiplication and division have second highest precedence
        return 2;
    }
    else if (character == '+' || character == '-') { // addition and subtraction have third highest precedence
        return 1;
    }
    else {
        return 0;
    }
}

void resetQueueAndStack(Node* queueHead, Node* stackHead) { // reset queue and stack
    while (queueHead->getNext() != NULL) { // delete all nodes in queue
        dequeue(queueHead);
    }
    while (stackHead->getNext() != NULL) { // delete all nodes in stack
        pop(stackHead);
    }
    dequeue(queueHead);
    pop(stackHead);
}

void dequeue(Node* &queueHead) { // remove first data value in queue
    if (queueHead == NULL) { // if queue is empty
        cout << "Queue is empty" << endl;
    }
    else { // if queue is not empty
        Node* temp = queueHead;
        queueHead = queueHead->getNext();
        delete temp;
    }
}

void enqueue(Node* &queueHead, char character) { // put at back of the queue
    Node* newCharacter = new Node(character);
    if (queueHead == NULL) { // if queue is empty
        queueHead = newCharacter;
    }
    else { // if queue is not empty
        Node* temp = queueHead;
        while (temp->getNext() != NULL) { // loop through queue
            temp = temp->getNext();
        }
        temp->setNext(newCharacter);
    }
}

void push(Node* &stackHead, char character) { // put at the top of the stack
    Node* newNode = new Node(character);
    if (stackHead == NULL) { // if stack is empty
        stackHead = newNode;
    }
    else { // if stack is not empty
        Node* temp = stackHead;
        stackHead = newNode;
        stackHead->next = temp;
    }
}

void pop(Node* &stackHead) { // remove last data value in stack
    if (stackHead == NULL) { // if stack is empty
        return;
    }
    Node* next = stackHead->getNext();
    delete stackHead;
    stackHead = next;
}

char peek(Node* stackHead) { // look at top data value in stack
    if (stackHead == NULL) { // if stack is empty
        return 0;
    }
    return stackHead->data;
}