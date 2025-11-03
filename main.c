#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h> // Para o sleep no windows

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

void novoJogo(){
    printf("Iniciando um novo jogo...\n");
    Sleep(2000);

    // Lógica para iniciar um novo jogo seria implementada aqui
}

void linha(){
    puts("-------------------------------------------------\n");
}

int main() {
    int opcao;

    opcao = menuPrincipal(opcao);

    if (opcao == 1){
        novoJogo();
    } else if (opcao == 2){
        printf("Funcao de carregar jogo indisponivel no momento.\n");
        Sleep(2000);
        opcao = menuPrincipal(opcao);
        printf("%d", opcao);
    } else if (opcao == 3){ 
        printf("Saindo do jogo. Ate mais!\n");
        Sleep(2000);
    }

    return 0;
}