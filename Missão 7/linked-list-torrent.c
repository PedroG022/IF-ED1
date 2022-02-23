#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define separator "-------------------------------"
#define MAX_STR_SIZE 5

typedef struct Torrent {
    char link[MAX_STR_SIZE] ;
    struct Torrent* dataLink;
} Torrent ;

//Pushes a node to the top and then returns it
Torrent* pushNode(Torrent* head, char link[]) {
    Torrent* newNode = (Torrent*) malloc(sizeof(Torrent));

    strcpy(newNode -> link, link);
    newNode -> dataLink = head ;

    head = newNode ;
}

//Returns the bottom node
Torrent* getLastNode(Torrent* node) {
    Torrent* aux = node ;

    while (aux -> dataLink) {
        aux = aux -> dataLink ;
    }

    return aux ;
}

//Inserts a node at the last position
Torrent* insertNodeAtEnd(Torrent* head, char link[]) {
    if (!head)
        return pushNode(head, link);

    Torrent* lastNode = getLastNode(head);
    Torrent* newNode = malloc(sizeof(Torrent));

    strcpy(newNode -> link, link);
    newNode -> dataLink = NULL ;

    lastNode -> dataLink = newNode ;

    return head ;
}

//Returns a node's index given its link
int nodeIndex(Torrent* head, char link[]) {
    Torrent* aux = head ; 
    int counter = 0 ;
    int result = -1 ;

    while (aux) {
        counter ++ ;

        if (!strcmp(aux -> link, link)) {
            result = counter ;
            break ;
        }
        aux = aux -> dataLink ;
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
        aux = aux -> dataLink ;
    }

    return result ;
}

//Removes a node given its link
Torrent* removeNode(Torrent* head, char link[]) {
    Torrent* aux = head ; 
    
    //For the first item
    if (!strcmp(head -> link, link)) {
        Torrent* second = head -> dataLink ;
        free(head);
        return(second);
    }

    while (aux && aux -> dataLink) {
        int nextNodeIndex = nodeIndex(head, aux -> link) + 1 ;
        Torrent* next = (Torrent*) getNodeByIndex(head, nextNodeIndex);
        
        if (!strcmp(next -> link, link)) {
            aux -> dataLink = next -> dataLink ;
            free(next);
        }

        aux = aux -> dataLink ;
    }

    return head ;
}

//Brings a node to the top basing on its link
Torrent* bringNodeToTop(Torrent* head, char link[]) {
    Torrent* current = malloc(sizeof(Torrent)) ;

    char* copyId = malloc(MAX_STR_SIZE);
    strcpy(copyId, link);

    current = removeNode(head, link);
    current = pushNode(head, copyId);

    return current ;
}

//Shows the Torrent chain
void showNodeChain(Torrent* head) {
    Torrent* aux = head ;

    while (aux) {
        printf("Data: %s\n", aux -> link);
        aux = aux -> dataLink ;
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
    printf("Top node: %s - Top node index: %d\n", head -> link, nodeIndex(head, head -> link));
    printf("Bottom node: %s - Bottom node index: %d\n", lastNode -> link, nodeIndex(head, lastNode -> link));

    Torrent* gotNode = getNodeByIndex(head, 3);

    printf("Node gotten from index #3: %s\n", gotNode -> link);

    printf("%s\n", separator);
    printf("List with index #3 removed:\n%s\n",separator);

    head = removeNode(head, getNodeByIndex(head, 3) -> link);
    showNodeChain(head);

    printf("%s\n", separator);
    printf("List with index #3 moved to the top:\n%s\n",separator);

    head = bringNodeToTop(head, getNodeByIndex(head,3) -> link);
    showNodeChain(head);
}

int main () {
    executeTests();
    return 0 ;
}