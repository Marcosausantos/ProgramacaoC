#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// desafio 02
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;


void trocar(Componente *a, Componente *b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}


void bubbleSort(Componente *v, int n, int *comparacoes) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                trocar(&v[j], &v[j + 1]);
            }
        }
    }
}


void insertionSort(Componente *v, int n, int *comparacoes) {
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;

        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            (*comparacoes)++;
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}


void selectionSort(Componente *v, int n, int *comparacoes) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (v[j].prioridade < v[minIndex].prioridade)
                minIndex = j;
        }
        trocar(&v[i], &v[minIndex]);
    }
}


int buscaBinaria(Componente *v, int n, char *chave, int *comparacoes) {
    int esq = 0, dir = n - 1;
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        (*comparacoes)++;
        int cmp = strcmp(v[meio].nome, chave);

        if (cmp == 0) return meio;
        else if (cmp < 0) esq = meio + 1;
        else dir = meio - 1;
    }
    return -1;
}


void exibirComponentes(Componente *v, int n) {
    printf("\n===== COMPONENTES DA TORRE =====\n");
    printf("%-25s | %-15s | %-10s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-25s | %-15s | %-10d\n", v[i].nome, v[i].tipo, v[i].prioridade);
    }
}


int main() {
    Componente componentes[MAX_COMPONENTES];
    int n;

    printf("===== SISTEMA DE MONTAGEM DA TORRE DE FUGA =====\n\n");
    printf("Quantos componentes deseja cadastrar (máx %d)? ", MAX_COMPONENTES);
    scanf("%d", &n);
    getchar(); 

    if (n > MAX_COMPONENTES || n <= 0) {
        printf("Número inválido de componentes.\n");
        return 1;
    }

       for (int i = 0; i < n; i++) {
        printf("\nComponente %d:\n", i + 1);
        printf("Nome: ");
        fgets(componentes[i].nome, 30, stdin);
        componentes[i].nome[strcspn(componentes[i].nome, "\n")] = '\0';

        printf("Tipo: ");
        fgets(componentes[i].tipo, 20, stdin);
        componentes[i].tipo[strcspn(componentes[i].tipo, "\n")] = '\0';

        printf("Prioridade (1-10): ");
        scanf("%d", &componentes[i].prioridade);
        getchar(); // limpa o \n
    }

    int opcao, comparacoes = 0;
    clock_t inicio, fim;
    double tempo_execucao;

    /
    printf("\nEscolha o método de ordenação:\n");
    printf("1 - Bubble Sort (por Nome)\n");
    printf("2 - Insertion Sort (por Tipo)\n");
    printf("3 - Selection Sort (por Prioridade)\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    getchar();

   
    inicio = clock();
    switch (opcao) {
        case 1:
            bubbleSort(componentes, n, &comparacoes);
            break;
        case 2:
            insertionSort(componentes, n, &comparacoes);
            break;
        case 3:
            selectionSort(componentes, n, &comparacoes);
            break;
        default:
            printf("Opção inválida. Encerrando.\n");
            return 1;
    }
    fim = clock();

    tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\nOrdenação concluída!\n");
    printf("Comparações realizadas: %d\n", comparacoes);
    printf("Tempo de execução: %.6f segundos\n", tempo_execucao);

    
    exibirComponentes(componentes, n);

   
    if (opcao == 1) {
        char chave[30];
        printf("\nDigite o nome do componente-chave para iniciar a montagem: ");
        fgets(chave, 30, stdin);
        chave[strcspn(chave, "\n")] = '\0';

        int compBusca = 0;
        int pos = buscaBinaria(componentes, n, chave, &compBusca);

        if (p
