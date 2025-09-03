#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10   // limite de itens da mochila

// Struct que representa cada item do inventário
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Funções do sistema
void inserirItem(Item mochila[], int *qtd);
void removerItem(Item mochila[], int *qtd);
void listarItens(Item mochila[], int qtd);
void buscarItem(Item mochila[], int qtd);

int main() {
    Item mochila[MAX_ITENS];
    int qtd = 0; // quantidade atual de itens na mochila
    int opcao;

    do {
        printf("\n===== MOCHILA DO JOGADOR =====\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer do teclado

        switch(opcao) {
            case 1:
                inserirItem(mochila, &qtd);
                listarItens(mochila, qtd);
                break;
            case 2:
                removerItem(mochila, &qtd);
                listarItens(mochila, qtd);
                break;
            case 3:
                listarItens(mochila, qtd);
                break;
            case 4:
                buscarItem(mochila, qtd);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}

// Função para inserir item na mochila
void inserirItem(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("Digite o nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // remove \n do final

    printf("Digite o tipo do item (arma, municao, cura...): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar(); // limpa o buffer

    mochila[*qtd] = novo;
    (*qtd)++;

    printf("Item adicionado com sucesso!\n");
}

// Função para remover item pelo nome
void removerItem(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a ser removido: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int encontrado = -1;
    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        for (int i = encontrado; i < *qtd - 1; i++) {
            mochila[i] = mochila[i+1]; // desloca os itens para "tapar o buraco"
        }
        (*qtd)--;
        printf("Item removido com sucesso!\n");
    } else {
        printf("Item nao encontrado!\n");
    }
}

// Função para listar os itens
void listarItens(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    printf("\n--- Itens na mochila ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Função de busca sequencial pelo nome do item
void buscarItem(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a ser buscado: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }
    printf("Item nao encontrado!\n");
}