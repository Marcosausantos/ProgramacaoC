#include <stdio.h>

void moverTorre() {
    printf("\nMovimento da Torre (5 casas para a direita):\n");
    for (int i = 0; i < 5; i++) {
        printf("Direita\n");
    }
}

void moverBispo() {
    printf("\nMovimento do Bispo (5 casas na diagonal cima-direita):\n");
    int i = 0;
    while (i < 5) {
        printf("Cima, Direita\n");
        i++;
    }
}

void moverRainha() {
    printf("\nMovimento da Rainha (8 casas para a esquerda):\n");
    int i = 0;
    do {
        printf("Esquerda\n");
        i++;
    } while (i < 8);
}


void moverCavalo() {
    printf("\nMovimento do Cavalo (2 casas para baixo e 1 para a esquerda):\n");
    
    // Primeira parte do L: 2 casas para baixo
    for (int i = 0; i < 2; i++) {
        printf("Baixo\n");
    }
    
    // Segunda parte do L: 1 casa para a esquerda
    int j = 0;
    while (j < 1) {
        printf("Esquerda\n");
        j++;
    }
}

int main() {
    // Torre: for (5 casas para a direita)
    moverTorre();
    
    // Bispo: while (5 casas na diagonal cima-direita)
    moverBispo();
    
    // Rainha: do-while (8 casas para a esquerda)
    moverRainha();

    // Cavalo: loops aninhados (2 baixo + 1 esquerda)
    moverCavalo();
    
    return 0;
}