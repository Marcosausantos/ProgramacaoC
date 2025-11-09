#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3


typedef struct {
    char nome;  
    int id;     
} Peca;


typedef struct {
    Peca itens[MAX_FILA];
    int frente;
    int tras;
    int quantidade;
} Fila;


typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;


void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->quantidade = 0;
}

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}


Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}


int filaCheia(Fila *f) {
    return f->quantidade == MAX_FILA;
}

int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

void enfileirar(Fila *f, Peca p) {
    if (!filaCheia(f)) {
        f->tras = (f->tras + 1) % MAX_FILA;
        f->itens[f->tras] = p;
        f->quantidade++;
    }
}

Peca desenfileirar(Fila *f) {
    Peca removida = {'-', -1};
    if (!filaVazia(f)) {
        removida = f->itens[f->frente];
        f->frente = (f->frente + 1) % MAX_FILA;
        f->quantidade--;
    }
    return removida;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void empilhar(Pilha *p, Peca pc) {
    if (!pilhaCheia(p)) {
        p->topo++;
        p->itens[p->topo] = pc;
    }
}

Peca desempilhar(Pilha *p) {
    Peca retirada = {'-', -1};
    if (!pilhaVazia(p)) {
        retirada = p->itens[p->topo];
        p->topo--;
    }
    return retirada;
}

void exibirFila(Fila *f) {
    printf("\nFila de Peças: ");
    if (filaVazia(f)) {
        printf("(vazia)");
    } else {
        int i, idx;
        for (i = 0; i < f->quantidade; i++) {
            idx = (f->frente + i) % MAX_FILA;
            printf("[%c-%d] ", f->itens[idx].nome, f->itens[idx].id);
        }
    }
    printf("\n");
}

void exibirPilha(Pilha *p) {
    printf("Pilha de Reservas: ");
    if (pilhaVazia(p)) {
        printf("(vazia)");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c-%d] ", p->itens[i].nome, p->itens[i].id);
        }
    }
    printf("\n");
}

void jogarPeca(Fila *f, int *contadorID) {
    if (!filaVazia(f)) {
        Peca jogada = desenfileirar(f);
        printf("Peça jogada: [%c-%d]\n", jogada.nome, jogada.id);
