#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define separator "-------------------------------"

typedef struct Node {
    int data ;
    struct Node* link;
} Node ;

//Pushes a node to the top and then returns it
Node* pushNode(Node* head, int data) {
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
Node* insertNodeAtEnd(Node* head, int data) {
    if (!head)
        return pushNode(head, data);

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
Node* removeNode(Node* head, int data) {
    Node* aux = head ; 
    
    //For the first item
    if (head -> data == data) {
        Node* second = head -> link ;
        free(head);
        return(second);
    }

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
Node* bringNodeToTop(Node* head, int data) {
    if (head -> data == data)
        return head ;
        
    Node* current = malloc(sizeof(Node)) ;

    current = removeNode(head, data);
    current = pushNode(head, data);

    return current ;
}

//Shows the Node chain
void showNodeChain(Node* head) {
    Node* aux = head ;

    while (aux) {
        printf("Data: %d\n", aux -> data);
        aux = aux -> link ;
    }
}

void executeTests(){
    Node* head = NULL ;

    for (int i = 0 ; i < 5 ; i ++) {
        head = pushNode(head, i);
    }

    showNodeChain(head);

    Node* lastNode = getLastNode(head);

    printf("%s\n", separator);
    printf("Top node: %d - Top node index: %d\n", head -> data, nodeIndex(head, head -> data));
    printf("Bottom node: %d - Bottom node index: %d\n", lastNode -> data, nodeIndex(head, lastNode -> data));

    Node* gotNode = getNodeByIndex(head, 3);

    printf("Node gotten from index #3: %d\n", gotNode -> data);

    printf("%s\n", separator);
    printf("List with index #3 removed:\n%s\n",separator);

    head = removeNode(head, getNodeByIndex(head, 3) -> data);
    showNodeChain(head);

    printf("%s\n", separator);
    printf("List with index #3 moved to the top:\n%s\n",separator);

    head = bringNodeToTop(head, getNodeByIndex(head,3) -> data);
    showNodeChain(head);
}

int main () {
    executeTests();
    return 0 ;
}