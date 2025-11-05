#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h> // Para o sleep no windows
#include <stdbool.h>

#define n 4
#define total (n * n)

// Funções Prototipos
int menuPrincipal(int opcao);
void linha();

void novoJogo(int tabuleiro[n][n]){
    printf("Iniciando um novo jogo...\n");
    Sleep(2000);
    system("cls");

    // Lógica para iniciar um novo jogo, implementar aqui o embaralhamento
}


int main() {
    int opcao;
    int tabuleiro[n][n];

    // Já ta chamando o menu principal e lendo a opção
    opcao = menuPrincipal(opcao);

    if (opcao == 1){
        novoJogo(tabuleiro[n][n]);
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