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
int nodeIndexByLink(Torrent* head, char link[]) {
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

//Returns a node's index given its title
int nodeIndexByTitle(Torrent* head, char title[]) {
    Torrent* aux = head ; 
    int counter = 0 ;
    int result = -1 ;

    while (aux) {
        counter ++ ;

        if (!strcmp(aux -> title, title)) {
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
        int nextNodeIndex = nodeIndexByLink(head, aux -> link) + 1 ;
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

    Torrent* target = getNodeByIndex(head, nodeIndexByLink(head, link));

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

    int validTitle = 0 ;
    int validLink = 0 ;

    do {
        printf("Nome do torrent: ");
        scanf(" %[^\n]s", title);

        if (nodeIndexByTitle(topo, title) <= 0)
            validTitle = 1 ;
        else printf("Já existe um torrent com este título!\n");

    } while (!validTitle) ;

    do {
        printf("Link do torrent: ");
        scanf(" %[^\n]s", link);

        if (nodeIndexByLink(topo, link) <= 0)
            validLink = 1 ;
        else printf("Já existe um torrent com este link!\n");
        
    } while (!validLink) ;

    printf(SEPARATOR);
    printf("\nTorrent cadastrado com sucesso!\n%s\n", SEPARATOR);

    return pushNode(topo, link, title) ;
}

//Menu de pesquisa do torrent
Torrent* menuPesquisaTorrent(Torrent* topo) {
    system(CLEAR);
    printHeader("Busar torrent");

    char pesquisa[MAX_STR_SIZE] ;

    printf("Insira o nome do torrent que deseja buscar: ");
    scanf(" %[^\n]s", pesquisa);

    int foundResults = 0 ;
    Torrent* resultado = malloc(sizeof(Torrent));

    Torrent* aux = topo ;

    //trim()
    //Remove os espaços da pesquisa
    for (int i = 0 ; i < strlen(pesquisa) ; i ++ )
        if (pesquisa[i] == 32)
            pesquisa[i] = pesquisa [i+1] ;

    while (aux) {
        char trimmedTitle[MAX_STR_SIZE];
        strcpy(trimmedTitle, aux -> title);

        //trim()
        //Remove os espaços do titulo
        for (int i = 0 ; i < strlen(trimmedTitle) ; i ++)
            if(trimmedTitle[i] == 32)
                trimmedTitle[i] = trimmedTitle[i+1] ;

        //Se o tamanho da pesquisa for maior que o nome do torrent
        //logicamente, este não é o nosso alvo
        if (strlen(pesquisa) > strlen(trimmedTitle)) 
			aux = aux -> dataLink ;

        //Comparação ignorando CASE (MAÍUSCULO e minúsculo)
        //Optei por usar uma função da lib string, só que também
        //é possivel fazer manualmente, verificando a diferença de 32
        //no identificador de um char. Se ele está dentro de um range,
        //significa que é maíusculo (ou minúsculo). Para tornar ele
        //é necessário apenas somar ou subtrair 32. (Vide tabela ASCII)
        if (!strcasecmp(pesquisa, trimmedTitle)) {
            foundResults ++ ;
            *resultado = *aux ;
            break ;
        }

        //Método da lib string, verifica a diferença entre uma determinada
        //quantia de caractéres em duas strings
        if (!strncasecmp(pesquisa, trimmedTitle, 4)){
            resultado = aux ;
            foundResults ++ ;
            break ;
        }
        
        aux = aux -> dataLink ;
    }

    if (!resultado || foundResults == 0) {
        printf("Torrent não encontrado!\n%s\n", SEPARATOR);
        return topo ;
    } else if (foundResults == 1) {
        printf("%s\nNome: %s\nLink: %s\n%s\n", SEPARATOR, resultado -> title, resultado -> link, SEPARATOR);
        Torrent* foundTorrent = bringNodeToTop(topo, resultado -> link);
        return foundTorrent ;
    } else {
        return topo ;
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