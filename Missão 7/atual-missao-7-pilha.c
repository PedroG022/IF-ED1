#include <stdio.h>
#include <stdlib.h>
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

//Obtem o primeiro torrent
Torrent* obterTorrentBase(Torrent* torrent) {
    Torrent* aux = torrent ;

    while (aux -> proximo) {
        aux = aux -> proximo ;
    }

    return aux ;
}

//Pesquisa um torrent na lista e leva ele para o topo
Torrent* pesquisarTorrent(char* nome, Torrent* topo) {
    int encontrado = 0 ;
    
    Torrent* aux = topo ;
    Torrent* mover = malloc(sizeof(Torrent)) ;

    while (encontrado == 0) {
        if (!aux) break ;

        if(!aux -> proximo)
            return topo ;
        
        if (aux -> proximo && !strcmp(aux -> proximo -> titulo, nome)) {
            encontrado = 1 ;
            
            //Torrent a ser movido pro topo
            *mover = *aux -> proximo ;

            Torrent antigoPonteiro ;

            if(!mover -> proximo)
                return obterTorrentBase(topo) ;
                
            else
                antigoPonteiro = *mover -> proximo ;

            //O torrent agora é substuido pro endereço antigo do  agora topo
            *aux -> proximo = antigoPonteiro ;
            *mover -> proximo = *topo ;
            break ;
        } else aux = aux -> proximo ;
    }

    return mover ;
}

//Menu de pesquisa do torrent
void menuPesquisaTorrent(Torrent* topo) {
    system(CLEAR);
    printHeader("Busar torrent");

    char nome[MAX_STRING_SIZE] ;

    printf("Insira o nome do torrent que deseja buscar: ");
    scanf(" %[^\n]s", nome);

    Torrent* resultado = pesquisarTorrent(nome, topo);

    if (!resultado)
        printf("Torrent não encontrado!\n%s\n", SEPARATOR);
    else {
        printf("%s\nNome: %s\nLink: %s\n%s\n", SEPARATOR, resultado -> titulo, resultado -> link, SEPARATOR);
        *topo = *resultado ;
    }
}

//Lista todos os torrents cadastrados
void listarTorrents(Torrent* topo) {
    printHeader("Torrents cadastrados");

    while (topo) {
        printf("Nome: %s\nLink: %s\n%s\n", topo -> titulo, topo -> link, SEPARATOR);
        topo = topo -> proximo ;
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
    Torrent* primeiro = NULL ;

    while (1) {
        switch (optionsMenu()) {
            case MENU_CADASTRAR_TORRENT:
                primeiro = cadastrarTorrent(primeiro);
                break;

            case MENU_BUSCAR_TORRENT:
                menuPesquisaTorrent(primeiro);
                break;

            case MENU_LISTAR_TORRENT:
                listarTorrents(primeiro);
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