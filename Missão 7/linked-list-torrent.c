#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define separator "-------------------------------"
#define MAX_STR_SIZE 5

typedef struct Torrent {
    char id[MAX_STR_SIZE] ;
    struct Torrent* link;
} Torrent ;

//Pushes a node to the top and then returns it
Torrent* pushNode(Torrent* head, char id[]) {
    Torrent* newNode = (Torrent*) malloc(sizeof(Torrent));

    strcpy(newNode -> id, id);
    newNode -> link = head ;

    head = newNode ;
}

//Returns the bottom node
Torrent* getLastNode(Torrent* node) {
    Torrent* aux = node ;

    while (aux -> link) {
        aux = aux -> link ;
    }

    return aux ;
}

//Inserts a node at the last position
Torrent* insertNodeAtEnd(Torrent* head, char id[]) {
    if (!head)
        return pushNode(head, id);

    Torrent* lastNode = getLastNode(head);
    Torrent* newNode = malloc(sizeof(Torrent));

    strcpy(newNode -> id, id);
    newNode -> link = NULL ;

    lastNode -> link = newNode ;

    return head ;
}

//Returns a node's index given its id
int nodeIndex(Torrent* head, char id[]) {
    Torrent* aux = head ; 
    int counter = 0 ;
    int result = -1 ;

    while (aux) {
        counter ++ ;

        if (!strcmp(aux -> id, id)) {
            result = counter ;
            break ;
        }
        aux = aux -> link ;
    }

    return result ;
}

//Returns a node given an index
Torrent* getNodeByIndex(Torrent* head, int index) {
    Torrent* aux = head ; 
    Torrent* result = malloc(sizeof(Torrent)) ;

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

//Removes a node given its id
Torrent* removeNode(Torrent* head, char id[]) {
    Torrent* aux = head ; 
    
    //For the first item
    if (!strcmp(head -> id, id)) {
        Torrent* second = head -> link ;
        free(head);
        return(second);
    }

    while (aux && aux -> link) {
        int nextNodeIndex = nodeIndex(head, aux -> id) + 1 ;
        Torrent* next = (Torrent*) getNodeByIndex(head, nextNodeIndex);
        
        if (!strcmp(next -> id, id)) {
            aux -> link = next -> link ;
            free(next);
        }

        aux = aux -> link ;
    }

    return head ;
}

//Brings a node to the top basing on its id
Torrent* bringNodeToTop(Torrent* head, char id[]) {
    Torrent* current = malloc(sizeof(Torrent)) ;

    char* copyId = malloc(MAX_STR_SIZE);
    strcpy(copyId, id);

    current = removeNode(head, id);
    current = pushNode(head, copyId);

    return current ;
}

//Shows the Torrent chain
void showNodeChain(Torrent* head) {
    Torrent* aux = head ;

    while (aux) {
        printf("Data: %s\n", aux -> id);
        aux = aux -> link ;
    }
}

void executeTests(){
    Torrent* head = NULL ;

    head = pushNode(head, "e");
    head = pushNode(head, "d");
    head = pushNode(head, "c");
    head = pushNode(head, "b");
    head = pushNode(head, "a");

    showNodeChain(head);

    Torrent* lastNode = getLastNode(head);

    printf("%s\n", separator);
    printf("Top node: %s - Top node index: %d\n", head -> id, nodeIndex(head, head -> id));
    printf("Bottom node: %s - Bottom node index: %d\n", lastNode -> id, nodeIndex(head, lastNode -> id));

    Torrent* gotNode = getNodeByIndex(head, 3);

    printf("Node gotten from index #3: %s\n", gotNode -> id);

    printf("%s\n", separator);
    printf("List with index #3 removed:\n%s\n",separator);

    head = removeNode(head, getNodeByIndex(head, 3) -> id);
    showNodeChain(head);

    printf("%s\n", separator);
    printf("List with index #3 moved to the top:\n%s\n",separator);

    head = bringNodeToTop(head, getNodeByIndex(head,3) -> id);
    showNodeChain(head);
}

int main () {
    executeTests();
    return 0 ;
}