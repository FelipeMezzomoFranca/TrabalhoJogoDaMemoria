#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h> // Para o sleep no windows
#include <stdbool.h>

#define linhas 4
#define colunas 4
#define total (linhas * colunas)

typedef struct Carta {
    int valor;
    bool revelada;
} Carta;

// Funções Prototipos
int menuPrincipal(int opcao);
void linha();

int* gerarVetorPares(int totalCartas) {
    if (totalCartas % 2 != 0) return NULL;

    int* vet = malloc(sizeof(int) * totalCartas);
    if (!vet) return NULL;

    int valor = 1;
    for (int i = 0; i < totalCartas; i += 2) {
        vet[i] = valor;
        vet[i + 1] = valor;
        valor++;
    }

    return vet;
}

bool verificaPar(int valor1, int valor2) {
    return valor1 == valor2;
}

int contarCartasReveladas(Carta** tabuleiro, int linhas, int colunas) {
    int cont = 0;

    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            if (tabuleiro[i][j].revelada)
                cont++;

    return cont;
}

bool jogoConcluido(int cartasReveladas, int totalCartas) {
    return cartasReveladas == totalCartas;
}


void novoJogo(int tabuleiro[linhas][colunas]){
    printf("Iniciando um novo jogo...\n");
    Sleep(2000);
    system("cls");

    // Lógica para iniciar um novo jogo, implementar aqui o embaralhamento
    Carta c1 = {1, false};
    Carta c2 = {2, false};
    Carta c3 = {3, false};
    Carta c4 = {4, false};

    
}


int main() {
    int opcao;
    int tabuleiro[n][n];

    // Já ta chamando o menu principal e lendo a opção
    opcao = menuPrincipal(opcao);

    if (opcao == 1){
        novoJogo(tabuleiro[linhas][colunas]);
    } else if (opcao == 2){
        printf("Funcao de carregar jogo indisponivel no momento.\n");
        Sleep(2000);
        system("cls");
        opcao = menuPrincipal(opcao);
        printf("%d", opcao);
    } else if (opcao == 3){ 
        printf("Saindo do jogo. Ate mais!\n");
        Sleep(2000);
    }

    return 0;
}

void linha(){
    puts("-------------------------------------------------\n");
}

int menuPrincipal(int opcao){
    do{
        linha();
        printf("           JOGO DA MEMORIA\n");
        linha();
        printf("1 - Novo Jogo\n");
        printf("2 - Carregar Jogo (indisponivel)\n");
        printf("3 - Sair\n");
        linha();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
    } while (opcao < 1 || opcao > 3);

    return opcao;
}
