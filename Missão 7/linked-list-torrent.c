#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define SEPARATOR "-------------------------------"

#define MAX_STR_SIZE 150

#define MENU_CADASTRAR_TORRENT 1
#define MENU_BUSCAR_TORRENT 2
#define MENU_LISTAR_TORRENT 3
#define MENU_SAIR 4

#define CLEAR "clear"

typedef struct Torrent {
    char title[MAX_STR_SIZE] ;
    char link[MAX_STR_SIZE] ;
    struct Torrent* dataLink ;
} Torrent ;

//------------------------------------------------
// # Node Utility Methods
//------------------------------------------------

//Pushes a node to the top and then returns it
Torrent* pushNode(Torrent* head, char link[], char title[]) {
    Torrent* newNode = (Torrent*) malloc(sizeof(Torrent));

    strcpy(newNode -> title, title);
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
Torrent* insertNodeAtEnd(Torrent* head, char link[], char title[]) {
    if (!head)
        return pushNode(head, link, title);

    Torrent* lastNode = getLastNode(head);
    Torrent* newNode = malloc(sizeof(Torrent));

    strcpy(newNode -> title, title);
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

    //If the target is the top itself
    if (!strcmp(head -> link, link))
        return head ;

    Torrent* current = malloc(sizeof(Torrent)) ;

    char* copyId = malloc(MAX_STR_SIZE);
    char* copyTitle = malloc(MAX_STR_SIZE);

    Torrent* target = getNodeByIndex(head, nodeIndex(head, link));

    strcpy(copyId, link);
    strcpy(copyTitle, target -> title);

    current = removeNode(head, link);
    current = pushNode(head, copyId, copyTitle);

    return current ;
}

//------------------------------------------------
// # Main Methods
//------------------------------------------------

//Utilidade de design
void printHeader (char text[]) {
    printf("%s\n%s\n%s\n", SEPARATOR, text, SEPARATOR);
}

//Shows the Torrent chain
void showNodeChain(Torrent* head) {
    printHeader("Torrents cadastrados");

    Torrent* aux = head ;

    while (aux) {
        printf("Titulo: %s\nLink: %s\n%s\n", aux -> title, aux -> link, SEPARATOR);
        aux = aux -> dataLink ;
    }
}

//Adiciona um torrent na lista encadeada
Torrent* cadastrarTorrent(Torrent* topo) {
    printHeader("Cadastrar torrent");

    char title[MAX_STR_SIZE] ;
    char link[MAX_STR_SIZE] ;

    printf("Nome do torrent: ");
    scanf(" %[^\n]s", title);
    
    printf("Link do torrent: ");
    scanf(" %[^\n]s", link);

    printf(SEPARATOR);
    printf("\nTorrent cadastrado com sucesso!\n%s\n", SEPARATOR);

    return pushNode(topo, link, title) ;
}

//Pesquisa um torrent na lista e leva ele para o topo
Torrent* pesquisarTorrent(char* nome, Torrent* topo) {
    Torrent* aux = topo ;
    Torrent* result = NULL ;

    int counter = 0 ;
    
    while (aux) {
        counter ++ ;

        if (!strcmp(aux -> title, nome)) {
            result = malloc(sizeof(Torrent));
            result = getNodeByIndex(topo, counter);
            break ;
        }

        aux = aux -> dataLink ;
    }
    
    return result ;
}

//Menu de pesquisa do torrent
Torrent* menuPesquisaTorrent(Torrent* topo) {
    system(CLEAR);
    printHeader("Busar torrent");

    char nome[MAX_STR_SIZE] ;

    printf("Insira o nome do torrent que deseja buscar: ");
    scanf(" %[^\n]s", nome);

    Torrent* resultado = pesquisarTorrent(nome, topo);

    if (!resultado){
        printf("Torrent não encontrado!\n%s\n", SEPARATOR);
        return topo ;
    } else {
        printf("%s\nNome: %s\nLink: %s\n%s\n", SEPARATOR, resultado -> title, resultado -> link, SEPARATOR);
        Torrent* foundTorrent = bringNodeToTop(topo, resultado -> link);
        return foundTorrent ;
    }
}

//Mostra um menu com as opções disponíveis
int optionsMenu() {
    system(CLEAR);

    printHeader("iTorrente");

    printf("%d - Cadastrar torrent", MENU_CADASTRAR_TORRENT);
    printf("\n%d - Buscar torrent", MENU_BUSCAR_TORRENT);
    printf("\n%d - Listar torrents", MENU_LISTAR_TORRENT);
    printf("\n%d - Sair", MENU_SAIR);

    printf("\n%s\n", SEPARATOR);
    printf("Selecione a opção desejada: ");

    int selected = -1 ;
    scanf(" %d", &selected);

    system(CLEAR);

    return selected ;
}

//Método principal
int main() {
    Torrent* torrent = NULL ;

    while (1) {
        switch (optionsMenu()) {
            case MENU_CADASTRAR_TORRENT:
                torrent = cadastrarTorrent(torrent);
                break;

            case MENU_BUSCAR_TORRENT:
                torrent = menuPesquisaTorrent(torrent);
                break;

            case MENU_LISTAR_TORRENT:
                showNodeChain(torrent);
                break;

            case MENU_SAIR:
                return 0 ;
                break;

            default:
                printHeader("Opção desconhecida!");
                break;
        }

        printf("Pressione ENTER para continuar...");
        setbuf(stdin, NULL);
        getchar();
    }

    return 0 ;
}