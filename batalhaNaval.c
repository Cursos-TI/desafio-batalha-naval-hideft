#include <stdio.h>
#include <stdlib.h>

// Constantes para o tamanho do tabuleiro e o valor das células
#define TAMANHO_TABULEIRO 10
#define AGUA 0
#define NAVIO 3
#define AFETADO 5

// Constante para o tamanho das matrizes de habilidade (5x5)
#define TAMANHO_HABILIDADE 5

// Protótipos das funções
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void criar_matriz_cone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void criar_matriz_cruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void criar_matriz_octaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void sobrepor_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                         int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                         int origem_linha, int origem_coluna);

int main() {
    // 1. Definir o Tabuleiro 10x10
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Inicializa o tabuleiro com água (0) e coloca alguns navios (3)
    inicializar_tabuleiro(tabuleiro);

    // 2. Criar Matrizes de Habilidade (5x5)
    int matriz_cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int matriz_cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int matriz_octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // 3. Construir as matrizes de efeito
    criar_matriz_cone(matriz_cone);
    criar_matriz_cruz(matriz_cruz);
    criar_matriz_octaedro(matriz_octaedro);

    // 4. Integrar Habilidades ao Tabuleiro
    
    // Habilidade Cone: Origem (3, 3)
    printf("--- Tabuleiro antes da Habilidade Cone (Origem: 3, 3) ---\n");
    exibir_tabuleiro(tabuleiro);
    sobrepor_habilidade(tabuleiro, matriz_cone, 3, 3);
    printf("\n--- Tabuleiro apos Habilidade Cone ---\n");
    exibir_tabuleiro(tabuleiro);

    // Reinicializa o tabuleiro para o próximo teste (opcional, para visualização clara)
    inicializar_tabuleiro(tabuleiro); 

    // Habilidade Cruz: Origem (7, 7)
    printf("\n--- Tabuleiro antes da Habilidade Cruz (Origem: 7, 7) ---\n");
    exibir_tabuleiro(tabuleiro);
    sobrepor_habilidade(tabuleiro, matriz_cruz, 7, 7);
    printf("\n--- Tabuleiro apos Habilidade Cruz ---\n");
    exibir_tabuleiro(tabuleiro);

    // Reinicializa o tabuleiro para o próximo teste
    inicializar_tabuleiro(tabuleiro); 

    // Habilidade Octaedro: Origem (1, 5)
    printf("\n--- Tabuleiro antes da Habilidade Octaedro (Origem: 1, 5) ---\n");
    exibir_tabuleiro(tabuleiro);
    sobrepor_habilidade(tabuleiro, matriz_octaedro, 1, 5);
    printf("\n--- Tabuleiro apos Habilidade Octaedro ---\n");
    exibir_tabuleiro(tabuleiro);

    return 0;
}

/**
 * @brief Inicializa o tabuleiro 10x10 com AGUA (0) e posiciona alguns NAVIOS (3).
 * 
 * @param tabuleiro A matriz 10x10 que representa o tabuleiro.
 */
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Inicializa tudo com AGUA
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Posiciona alguns navios (exemplo fixo)
    tabuleiro[0][0] = NAVIO;
    tabuleiro[0][1] = NAVIO;
    tabuleiro[3][3] = NAVIO;
    tabuleiro[4][3] = NAVIO;
    tabuleiro[5][3] = NAVIO;
    tabuleiro[7][7] = NAVIO;
    tabuleiro[7][8] = NAVIO;
    tabuleiro[9][9] = NAVIO;
}

/**
 * @brief Exibe o tabuleiro no console, utilizando caracteres para representar os elementos.
 * 
 * @param tabuleiro A matriz 10x10 que representa o tabuleiro.
 */
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Exibe cabeçalho de colunas
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    // Exibe o tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i); // Exibe índice da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Utiliza condicionais para exibir o caractere correto
            if (tabuleiro[i][j] == AGUA) {
                printf(" . "); // Água (0)
            } else if (tabuleiro[i][j] == NAVIO) {
                printf(" N "); // Navio (3)
            } else if (tabuleiro[i][j] == AFETADO) {
                printf(" X "); // Área afetada (5)
            } else {
                printf(" ? "); // Valor inesperado
            }
        }
        printf("\n");
    }
}

/**
 * @brief Cria a matriz de efeito para a habilidade "Cone" (5x5).
 * 
 * O cone aponta para baixo, com o ponto de origem no topo (centro da primeira linha)
 * e expandindo-se em direção à base.
 * 
 * @param matriz A matriz 5x5 que será preenchida com 0s e 1s.
 */
void criar_matriz_cone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2; // 2

    // Loops aninhados para preencher a matriz
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // A área afetada (1) se expande com a linha (i)
            // A largura afetada é (2 * i) + 1, centrada em 'centro'
            // A coluna 'j' está afetada se estiver dentro do intervalo [centro - i, centro + i]
            if (j >= centro - i && j <= centro + i) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

/**
 * @brief Cria a matriz de efeito para a habilidade "Cruz" (5x5).
 * 
 * A cruz tem o ponto de origem no centro.
 * 
 * @param matriz A matriz 5x5 que será preenchida com 0s e 1s.
 */
void criar_matriz_cruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2; // 2

    // Loops aninhados para preencher a matriz
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // A área afetada (1) é a linha central (i == centro) OU a coluna central (j == centro)
            if (i == centro || j == centro) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

/**
 * @brief Cria a matriz de efeito para a habilidade "Octaedro" (5x5).
 * 
 * O octaedro (losango) tem o ponto de origem no centro.
 * 
 * @param matriz A matriz 5x5 que será preenchida com 0s e 1s.
 */
void criar_matriz_octaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2; // 2

    // Loops aninhados para preencher a matriz
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // A condição para um losango é que a distância de Manhattan do centro (centro, centro)
            // seja menor ou igual à distância máxima (centro).
            // Distância de Manhattan: |i - centro| + |j - centro|
            int dist_manhattan = abs(i - centro) + abs(j - centro);

            if (dist_manhattan <= centro) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

/**
 * @brief Implementa a lógica para sobrepor a matriz de habilidade ao tabuleiro.
 * 
 * A sobreposição é feita centrando a matriz de habilidade no ponto de origem (origem_linha, origem_coluna).
 * A lógica garante que a sobreposição permaneça dentro dos limites do tabuleiro.
 * 
 * @param tabuleiro A matriz 10x10 do jogo.
 * @param matriz_habilidade A matriz 5x5 da habilidade (0 ou 1).
 * @param origem_linha Coordenada da linha de origem no tabuleiro.
 * @param origem_coluna Coordenada da coluna de origem no tabuleiro.
 */
void sobrepor_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                         int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                         int origem_linha, int origem_coluna) {
    
    // O centro da matriz de habilidade 5x5 é (2, 2)
    int centro_habilidade = TAMANHO_HABILIDADE / 2; // 2

    // Loops aninhados para percorrer a matriz de habilidade
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            
            // Se a posição na matriz de habilidade está afetada (valor 1)
            if (matriz_habilidade[i][j] == 1) {
                
                // Calcula a coordenada correspondente no tabuleiro
                // A posição (i, j) da matriz de habilidade é mapeada para o tabuleiro
                // subtraindo o centro da habilidade e somando a origem no tabuleiro.
                int tab_linha = origem_linha + (i - centro_habilidade);
                int tab_coluna = origem_coluna + (j - centro_habilidade);

                // Condicional para verificar se a posição calculada está dentro dos limites do tabuleiro
                if (tab_linha >= 0 && tab_linha < TAMANHO_TABULEIRO &&
                    tab_coluna >= 0 && tab_coluna < TAMANHO_TABULEIRO) {
                    
                    // Marca a posição no tabuleiro como AFETADO (5)
                    // Se a célula já for um navio (3), ela será marcada como AFETADO (5) para fins de visualização.
                    if (tabuleiro[tab_linha][tab_coluna] != NAVIO) {
                        tabuleiro[tab_linha][tab_coluna] = AFETADO;
                    }
                }
            }
        }
    }
}