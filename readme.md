# 🧩 Jogo da Memória – Algoritmos II  
### Autores: Felipe Mezzomo França, Guilherme Fernandes Oliveira, Letícia Ceron Hass  
### Linguagem: C  
### Arquivo principal: `main.c`  
### Arquivo do save: `savegame.bin`

---

## 📖 Descrição Geral

Este projeto implementa um **Jogo da Memória em C** utilizando:

- Matrizes dinâmicas  
- Structs  
- Ponteiros  
- Embaralhamento usando Fisher-Yates  
- Leitura segura de entrada  
- Sistema completo de **Salvar e Carregar jogo (Save/Load)** usando arquivo binário  
- Validações robustas para evitar loops infinitos e bugs com entrada inválida  

O tabuleiro possui **2 linhas × 9 colunas (18 cartas)**.  
As cartas são distribuídas em pares e embaralhadas aleatoriamente.

O jogador seleciona cartas usando coordenadas e tenta encontrar todos os pares.

---

## 🎮 Como Jogar

### 🟦 Menu inicial

Ao iniciar o programa, você verá:

1 - Novo Jogo 
2 - Carregar Jogo 
3 - Sair 

---

## ▶️ Jogabilidade

Quando o jogo começa:

1. O tabuleiro é exibido com linhas e colunas numeradas.
2. Para selecionar uma carta, digite: linha coluna
  Exemplo: 1 3
3. A carta será revelada.
4. O processo se repete para a segunda carta.
5. Se os valores coincidirem → par encontrado.  
Caso contrário → ambas são ocultadas novamente.

O jogo termina quando **todas as cartas forem encontradas**.

---

## 💾 Salvar e Sair (Função “Salvar e Sair”)

Em qualquer momento de escolha da *primeira carta*, o usuário pode digitar: 99

Isso vai:

- Salvar o estado completo do jogo
- Encerrar a partida imediatamente
- Retornar ao menu principal

O jogo é salvo no arquivo savegame.bin

---

## 📂 Carregar Jogo

Ao selecionar:
2 - Carregar Jogo

O programa:

- Verifica se o arquivo `savegame.bin` existe  
- Carrega o tabuleiro completo  
- Recupera cartas reveladas e encontradas  
- Mantém o jogador exatamente no ponto onde parou

---

# 🔍 Aprendizados Peculiares (Conceitos Importantes)

Esta seção explica técnicas usadas no código que normalmente não aparecem tão cedo na disciplina,
mas que fizeram total diferença para deixar o programa estável.

---

## 1. Entrada Segura com fgets() + sscanf()

Usar somente scanf é arriscado: se o usuário digitar uma letra, símbolo ou espaço a mais, o
programa trava, entra em loop ou fica “piscando” o terminal.  
Para resolver isso, usamos uma combinação muito mais segura:

    fgets(entrada, sizeof(entrada), stdin);
    sscanf(entrada, "%d %d", &l, &c);

Por que isso é importante?

- Evita loops infinitos  
- Aceita tanto “1 3” quanto “99”  
- Permite comandos especiais  
- Lê a linha completa primeiro → não deixa lixo no buffer  

---

## 2. limparEntrada() – Limpando o buffer do teclado

Quando scanf falha, ele deixa o caractere inválido no buffer (stdin), o que cria loops
infinitos mesmo com cls().  
Para evitar isso, criamos:

    void limparEntrada() {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

Benefícios:

- Garante que a próxima leitura será limpa  
- Impede repetição automática do menu  
- Evita comportamento estranho quando o usuário digita errado  

---

## 3. Embaralhamento Fisher-Yates

Método correto para embaralhar vetores:

    for (int i = tam - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = vet[i];
        vet[i] = vet[j];
        vet[j] = temp;
    }

Benefícios:

- Distribuição totalmente uniforme  
- Não favorece nenhuma carta  
- Utilizado em jogos reais, baralhos e sistemas de sorteio  

---

## 4. Matriz Dinâmica com Ponteiros Duplos (Carta **tabuleiro)

A matriz é alocada assim:

    Carta **tabuleiro = malloc(LINHAS * sizeof(Carta*));

E cada linha:

    tabuleiro[i] = malloc(COLUNAS * sizeof(Carta));

Por que isso é importante?

- Permite passar o tabuleiro entre funções  
- Suporta carregar jogos salvos  
- Treina uso de ponteiros e memória dinâmica  
- Facilita expandir o jogo no futuro  

---

## 5. Save/Load Binário Profissional

Gravamos a struct inteira no arquivo:

    fwrite(&tab[i][j], sizeof(Carta), 1, arq);

E carregamos:

    fread(&tab[i][j], sizeof(Carta), 1, arq);

Isso salva:

- valor  
- revelada  
- encontrada  

O jogo volta exatamente igual ao estado salvo.

---

## 6. Interpretação Híbrida (coordenada OU comando)

O sistema aceita:

    1 3   → jogada normal  
    99    → salvar e sair  

Tudo com um único mecanismo:

    if (sscanf(entrada, "%d", &cmd) == 1 && cmd == 99)

Benefícios:

- Entrada flexível  
- Código mais simples  
- Usuário entende facilmente  

---

## ✔ Resumo dos Aprendizados

- Entrada segura evitando travamentos (esquema com o sscanf)  
- Limpeza de buffer pra não dar pau  
- Fisher-Yates garante embaralhamento sem pender para lado nenhum  
- Ponteiros duplos permitem matriz dinâmica  
- Save/Load binário restaura o jogo perfeitamente  
