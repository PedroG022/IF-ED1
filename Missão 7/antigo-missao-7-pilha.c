#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define SEPARATOR "=============================="
#define CLEAR "clear"

#define MAX_STRING_SIZE 2

//Opções do menu

#define MENU_CADASTRAR_TORRENT 1
#define MENU_BUSCAR_TORRENT 2
#define MENU_LISTAR_TORRENT 3
#define MENU_SAIR 4

//Definição dos tipos

typedef struct Torrent {
    char titulo[MAX_STRING_SIZE] ;
    char link[MAX_STRING_SIZE] ;
    struct Torrent *proximo ;
} Torrent ;

//Utilidade de design
void printHeader (char text[]) {
    printf("%s\n%s\n%s\n", SEPARATOR, text, SEPARATOR);
}

//Adiciona um torrent na lista encadeada
Torrent* cadastrarTorrent(Torrent* topo) {
    printHeader("Cadastrar torrent");

    Torrent* torrent = malloc(sizeof(Torrent));

    printf("Nome do torrent: ");
    scanf(" %[^\n]s", torrent -> titulo);
    
    printf("Link do torrent: ");
    scanf(" %[^\n]s", torrent -> link);

    torrent -> proximo = topo ;

    printf(SEPARATOR);
    printf("\nTorrent cadastrado com sucesso!\n%s\n", SEPARATOR);

    return torrent ;
}

//Pesquisa um torrent na lista e leva ele para o topo
Torrent* pesquisarTorrent(char* nome, Torrent* topo) {
    int encontrado = 0 ;
    int todosPercorridos = 0 ;

    Torrent* copia = topo ;
    Torrent* resultado = NULL ;

    while (encontrado == 0 && todosPercorridos == 0) {
        if (!topo) {
            todosPercorridos = 1 ;
            break ;
        }

        if (strcmp(topo -> titulo, nome) == 0) {
            encontrado = 1 ;
            resultado = topo ;

            while (copia -> proximo) {
                if (strcmp(copia -> proximo -> titulo, nome) == 0) {
                    free(copia -> proximo);
                }
            }
            

            resultado -> proximo = copia ;
            break ;
        } else topo = topo -> proximo ;
    }

    return resultado ;
}

//Lista todos os torrents cadastrados
void listarTorrents(Torrent* topo) {
    printHeader("Torrents cadastrados");

    while (topo) {
        printf("Nome: %s\nLink: %s\n%s\n", topo -> titulo, topo -> link, SEPARATOR);
        topo = topo -> proximo ;
    }
}

//Menu de pesquisa do torrent
Torrent* menuPesquisaTorrent(Torrent* topo) {
    system(CLEAR);
    printHeader("Busar torrent");

    char nome[MAX_STRING_SIZE] ;

    printf("Insira o nome do torrent que deseja buscar: ");
    scanf(" %[^\n]s", nome);

    Torrent* resultado = pesquisarTorrent(nome, topo);

    if (!resultado)
        printf("\nTorrent não encontrado!\n");
    else {
        printf("%s\nNome: %s\nLink: %s\n%s\n", SEPARATOR, resultado -> titulo, resultado -> link, SEPARATOR);
        *topo = *resultado ;
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
    Torrent* topo = NULL ;

    while (1) {
        switch (optionsMenu()) {
            case MENU_CADASTRAR_TORRENT:
                topo = cadastrarTorrent(topo);
                break;

            case MENU_BUSCAR_TORRENT:
                menuPesquisaTorrent(topo);
                break;

            case MENU_LISTAR_TORRENT:
                listarTorrents(topo);
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