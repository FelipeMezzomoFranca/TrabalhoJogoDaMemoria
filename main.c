#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void menuPrincipal(int opcao){
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
}

void linha(){
    puts("-------------------------------------------------\n");
}

int main() {
    int opcao;
    menuPrincipal(opcao);

    printf("fim");
    return 0;
}