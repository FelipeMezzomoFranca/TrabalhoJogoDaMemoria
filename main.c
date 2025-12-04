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

 int totalCartas = total;
    int* pares = gerarVetorPares(totalCartas);

    Carta cartas[totalCartas];

    for (int i = 0; i < totalCartas; i++) {
        cartas[i].valor = pares[i];
        cartas[i].revelada = false;
    }

    int escolha1, escolha2;

    printf("Digite o indice da primeira carta (0 a %d): ", totalCartas - 1);
    scanf("%d", &escolha1);

    printf("Digite o indice da segunda carta (0 a %d): ", totalCartas - 1);
    scanf("%d", &escolha2);

    printf("\nVoce escolheu as cartas %d e %d\n",
            cartas[escolha1].valor,
            cartas[escolha2].valor);

    if (verificaPar(cartas[escolha1].valor, cartas[escolha2].valor)) {
        printf("Par encontrado!\n");
        cartas[escolha1].revelada = true;
        cartas[escolha2].revelada = true;
    } else {
        printf("Nao eh par.\n");
    }

    int reveladas = 0;
    for (int i = 0; i < totalCartas; i++) {
        if (cartas[i].revelada)
            reveladas++;
    }

    printf("\nCartas reveladas ate agora: %d\n", reveladas);

    if (jogoConcluido(reveladas, totalCartas)) {
        printf("Todas as cartas foram encontradas! Fim do jogo.\n");
    }

    free(pares);
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
