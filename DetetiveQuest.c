#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



typedef struct Sala {
    char *nome;
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

typedef struct PistaNode {
    char *pista;
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

typedef struct HashEntry {
    char *chave;   
    char *valor;  
    struct HashEntry *prox;
} HashEntry;

#define TAM_HASH 101
typedef struct {
    HashEntry *buckets[TAM_HASH];
} HashTable;


char *strdup_safe(const char *s) {
    char *r = malloc(strlen(s)+1);
    strcpy(r, s);
    return r;
}

void removerNovaLinha(char *s) {
    if (!s) return;
    char *p = strchr(s, '\n');
    if (p) *p = '\0';
}

unsigned long hash_str(const char *s) {
    unsigned long h = 5381;
    while (*s) h = ((h << 5) + h) + (unsigned char)(*s++);
    return h % TAM_HASH;
}


/*
 * Cada sala possui um nome exclusivo e ponteiros 
 * Retorna o ponteiro para a nova sala.
 */
Sala* criarSala(const char *nome) {
    Sala *nova = malloc(sizeof(Sala));
    if (!nova) { perror("Erro ao alocar sala"); exit(EXIT_FAILURE); }
    nova->nome = strdup_safe(nome);
    nova->esquerda = nova->direita = NULL;
    return nova;
}


Sala* construirMansao() {
    Sala *raiz = criarSala("Hall de Entrada");
    raiz->esquerda = criarSala("Biblioteca");
    raiz->direita = criarSala("Sala de Jantar");

    raiz->esquerda->esquerda = criarSala("Escritório");
    raiz->esquerda->direita = criarSala("Conservatório");
    raiz->direita->esquerda = criarSala("Cozinha");
    raiz->direita->direita = criarSala("Quarto Principal");

    return raiz;
}

/*
 * A ordenação é alfabética para facilitar a listagem final.
 */
PistaNode* inserirPista(PistaNode *raiz, const char *pista) {
    if (!raiz) {
        PistaNode *novo = malloc(sizeof(PistaNode));
        novo->pista = strdup_safe(pista);
        novo->esquerda = novo->direita = NULL;
        return novo;
    }
    int cmp = strcmp(pista, raiz->pista);
    if (cmp < 0) raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else raiz->direita = inserirPista(raiz->direita, pista);
    return raiz;
}

void imprimirPistas(PistaNode *raiz) {
    if (!raiz) return;
    imprimirPistas(raiz->esquerda);
    printf(" - %s\n", raiz->pista);
    imprimirPistas(raiz->direita);
}

/*
 * ao nome de um suspeito (valor). O método de colisão é encadeamento.
 */
void inserirNaHash(HashTable *ht, const char *pista, const char *suspeito) {
    unsigned long idx = hash_str(pista);
    HashEntry *nova = malloc(sizeof(HashEntry));
    nova->chave = strdup_safe(pista);
    nova->valor = strdup_safe(suspeito);
    nova->prox = ht->buckets[idx];
    ht->buckets[idx] = nova;
}


/*
 * à pista informada. Retorna o nome do suspeito, ou NULL se não encontrado.
 */
const char* encontrarSuspeito(HashTable *ht, const char *pista) {
    unsigned long idx = hash_str(pista);
    for (HashEntry *e = ht->buckets[idx]; e; e = e->prox) {
        if (strcmp(e->chave, pista) == 0)
            return e->valor;
    }
    return NULL;
}


HashTable* construirTabelaHash() {
    HashTable *ht = malloc(sizeof(HashTable));
    for (int i=0;i<TAM_HASH;i++) ht->buckets[i] = NULL;

    inserirNaHash(ht, "Pegada encharcada", "Marcos");
    inserirNaHash(ht, "Livro riscado com inicial 'M'", "Marcos");
    inserirNaHash(ht, "Carta rasgada", "Ana");
    inserirNaHash(ht, "Pó de erva exótica", "Carlos");
    inserirNaHash(ht, "Vaso quebrado", "Ana");
    inserirNaHash(ht, "Panela com anomalia no fundo", "Carlos");
    inserirNaHash(ht, "Lençol com manchas de tinta", "Beatriz");
    return ht;
}


const char* pistaPorSala(const char *nome) {
    if (strcmp(nome, "Hall de Entrada") == 0) return "Pegada encharcada";
    if (strcmp(nome, "Biblioteca") == 0) return "Livro riscado com inicial 'M'";
    if (strcmp(nome, "Escritório") == 0) return "Carta rasgada";
    if (strcmp(nome, "Conservatório") == 0) return "Pó de erva exótica";
    if (strcmp(nome, "Sala de Jantar") == 0) return "Vaso quebrado";
    if (strcmp(nome, "Cozinha") == 0) return "Panela com anomalia no fundo";
    if (strcmp(nome, "Quarto Principal") == 0) return "Lençol com manchas de tinta";
    return NULL;
}


void explorarSalas(Sala *inicio, PistaNode **pistas, HashTable *ht) {
    Sala *atual = inicio;
    char op[16];

    printf("\n--- Exploração da mansão iniciada ---\n");
    printf("Comandos: esquerda (e), direita (d), sair (s)\n");

    while (1) {
        printf("\nVocê está em: %s\n", atual->nome);
        const char *pista = pistaPorSala(atual->nome);
        if (pista) {
            printf("Pista encontrada: %s\n", pista);
            printf("Deseja coletar essa pista? (s/n): ");
            fgets(op, sizeof(op), stdin);
            removerNovaLinha(op);
            if (op[0] == 's' || op[0] == 'S') {
                *pistas = inserirPista(*pistas, pista);
                printf("Pista coletada!\n");
            }
        } else {
            printf("Nenhuma pista aqui.\n");
        }

        printf("Mover para (e/d) ou sair (s): ");
        fgets(op, sizeof(op), stdin);
        removerNovaLinha(op);

        if (op[0] == 's' || op[0] == 'S') {
            printf("Encerrando exploração\n");
            break;
        } else if (op[0] == 'e' || op[0] == 'E') {
            if (atual->esquerda) atual = atual->esquerda;
            else printf("Não há sala à esquerda.\n");
        } else if (op[0] == 'd' || op[0] == 'D') {
            if (atual->direita) atual = atual->direita;
            else printf("Não há sala à direita.\n");
        } else {
            printf("Comando inválido.\n");
        }
    }
}


void verificarSuspeitoFinal(PistaNode *pistas, HashTable *ht) {
    if (!pistas) {
        printf("\nNenhuma pista coletada.\n");
        return;
    }

    printf("\nPistas coletadas:\n");
    imprimirPistas(pistas);

    char acusado[64];
    printf("\nDigite o nome do suspeito: ");
    fgets(acusado, sizeof(acusado), stdin);
    removerNovaLinha(acusado);

    int cont = 0;
   
    if (pistas) {
     
        PistaNode *stack[64];
        int top = 0;
        PistaNode *cur = pistas;
        while (cur || top > 0) {
            while (cur) {
                stack[top++] = cur;
                cur = cur->esquerda;
            }
            cur = stack[--top];
            const char *sus = encontrarSuspeito(ht, cur->pista);
            if (sus && strcasecmp(sus, acusado) == 0)
                cont++;
            cur = cur->direita;
        }
    }

    printf("\nTotal de pistas que apontam para %s: %d\n", acusado, cont);
    if (cont >= 2)
        printf("1 = Acusação sustentada! Há evidências suficientes.\n");
    else
        printf("2 = Acusação fraca. Menos de 2 pistas associadas.\n");
}


int main() {
    printf("=== DETECTIVE QUEST ===\n");

    Sala *mansao = construirMansao();
    HashTable *tabela = construirTabelaHash();
    PistaNode *pistas = NULL;

    explorarSalas(mansao, &pistas, tabela);
    verificarSuspeitoFinal(pistas, tabela);

    printf("\nFim do jogo!\n");
    return 0;
}
