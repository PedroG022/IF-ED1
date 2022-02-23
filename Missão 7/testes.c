#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define separator "-------------------------------"

typedef struct Node {
    int data ;
    struct Node* link;
} Node ;

//Returns the top node
Node* push(Node* head, int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));

    newNode -> data = data ;
    newNode -> link = head ;

    head = newNode ;
}

//Returns the bottom node
Node* getLastNode(Node* node) {
    Node* aux = node ;

    while (aux -> link) {
        aux = aux -> link ;
    }

    return aux ;
}

//Inserts a node at the last position
Node* insertAtEnd(Node* head, int data) {
    if (!head)
        return push(head, data);

    Node* lastNode = getLastNode(head);
    Node* newNode = malloc(sizeof(Node));

    newNode -> data = data ;
    newNode -> link = NULL ;

    lastNode -> link = newNode ;

    return head ;
}

//Returns a node's index given its data
int nodeIndex(Node* head, int data) {
    Node* aux = head ; 
    int counter = 0 ;
    int result = -1 ;

    while (aux) {
        counter ++ ;

        if (aux -> data == data) {
            result = counter ;
            break ;
        }
        aux = aux -> link ;
    }

    return result ;
}

//Returns a node given an index
Node* getNodeByIndex(Node* head, int index) {
    Node* aux = head ; 
    Node* result = malloc(sizeof(Node)) ;

    int counter = 0 ;

    while (aux) {
        counter ++ ;

        if (counter == index) {
            result = aux ;
            break ;
        }
        aux = aux -> link ;
    }

    return result ;
}

//Removes a node given its data
//Pass the link from its neighbours
Node* removeNode(Node* head, int data) {
    Node* aux = head ; 

    while (aux && aux -> link) {
        int nextNodeIndex = nodeIndex(head, aux -> data) + 1 ;
        Node* next = (Node*) getNodeByIndex(head, nextNodeIndex);
        
        if (next -> data == data) {
            aux -> link = next -> link ;
            free(next);
        }

        aux = aux -> link ;
    }

    return head ;
}

//Brings a node to the top basing on its data
Node* bringToTop(Node* head, int data) {
    Node* current = malloc(sizeof(Node)) ;

    current = removeNode(head, data);
    current = push(head, data);

    return current ;
}

//Shows the Node chain
void showChain(Node* head) {
    Node* aux = head ;

    while (aux) {
        printf("Data: %d\n", aux -> data);
        aux = aux -> link ;
    }
}

void executeTests(){
    Node* head = NULL ;

    head = insertAtEnd(head, -1);
    head = insertAtEnd(head, -2);
    head = insertAtEnd(head, -3);
    head = insertAtEnd(head, -4);
    head = insertAtEnd(head, -5);

    head = push(head, 0);
    head = push(head, 1);
    head = push(head, 2);


    showChain(head);

    Node* lastNode = getLastNode(head);

    printf("%s\n", separator);
    printf("Bottom node: %d\n", lastNode -> data);
    printf("Top node: %d\n", head -> data);
    printf("Bottom node index: %d\n", nodeIndex(head, lastNode -> data));

    Node* gotNode = getNodeByIndex(head, 3);

    printf("Node gotten from index #3: %d\n", gotNode -> data);

    printf("%s\n", separator);
    printf("List with index #3 removed:\n%s\n",separator);

    head = removeNode(head, getNodeByIndex(head, 3) -> data);
    showChain(head);

    printf("%s\n", separator);
    printf("List with index #3 moved to the top:\n%s\n",separator);

    head = bringToTop(head, getNodeByIndex(head,4) -> data);
    showChain(head);
}

int main () {
    executeTests();
    return 0 ;
}