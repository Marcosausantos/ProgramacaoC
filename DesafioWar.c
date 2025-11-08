#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ------------------------------------------------------
// Estrutura que representa um território no jogo
// ------------------------------------------------------
typedef struct {
    char nome[30];   // Nome do território (ex: "Território Norte")
    char cor[10];    // Cor do exército que controla o território (ex: "Azul")
    int tropas;      // Número de tropas no território
} Territorio;

// ------------------------------------------------------
// Função: atacar
// Simula um ataque entre dois territórios utilizando rolagem de dados (1–6).
// Caso o atacante vença, ele conquista o território do defensor.
// Caso perca, perde 1 tropa.
// ------------------------------------------------------
void atacar(Territorio *atacante, Territorio *defensor) {
    // Validação: não pode atacar um território da mesma cor
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n❌ Ataque inválido! Você não pode atacar um território aliado (%s e %s têm a mesma cor).\n",
               atacante->nome, defensor->nome);
        return;
    }

    // Rolagem de dados entre 1 e 6
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n🎲 %s (atacante - %s) rolou: %d\n", atacante->nome, atacante->cor, dadoAtacante);
    printf("🎲 %s (defensor - %s) rolou: %d\n", defensor->nome, defensor->cor, dadoDefensor);

    // Resultado da batalha
    if (dadoAtacante > dadoDefensor) {
        printf("🏆 %s venceu a batalha!\n", atacante->nome);

        // O atacante transfere metade das tropas para o território conquistado
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

        // Transfere o domínio (cor) do território
        strcpy(defensor->cor, atacante->cor);

        printf("➡ O território %s agora pertence ao exército %s com %d tropas.\n",
               defensor->nome, defensor->cor, defensor->tropas);
    } else {
        printf("💀 %s perdeu a batalha e perde 1 tropa.\n", atacante->nome);
        atacante->tropas--;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

// ------------------------------------------------------
// Função: atribuirMissao
// Sorteia uma missão aleatória para o jogador.
// ------------------------------------------------------
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// ------------------------------------------------------
// Função: exibirMapa
// Exibe o estado atual dos territórios do jogo.
// ------------------------------------------------------
void exibirMapa(Territorio *mapa, int qtdTerritorios) {
    printf("\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < qtdTerritorios; i++) {
        printf("%d) %-20s | Cor: %-8s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// ------------------------------------------------------
// Função: liberarMemoria
// Libera toda a memória alocada dinamicamente no programa.
// ------------------------------------------------------
void liberarMemoria(Territorio *mapa, char **missoesJogadores, int qtdJogadores) {
    free(mapa); // libera o vetor de territórios

    for (int i = 0; i < qtdJogadores; i++) {
        free(missoesJogadores[i]); // libera cada missão individual
    }
    free(missoesJogadores); // libera o vetor de ponteiros
}

// ------------------------------------------------------
// Função principal: main
// Cria territórios, atribui missões e simula um ataque.
// ------------------------------------------------------
int main() {
    srand(time(NULL)); // inicializa gerador de números aleatórios

    // --- Lista de possíveis missões ---
    char *missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas vermelhas",
        "Controlar todos os territorios azuis",
        "Manter 2 territorios com mais de 10 tropas",
        "Destruir o exercito verde"
    };
    int totalMissoes = 5;

    // --- Criação dinâmica do mapa de territórios ---
    int qtdTerritorios = 3;
    Territorio *mapa = (Territorio *)calloc(qtdTerritorios, sizeof(Territorio));

    // Preenche manualmente os territórios
    strcpy(mapa[0].nome, "Territorio Norte");
    strcpy(mapa[0].cor, "Azul");
    mapa[0].tropas = 8;

    strcpy(mapa[1].nome, "Territorio Sul");
    strcpy(mapa[1].cor, "Vermelho");
    mapa[1].tropas = 6;

    strcpy(mapa[2].nome, "Territorio Leste");
    strcpy(mapa[2].cor, "Verde");
    mapa[2].tropas = 5;

    // --- Criação dinâmica das missões dos jogadores ---
    int qtdJogadores = 2;
    char **missoesJogadores = (char **)malloc(qtdJogadores * sizeof(char *));
    for (int i = 0; i < qtdJogadores; i++) {
        missoesJogadores[i] = (char *)malloc(100 * sizeof(char));
        atribuirMissao(missoesJogadores[i], missoes, totalMissoes);
        printf("\nJogador %d recebeu a missão: %s\n", i + 1, missoesJogadores[i]);
    }

    // --- Exibe o mapa inicial ---
    exibirMapa(mapa, qtdTerritorios);

    // --- Simulação de ataque ---
    printf("\n--- Simulando ataque do Territorio 1 contra o Territorio 2 ---\n");
    atacar(&mapa[0], &mapa[1]); // só será válido se forem de cores diferentes

    // --- Exibe o mapa atualizado ---
    exibirMapa(mapa, qtdTerritorios);

    // --- Libera toda a memória alocada ---
    liberarMemoria(mapa, missoesJogadores, qtdJogadores);

    printf("\n✅ Memória liberada e programa encerrado com sucesso.\n");
    return 0;
}
