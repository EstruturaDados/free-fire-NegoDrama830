#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// ----------------------------
// Structs
// ----------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No *proximo;
} No;

// ----------------------------
// Variáveis globais
// ----------------------------
int comparacoes = 0; // contador de comparações para análise

// ----------------------------
// Funções para Vetor
// ----------------------------
void inserirItemVetor(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("Mochila (vetor) cheia!\n");
        return;
    }
    Item novo;
    printf("Nome: "); fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    printf("Tipo: "); fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    printf("Quantidade: "); scanf("%d", &novo.quantidade);
    getchar();
    mochila[*qtd] = novo;
    (*qtd)++;
    printf("Item inserido (vetor)!\n");
}

void removerItemVetor(Item mochila[], int *qtd) {
    char nome[30];
    printf("Nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *qtd - 1; j++) {
                mochila[j] = mochila[j+1];
            }
            (*qtd)--;
            printf("Item removido (vetor)!\n");
            return;
        }
    }
    printf("Item nao encontrado!\n");
}

void listarItensVetor(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("Mochila (vetor) vazia!\n");
        return;
    }
    for (int i = 0; i < qtd; i++) {
        printf("%d) Nome: %s | Tipo: %s | Qtd: %d\n",
               i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

int buscarSequencialVetor(Item mochila[], int qtd, char nome[]) {
    comparacoes = 0;
    for (int i = 0; i < qtd; i++) {
        comparacoes++;
        if (strcmp(mochila[i].nome, nome) == 0) return i;
    }
    return -1;
}

// Ordenação Bubble Sort
void ordenarVetor(Item mochila[], int qtd) {
    Item temp;
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j+1].nome) > 0) {
                temp = mochila[j];
                mochila[j] = mochila[j+1];
                mochila[j+1] = temp;
            }
        }
    }
    printf("Itens ordenados por nome (vetor).\n");
}

// Busca binária
int buscarBinariaVetor(Item mochila[], int qtd, char nome[]) {
    int inicio = 0, fim = qtd - 1, meio;
    comparacoes = 0;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// ----------------------------
// Funções para Lista Encadeada
// ----------------------------
void inserirItemLista(No **inicio) {
    No *novo = (No*) malloc(sizeof(No));
    printf("Nome: "); fgets(novo->dados.nome, sizeof(novo->dados.nome), stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';
    printf("Tipo: "); fgets(novo->dados.tipo, sizeof(novo->dados.tipo), stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';
    printf("Quantidade: "); scanf("%d", &novo->dados.quantidade);
    getchar();
    novo->proximo = *inicio;
    *inicio = novo;
    printf("Item inserido (lista)!\n");
}

void removerItemLista(No **inicio) {
    char nome[30];
    printf("Nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No *atual = *inicio, *anterior = NULL;
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) *inicio = atual->proximo;
            else anterior->proximo = atual->proximo;
            free(atual);
            printf("Item removido (lista)!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item nao encontrado!\n");
}

void listarItensLista(No *inicio) {
    if (inicio == NULL) {
        printf("Mochila (lista) vazia!\n");
        return;
    }
    int i = 1;
    while (inicio != NULL) {
        printf("%d) Nome: %s | Tipo: %s | Qtd: %d\n",
               i++, inicio->dados.nome, inicio->dados.tipo, inicio->dados.quantidade);
        inicio = inicio->proximo;
    }
}

No* buscarSequencialLista(No *inicio, char nome[]) {
    comparacoes = 0;
    while (inicio != NULL) {
        comparacoes++;
        if (strcmp(inicio->dados.nome, nome) == 0) return inicio;
        inicio = inicio->proximo;
    }
    return NULL;
}

// ----------------------------
// Programa principal
// ----------------------------
int main() {
    Item mochilaVetor[MAX_ITENS];
    int qtdVetor = 0;
    No *mochilaLista = NULL;

    int opcao, estrutura;

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Usar mochila com VETOR\n");
        printf("2. Usar mochila com LISTA ENCADEADA\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &estrutura);
        getchar();

        if (estrutura == 1) {
            do {
                printf("\n--- Mochila com Vetor ---\n");
                printf("1. Inserir\n2. Remover\n3. Listar\n4. Buscar Sequencial\n5. Ordenar\n6. Buscar Binaria\n0. Voltar\n");
                printf("Opcao: ");
                scanf("%d", &opcao);
                getchar();
                if (opcao == 1) inserirItemVetor(mochilaVetor, &qtdVetor);
                else if (opcao == 2) removerItemVetor(mochilaVetor, &qtdVetor);
                else if (opcao == 3) listarItensVetor(mochilaVetor, qtdVetor);
                else if (opcao == 4) {
                    char nome[30];
                    printf("Nome a buscar: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = '\0';
                    int idx = buscarSequencialVetor(mochilaVetor, qtdVetor, nome);
                    if (idx != -1) printf("Encontrado: %s | Comparacoes: %d\n", mochilaVetor[idx].nome, comparacoes);
                    else printf("Nao encontrado | Comparacoes: %d\n", comparacoes);
                }
                else if (opcao == 5) ordenarVetor(mochilaVetor, qtdVetor);
                else if (opcao == 6) {
                    char nome[30];
                    printf("Nome a buscar: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = '\0';
                    int idx = buscarBinariaVetor(mochilaVetor, qtdVetor, nome);
                    if (idx != -1) printf("Encontrado: %s | Comparacoes: %d\n", mochilaVetor[idx].nome, comparacoes);
                    else printf("Nao encontrado | Comparacoes: %d\n", comparacoes);
                }
            } while (opcao != 0);
        }
        else if (estrutura == 2) {
            do {
                printf("\n--- Mochila com Lista ---\n");
                printf("1. Inserir\n2. Remover\n3. Listar\n4. Buscar Sequencial\n0. Voltar\n");
                printf("Opcao: ");
                scanf("%d", &opcao);
                getchar();
                if (opcao == 1) inserirItemLista(&mochilaLista);
                else if (opcao == 2) removerItemLista(&mochilaLista);
                else if (opcao == 3) listarItensLista(mochilaLista);
                else if (opcao == 4) {
                    char nome[30];
                    printf("Nome a buscar: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = '\0';
                    No *res = buscarSequencialLista(mochilaLista, nome);
                    if (res != NULL) printf("Encontrado: %s | Comparacoes: %d\n", res->dados.nome, comparacoes);
                    else printf("Nao encontrado | Comparacoes: %d\n", comparacoes);
                }
            } while (opcao != 0);
        }
    } while (estrutura != 0);

    printf("Fim do programa!\n");
    return 0;
}
