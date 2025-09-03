#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// ----------------------------
// Struct principal
// ----------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // de 1 a 10
} Componente;

// ----------------------------
// Variáveis globais
// ----------------------------
int comparacoes = 0; // contador de comparações

// ----------------------------
// Funções utilitárias
// ----------------------------
void mostrarComponentes(Componente v[], int n) {
    printf("\n--- Lista de Componentes ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d) Nome: %s | Tipo: %s | Prioridade: %d\n",
               i+1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

// ----------------------------
// Algoritmos de ordenação
// ----------------------------

// Bubble Sort por nome
void bubbleSortNome(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j+1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
}

// Insertion Sort por tipo
void insertionSortTipo(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;
        while (j >= 0 && (comparacoes++, strcmp(v[j].tipo, chave.tipo) > 0)) {
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = chave;
    }
}

// Selection Sort por prioridade
void selectionSortPrioridade(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n-1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            Componente temp = v[i];
            v[i] = v[min];
            v[min] = temp;
        }
    }
}

// ----------------------------
// Busca binária (somente por nome)
// ----------------------------
int buscaBinariaPorNome(Componente v[], int n, char chave[]) {
    int inicio = 0, fim = n-1, meio;
    comparacoes = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(v[meio].nome, chave);
        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// ----------------------------
// Função para medir tempo
// ----------------------------
void medirTempo(void (*algoritmo)(Componente[], int), Componente v[], int n, char criterio[]) {
    clock_t inicio, fim;
    inicio = clock();
    algoritmo(v, n);
    fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\nOrdenacao por %s concluida!\n", criterio);
    printf("Comparacoes realizadas: %d\n", comparacoes);
    printf("Tempo de execucao: %.6f segundos\n", tempo);
    mostrarComponentes(v, n);
}

// ----------------------------
// Programa principal
// ----------------------------
int main() {
    Componente torre[MAX_COMPONENTES];
    int qtd = 0, opcao;

    do {
        printf("\n===== MENU TORRE DE FUGA =====\n");
        printf("1. Cadastrar componente\n");
        printf("2. Listar componentes\n");
        printf("3. Ordenar por nome (Bubble Sort)\n");
        printf("4. Ordenar por tipo (Insertion Sort)\n");
        printf("5. Ordenar por prioridade (Selection Sort)\n");
        printf("6. Buscar componente-chave (binaria por nome)\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            if (qtd >= MAX_COMPONENTES) {
                printf("Limite maximo atingido!\n");
            } else {
                printf("Nome: "); fgets(torre[qtd].nome, sizeof(torre[qtd].nome), stdin);
                torre[qtd].nome[strcspn(torre[qtd].nome, "\n")] = '\0';
                printf("Tipo: "); fgets(torre[qtd].tipo, sizeof(torre[qtd].tipo), stdin);
                torre[qtd].tipo[strcspn(torre[qtd].tipo, "\n")] = '\0';
                printf("Prioridade (1 a 10): "); scanf("%d", &torre[qtd].prioridade);
                getchar();
                qtd++;
                printf("Componente cadastrado!\n");
            }
        }
        else if (opcao == 2) {
            mostrarComponentes(torre, qtd);
        }
        else if (opcao == 3) {
            medirTempo(bubbleSortNome, torre, qtd, "nome (Bubble Sort)");
        }
        else if (opcao == 4) {
            medirTempo(insertionSortTipo, torre, qtd, "tipo (Insertion Sort)");
        }
        else if (opcao == 5) {
            medirTempo(selectionSortPrioridade, torre, qtd, "prioridade (Selection Sort)");
        }
        else if (opcao == 6) {
            if (qtd == 0) {
                printf("Nao ha componentes cadastrados!\n");
            } else {
                char chave[30];
                printf("Digite o nome do componente-chave: ");
                fgets(chave, sizeof(chave), stdin);
                chave[strcspn(chave, "\n")] = '\0';
                int idx = buscaBinariaPorNome(torre, qtd, chave);
                if (idx != -1) {
                    printf("Componente encontrado: %s | Tipo: %s | Prioridade: %d\n",
                           torre[idx].nome, torre[idx].tipo, torre[idx].prioridade);
                    printf("Comparacoes na busca binaria: %d\n", comparacoes);
                } else {
                    printf("Componente nao encontrado! | Comparacoes: %d\n", comparacoes);
                }
            }
        }
    } while (opcao != 0);

    printf("Fim da simulacao! Torre montada ou jogador eliminado...\n");
    return 0;
}
