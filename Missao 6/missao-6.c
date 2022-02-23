#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------
//Constantes
//----------------------------------------------------

//Constantes gerais

#define MAX_STRING_SIZE 150
#define MAX_ARRAY_SIZE 20

//Opções de SO

#define CLEAR "clear"

//Design

#define SEPARATOR "=================================================="

//Constantes do menu

#define MENU_CADASTRAR 1
#define MENU_MOSTRAR_LIVROS 2
#define MENU_PRATELEIRAS 3
#define MENU_LISTAR_AREAS 4
#define MENU_LIVRO_POR_AREA 5
#define MENU_SAIR 6

//----------------------------------------------------
//Declaração de tipos
//----------------------------------------------------

//Declaração de tipos
typedef struct {
    char titulo[MAX_STRING_SIZE] ;
    char autor[MAX_STRING_SIZE] ;
    char areaConhecimento[MAX_STRING_SIZE] ;
    int ano ;
    int localizacao ;
    int id ;
} Livro ;

typedef struct {
    char areas[MAX_ARRAY_SIZE][MAX_STRING_SIZE] ;
    int tamanho ;
} ListaAreas ;

typedef struct {
    int tamanho ;
    char area[MAX_ARRAY_SIZE] ;
} Prateleira ;

typedef struct {
    Prateleira prateleiras[MAX_ARRAY_SIZE] ;
    int tamanho ;
} Armario ;

//----------------------------------------------------
//Outros
//----------------------------------------------------

//Printar menu simples
void printHeader(char title[]) {
    printf(SEPARATOR);
    printf("\n%s", title);
    printf("\n%s\n", SEPARATOR);
}

void menuPrateleiras(Livro livros[], int tamanhoLivros, ListaAreas lista) {
    system(CLEAR);
    printHeader("Prateleiras: ");
}

int obterPrateleiraVazia(Armario* armario, char area[]) {
    int tamanho = armario -> tamanho ;

    int resultado = 0 ;
    int achou = 0 ;

    for (int i = 0 ; i < tamanho ; i ++ ) {
        Prateleira prateleira = armario -> prateleiras[i] ;

        char areaPrat[MAX_STRING_SIZE];
        strcpy(areaPrat, prateleira.area);

        if (strcmp(areaPrat, area) == 0) {
            
            //Prateleira vazia encontrada
            if (prateleira.tamanho < 3) {
                achou = 1 ;
                prateleira.tamanho ++ ;
                armario -> prateleiras[i] = prateleira ;
                resultado = ++ i  ;
            }
        }
    }

    if (!achou) {
        Prateleira nova ;
        nova.tamanho = 1 ;
        strcpy(nova.area, area);
        armario -> prateleiras[armario -> tamanho] = nova ;
        armario -> tamanho ++ ;
        resultado = armario -> tamanho ;
    }

    return resultado ;
}

//----------------------------------------------------
//Áreas de Conhecimento
//----------------------------------------------------

//Mostrar as areas
void mostrarAreasDeConhecimento(ListaAreas listaAreas) {
    system(CLEAR);
    printHeader("Areas de Conhecimento cadastradas");
    
    for (int i = 0 ; i < listaAreas.tamanho ; i ++ ) {
        printf("%d: %s", i, listaAreas.areas[i]);

        //Se não for o último item, imprime uma linha
        if (!i == listaAreas.tamanho - 1)
            printf("\n");
    }

    printf("\n%s\n", SEPARATOR);
}

//Indica a posição de uma "Area" em uma lista, dado o seu nome
int localizarArea(ListaAreas* areas, char nome[]) {
    int posicao = -1 ;

    for (int i = 0 ; i < areas -> tamanho ; i ++ ) 
        if (strcmp(areas->areas[i], nome) == 0)
            posicao = i ;
    
    return posicao ;
}

//Coloca as áreas de determinado array em ordem alfabetica
void organizarAreas(ListaAreas* lista) {
    int size = lista -> tamanho ;

    for (int i = 0 ; i < size ; i ++)
        for (int j = 0 ; j < size - 1 ; j ++) {
            if (strcmp(lista -> areas[j], lista -> areas[j + 1]) > 0){
                char aux[MAX_STRING_SIZE] ;
                strcpy(aux, lista -> areas [j]);
                strcpy(lista -> areas [j], lista -> areas [j + 1]);
                strcpy(lista -> areas [j + 1], aux);
            }
        }
}

//----------------------------------------------------
//Funções do livro
//----------------------------------------------------

//Cadastro de livro
void cadastrarLivro(Livro livros[], int tamanhoLivros, ListaAreas* listaAreas, Armario* armario) {
    Livro livro ;

    system(CLEAR);
    printHeader("Cadastrar livro");
    
    printf("Título do livro: ");
    scanf(" %[^\n]s", livro.titulo);

    printf("Autor do livro: ");
    scanf(" %[^\n]s", livro.autor);

    printf("Área de conhe1cimento do livro: ");
    scanf(" %[^\n]s", livro.areaConhecimento);

    if (localizarArea(listaAreas, livro.areaConhecimento) < 0)
        strcpy(listaAreas -> areas[listaAreas -> tamanho++], livro.areaConhecimento);

    printf("Ano do livro: ");
    scanf(" %d", &livro.ano);

    livro.id = tamanhoLivros ;
    livro.localizacao = obterPrateleiraVazia(armario, livro.areaConhecimento);

    livros[tamanhoLivros] = livro ;

    printHeader("Livro cadastrado com sucesso!");
}

//Mostrar detalhes de um único livro
void mostrarLivro(Livro livro, int final) {
    printf(SEPARATOR);
    printf("\nTitulo: %s", livro.titulo);
    printf("\nAutor: %s", livro.autor);
    printf("\nAno: %d", livro.ano);
    printf("\nArea de Conhecimento: %s", livro.areaConhecimento);
    printf("\nLocalizacao: %d", livro.localizacao);
    printf("\nID: %d\n", livro.id);

    if (final)
        printf("%s\n", SEPARATOR);
}

//Mostrar todos os livros sem classificar
void mostratTodosLivros(Livro livro[], int tamanho) {
    for (int i = 0 ; i < tamanho ; i ++) {
        int final = (i == (tamanho - 1));
        mostrarLivro(livro[i], final);
    }
}

//Coloca os livros de determinado array em ordem alfabetica
void organizarLivros(Livro livros[], int tamanaho){
    for (int i = 0 ; i < tamanaho ; i ++ ) {
        for (int j = 0 ; j < tamanaho - 1 ; j ++ ) {
            if(strcmp(livros[j].titulo, livros[j + 1].titulo) > 0) {
                Livro aux = livros[j] ;
                livros[j] = livros[j + 1];
                livros[j + 1] = aux ;
            }
        }
    }
}

//Mostra todos os livros de uma determinada área
void mostrarLivroPorArea(Livro livros[], int tamanhoLivros, char areaDeConhecimento[]){
    Livro livrosDaArea[MAX_ARRAY_SIZE] ;
    int tamanhoLivrosDaArea = 0 ;

    for (int i = 0 ; i < tamanhoLivros ; i ++)
        if (strcmp(livros[i].areaConhecimento, areaDeConhecimento) == 0) 
            livrosDaArea[tamanhoLivrosDaArea++] = livros[i] ;

    organizarLivros(livrosDaArea, tamanhoLivrosDaArea);
    mostratTodosLivros(livrosDaArea, tamanhoLivrosDaArea);
}

//Pergunta ao usuário a área em que deve buscar os livros
void promptLivrosArea(Livro livros[], int tamanhoLivros) {
    system(CLEAR);
    printHeader("Mostrar livros por Área de Conhecimento");

    char area[MAX_STRING_SIZE] ;

    printf("Insira a área que deseja buscar: ");
    scanf(" %[^\n]s", area);

    mostrarLivroPorArea(livros, tamanhoLivros, area);
}

//Atualiza o id de um livro dado o índicde de uma determinada área
void atualizarLocalLivro(Livro livros[], int tamanho, ListaAreas* lista) {
    for (int i = 0 ; i < tamanho ; i ++ ) {
        livros[i].localizacao = localizarArea(lista, livros[i].areaConhecimento);
    }
}

//----------------------------------------------------
//Base
//----------------------------------------------------

//Menu principal da aplicação
int menu() {
    int option ;

    system(CLEAR);
    printHeader("Gerenciamento de livros");
    printf("Opções:");
    printf("\n\n%d - Cadastrar livro(s)", MENU_CADASTRAR);
    printf("\n%d - Mostrar todos os livros", MENU_MOSTRAR_LIVROS);
    printf("\n%d - Mostrar todos os livros (prateleiras)", MENU_PRATELEIRAS);
    printf("\n%d - Listar as Areas de Conhecimento", MENU_LISTAR_AREAS);
    printf("\n%d - Mostrar os livros por Areas de Conhecimento", MENU_LIVRO_POR_AREA);
    printf("\n%d - Sair", MENU_SAIR);
    printf("\n%s", SEPARATOR);

    printf("\nInsira a opção desejada: ");
    scanf(" %d", &option);

    system(CLEAR);

    return option ;
} 

//Método principal
int main () {
    Livro livros[MAX_ARRAY_SIZE] ;
    int tamanhoLivros = 0 ;
    
    ListaAreas areas ;
    areas.tamanho = 0 ;

    Armario armario ;
    armario.tamanho = 0 ;

    while (1) {
        organizarAreas(&areas);
        organizarLivros(livros, tamanhoLivros);
        //atualizarIdLivro(livros, tamanhoLivros, &lista);

        switch (menu()) {
            case MENU_CADASTRAR:
                cadastrarLivro(livros, tamanhoLivros++, &areas, &armario);
                break;

            case MENU_MOSTRAR_LIVROS:
                mostratTodosLivros(livros, tamanhoLivros);
                break;

            case MENU_LISTAR_AREAS:
                mostrarAreasDeConhecimento(areas);
                break;

            case MENU_LIVRO_POR_AREA:
                promptLivrosArea(livros, tamanhoLivros);
                break;

            case MENU_PRATELEIRAS:
                menuPrateleiras(livros, tamanhoLivros, areas);
                break;

            case MENU_SAIR:
                return 0 ;
                break;
        
            default:
                break;
        }

        printf("Pressione ENTER para continuar...");
        setbuf(stdin, NULL);
        getchar();
    }
    
    return 0 ;
}