#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

//-------------------------------------------------------------
// DEFINES
//-------------------------------------------------------------
#define LINHAS 2
#define COLUNAS 9
#define TOTAL_CARTAS (LINHAS * COLUNAS)
#define SAVEFILE "savegame.bin"

//-------------------------------------------------------------
// STRUCT CARTA
//-------------------------------------------------------------
typedef struct {
    int valor;
    bool revelada;
    bool encontrada;
} Carta;

//-------------------------------------------------------------
// PROTÓTIPOS
//-------------------------------------------------------------
int menuPrincipal();
void linha();
void limparEntrada();
int* gerarPares();
void embaralhar(int *vet, int tam);
Carta** alocarTabuleiro();
void preencherTabuleiro(Carta **tab, int *valores);
void exibirTabuleiro(Carta **tab);
void escolherCarta(Carta **tab, int *l, int *c, const char *texto);
void novoJogo();
void salvarJogo(Carta **tab);
Carta** carregarJogo();
void continuarJogoCarregado(Carta **tab);

//-------------------------------------------------------------
// LIMPA BUFFER (CORRIGE BUG DAS LETRAS)
//-------------------------------------------------------------
void limparEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//-------------------------------------------------------------
// MENU PRINCIPAL
//-------------------------------------------------------------
int menuPrincipal() {
    int opcao;

    while (1) {
        linha();
        printf("           JOGO DA MEMORIA\n");
        linha();
        printf("1 - Novo Jogo\n");
        printf("2 - Carregar Jogo\n");
        printf("3 - Sair\n");
        linha();
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida! Digite um numero.\n");
            limparEntrada();
            Sleep(1300);
            system("cls");
            continue;
        }

        if (opcao >= 1 && opcao <= 3)
            return opcao;

        printf("Opcao invalida!\n");
        Sleep(1200);
        system("cls");
    }
}

void linha() {
    printf("-------------------------------------------------\n");
}

//-------------------------------------------------------------
// GERAÇÃO DE PARES
//-------------------------------------------------------------
int* gerarPares() {
    int *vet = malloc(TOTAL_CARTAS * sizeof(int));
    int k = 0;

    for (int i = 1; i <= TOTAL_CARTAS / 2; i++) {
        vet[k++] = i;
        vet[k++] = i;
    }
    return vet;
}

//-------------------------------------------------------------
// EMBARALHAR (FISHER-YATES)
//-------------------------------------------------------------
void embaralhar(int *vet, int tam) {
    for (int i = tam - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = vet[i];
        vet[i] = vet[j];
        vet[j] = tmp;
    }
}

//-------------------------------------------------------------
// ALOCAR MATRIZ
//-------------------------------------------------------------
Carta** alocarTabuleiro() {
    Carta **m = malloc(LINHAS * sizeof(Carta*));
    for (int i = 0; i < LINHAS; i++)
        m[i] = malloc(COLUNAS * sizeof(Carta));
    return m;
}

//-------------------------------------------------------------
// PREENCHER TABULEIRO
//-------------------------------------------------------------
void preencherTabuleiro(Carta **tab, int *valores) {
    int k = 0;
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++) {
            tab[i][j].valor = valores[k++];
            tab[i][j].revelada = false;
            tab[i][j].encontrada = false;
        }
}

//-------------------------------------------------------------
// EXIBIR TABULEIRO
//-------------------------------------------------------------
void exibirTabuleiro(Carta **tab) {
    printf("\nTABULEIRO:\n\n");

    printf("      ");
    for (int c = 1; c <= COLUNAS; c++)
        printf(" %2d ", c);
    printf("\n");

    printf("      ");
    for (int c = 1; c <= COLUNAS; c++)
        printf("----");
    printf("\n");

    for (int i = 0; i < LINHAS; i++) {
        printf(" %2d | ", i + 1);

        for (int j = 0; j < COLUNAS; j++) {
            if (tab[i][j].encontrada)
                printf(" -  ");
            else if (tab[i][j].revelada)
                printf(" %2d ", tab[i][j].valor);
            else
                printf(" *  ");
        }
        printf("\n");
    }
}

//-------------------------------------------------------------
// ESCOLHER CARTA (com validação e entrada robusta)
//-------------------------------------------------------------
void escolherCarta(Carta **tab, int *l, int *c, const char *texto) {

    while (1) {
        printf("%s (linha coluna): ", texto);

        if (scanf("%d %d", l, c) != 2) {
            printf("Entrada invalida! Digite dois numeros.\n");
            limparEntrada();
            Sleep(1200);
            continue;
        }

        *l -= 1;
        *c -= 1;

        if (*l < 0 || *l >= LINHAS || *c < 0 || *c >= COLUNAS) {
            printf("Posicao fora do tabuleiro!\n");
            Sleep(1000);
            continue;
        }

        if (tab[*l][*c].encontrada) {
            printf("Carta já encontrada!\n");
            Sleep(1000);
            continue;
        }

        if (tab[*l][*c].revelada) {
            printf("Carta já revelada nesta jogada!\n");
            Sleep(1000);
            continue;
        }

        break;
    }
}

//-------------------------------------------------------------
// SALVAR JOGO
//-------------------------------------------------------------
void salvarJogo(Carta **tab) {

    FILE *arq = fopen(SAVEFILE, "wb");
    if (!arq) {
        printf("Erro ao salvar!\n");
        Sleep(1500);
        return;
    }

    int linhas = LINHAS;
    int colunas = COLUNAS;

    fwrite(&linhas, sizeof(int), 1, arq);
    fwrite(&colunas, sizeof(int), 1, arq);

    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            fwrite(&tab[i][j], sizeof(Carta), 1, arq);

    fclose(arq);

    printf("\nJogo salvo com sucesso!\n");
    Sleep(1500);
}

//-------------------------------------------------------------
// CARREGAR JOGO
//-------------------------------------------------------------
Carta** carregarJogo() {

    FILE *arq = fopen(SAVEFILE, "rb");
    if (!arq) {
        printf("\nNao existe jogo salvo!\n");
        Sleep(1500);
        return NULL;
    }

    int a, b;
    fread(&a, sizeof(int), 1, arq);
    fread(&b, sizeof(int), 1, arq);

    if (a != LINHAS || b != COLUNAS) {
        printf("Save incompatível!\n");
        fclose(arq);
        Sleep(1500);
        return NULL;
    }

    Carta **tab = alocarTabuleiro();

    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            fread(&tab[i][j], sizeof(Carta), 1, arq);

    fclose(arq);

    printf("\nJogo carregado com sucesso!\n");
    Sleep(1500);

    return tab;
}

//-------------------------------------------------------------
// CONTINUAR JOGO CARREGADO (com salvar e sair)
//-------------------------------------------------------------
void continuarJogoCarregado(Carta **tabuleiro) {

    int l1, c1, l2, c2;
    char entrada[20];

    while (1) {

        system("cls");
        exibirTabuleiro(tabuleiro);

        printf("\nDigite 99 para SALVAR E SAIR.\n");

        //---------------------------------------------------------
        // PRIMEIRA CARTA
        //---------------------------------------------------------
        printf("\nEscolha a PRIMEIRA carta (linha coluna) ou 99: ");

        limparEntrada();
        fgets(entrada, sizeof(entrada), stdin);

        int cmd;
        if (sscanf(entrada, "%d", &cmd) == 1 && cmd == 99) {
            salvarJogo(tabuleiro);
            printf("Jogo salvo. Encerrando partida...\n");
            Sleep(1500);
            return;
        }

        if (sscanf(entrada, "%d %d", &l1, &c1) != 2) {
            printf("Entrada inválida! Use: linha coluna\n");
            Sleep(1200);
            continue;
        }

        l1--;  
        c1--;

        if (l1 < 0 || l1 >= LINHAS || c1 < 0 || c1 >= COLUNAS) continue;
        if (tabuleiro[l1][c1].encontrada || tabuleiro[l1][c1].revelada) continue;

        tabuleiro[l1][c1].revelada = true;

        system("cls");
        exibirTabuleiro(tabuleiro);

        //---------------------------------------------------------
        // SEGUNDA CARTA
        //---------------------------------------------------------
        escolherCarta(tabuleiro, &l2, &c2, "\nEscolha a SEGUNDA carta");
        tabuleiro[l2][c2].revelada = true;

        system("cls");
        exibirTabuleiro(tabuleiro);

        //---------------------------------------------------------
        // PAR?
        //---------------------------------------------------------
        if (tabuleiro[l1][c1].valor == tabuleiro[l2][c2].valor) {
            printf("\n>>> PAR ENCONTRADO! <<<\n");
            Sleep(1200);
            tabuleiro[l1][c1].encontrada = true;
            tabuleiro[l2][c2].encontrada = true;

        } else {
            printf("\nNao sao iguais...\n");
            Sleep(1200);
            tabuleiro[l1][c1].revelada = false;
            tabuleiro[l2][c2].revelada = false;
        }

        //---------------------------------------------------------
        // VERIFICA O FIM
        //---------------------------------------------------------
        int ach = 0;
        for (int i = 0; i < LINHAS; i++)
            for (int j = 0; j < COLUNAS; j++)
                if (tabuleiro[i][j].encontrada)
                    ach++;

        if (ach == TOTAL_CARTAS) {
            printf("\nTODAS AS CARTAS FORAM ENCONTRADAS!!!\n");
            Sleep(1500);
            return;
        }
    }
}

//-------------------------------------------------------------
// NOVO JOGO (com salvar e sair)
//-------------------------------------------------------------
void novoJogo() {

    system("cls");
    printf("Iniciando um novo jogo...\n");
    Sleep(1200);
    system("cls");

    srand(time(NULL));

    int *pares = gerarPares();
    embaralhar(pares, TOTAL_CARTAS);

    Carta **tabuleiro = alocarTabuleiro();
    preencherTabuleiro(tabuleiro, pares);

    free(pares);

    int l1, c1, l2, c2;
    char entrada[20];

    while (1) {

        system("cls");
        exibirTabuleiro(tabuleiro);

        printf("\nDigite 99 para SALVAR E SAIR.\n");

        //---------------------------------------------------------
        // PRIMEIRA CARTA
        //---------------------------------------------------------
        printf("\nEscolha a PRIMEIRA carta (linha coluna) ou 99: ");

        limparEntrada();
        fgets(entrada, sizeof(entrada), stdin);

        int cmd;
        if (sscanf(entrada, "%d", &cmd) == 1 && cmd == 99) {
            salvarJogo(tabuleiro);
            printf("Jogo salvo. Encerrando partida...\n");
            Sleep(1500);
            break;
        }

        if (sscanf(entrada, "%d %d", &l1, &c1) != 2) {
            printf("Entrada inválida! Use: linha coluna\n");
            Sleep(1200);
            continue;
        }

        l1--;  
        c1--;

        if (l1 < 0 || l1 >= LINHAS || c1 < 0 || c1 >= COLUNAS) continue;
        if (tabuleiro[l1][c1].encontrada || tabuleiro[l1][c1].revelada) continue;

        tabuleiro[l1][c1].revelada = true;

        system("cls");
        exibirTabuleiro(tabuleiro);

        //---------------------------------------------------------
        // SEGUNDA CARTA
        //---------------------------------------------------------
        escolherCarta(tabuleiro, &l2, &c2, "\nEscolha a SEGUNDA carta");
        tabuleiro[l2][c2].revelada = true;

        system("cls");
        exibirTabuleiro(tabuleiro);

        //---------------------------------------------------------
        // PAR?
        //---------------------------------------------------------
        if (tabuleiro[l1][c1].valor == tabuleiro[l2][c2].valor) {
            printf("\n>>> PAR ENCONTRADO! <<<\n");
            Sleep(1200);
            tabuleiro[l1][c1].encontrada = true;
            tabuleiro[l2][c2].encontrada = true;

        } else {
            printf("\nNao sao iguais...\n");
            Sleep(1200);
            tabuleiro[l1][c1].revelada = false;
            tabuleiro[l2][c2].revelada = false;
        }

        //---------------------------------------------------------
        // VERIFICA O FIM
        //---------------------------------------------------------
        int achadas = 0;
        for (int i = 0; i < LINHAS; i++)
            for (int j = 0; j < COLUNAS; j++)
                if (tabuleiro[i][j].encontrada)
                    achadas++;

        if (achadas == TOTAL_CARTAS) {
            printf("\nTODAS AS CARTAS FORAM ENCONTRADAS!!!\n");
            Sleep(1500);
            break;
        }
    }

    //---------------------------------------------------------
    // LIBERAR MEMÓRIA
    //---------------------------------------------------------
    for (int i = 0; i < LINHAS; i++)
        free(tabuleiro[i]);
    free(tabuleiro);
}

//-------------------------------------------------------------
// MAIN
//-------------------------------------------------------------
int main() {

    while (1) {

        int opcao = menuPrincipal();

        if (opcao == 1)
            novoJogo();

        else if (opcao == 2) {
            Carta **tab = carregarJogo();
            if (tab != NULL)
                continuarJogoCarregado(tab);
        }

        else if (opcao == 3) {
            printf("Saindo...\n");
            Sleep(800);
            break;
        }
    }

    return 0;
}