#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20


// STRUCT DE COMPONENTE

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;


// FUNÇÕES AUXILIARES

void mostrarComponentes(Componente comp[], int n) {
    printf("\n=== LISTA DE COMPONENTES ===\n");
    for (int i = 0; i < n; i++) {
        printf("%2d. Nome: %-20s | Tipo: %-15s | Prioridade: %d\n",
               i + 1, comp[i].nome, comp[i].tipo, comp[i].prioridade);
    }
    printf("============================\n");
}

void copiarArray(Componente origem[], Componente destino[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}

// ORDENAR POR NOME 

int ordenarPorNome(Componente comp[], int n) {
    int comparacoes = 0;
    Componente temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(comp[j].nome, comp[j + 1].nome) > 0) {
                temp = comp[j];
                comp[j] = comp[j + 1];
                comp[j + 1] = temp;
            }
        }
    }
    return comparacoes;
}


// INSERTION SORT (por tipo)

int insertionSortTipo(Componente comp[], int n) {
    int comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = comp[i];
        int j = i - 1;

        while (j >= 0 && strcmp(comp[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            comp[j + 1] = comp[j];
            j--;
        }
        if (j >= 0) comparacoes++;
        comp[j + 1] = chave;
    }
    return comparacoes;
}


// SELECTION SORT

int selectionSortPrioridade(Componente comp[], int n) {
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (comp[j].prioridade < comp[min].prioridade)
                min = j;
        }
        if (min != i) {
            Componente temp = comp[i];
            comp[i] = comp[min];
            comp[min] = temp;
        }
    }
    return comparacoes;
}


// busca por nome

int buscarPorNome(Componente comp[], int n, char chave[]) {
    int inicio = 0, fim = n - 1, comparacoes = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(chave, comp[meio].nome);
        if (cmp == 0) {
            printf("\n>>> Componente encontrado: %s (Tipo: %s, Prioridade: %d)\n",
                   comp[meio].nome, comp[meio].tipo, comp[meio].prioridade);
            printf("Comparações na busca: %d\n", comparacoes);
            return meio;
        } else if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }
    printf("\nComponente não encontrado.\n");
    printf("Comparações na busca: %d\n", comparacoes);
    return -1;
}


// MENU

int main() {
    Componente componentes[MAX], copia[MAX];
    int n, opcao;
    char chave[30];
    clock_t inicio, fim;
    double tempo;
    int comparacoes;

    printf("=== SISTEMA DE MONTAGEM DA TORRE DE FUGA ===\n");
    printf("Quantos componentes deseja cadastrar (max %d)? ", MAX);
    scanf("%d", &n);
    getchar(); // limpa o buffer

    for (int i = 0; i < n; i++) {
        printf("\nComponente %d:\n", i + 1);
        printf("Nome: ");
        fgets(componentes[i].nome, 30, stdin);
        componentes[i].nome[strcspn(componentes[i].nome, "\n")] = 0;

        printf("Tipo: ");
        fgets(componentes[i].tipo, 20, stdin);
        componentes[i].tipo[strcspn(componentes[i].tipo, "\n")] = 0;

        printf("Prioridade (1-10): ");
        scanf("%d", &componentes[i].prioridade);
        getchar();
    }

    do {
        printf("\n=== MENU ===\n");
        printf("1. Ordenar por nome (Bubble Sort)\n");
        printf("2. Ordenar por tipo (Insertion Sort)\n");
        printf("3. Ordenar por prioridade (Selection Sort)\n");
        printf("4. Buscar componente por nome (requer ordenação por nome)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        copiarArray(componentes, copia, n);

        switch (opcao) {
            case 1:
                inicio = clock();
                comparacoes = ordenarPorNome(copia, n);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                mostrarComponentes(copia, n);
                printf("Comparações: %d | Tempo: %.6f s\n", comparacoes, tempo);
                break;

            case 2:
                inicio = clock();
                comparacoes = insertionSortTipo(copia, n);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                mostrarComponentes(copia, n);
                printf("Comparações: %d | Tempo: %.6f s\n", comparacoes, tempo);
                break;

            case 3:
                inicio = clock();
                comparacoes = selectionSortPrioridade(copia, n);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                mostrarComponentes(copia, n);
                printf("Comparações: %d | Tempo: %.6f s\n", comparacoes, tempo);
                break;

            case 4:
                printf("\nDigite o nome do componente-chave: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = 0;
                ordenarPorNome(copia, n); // obrigatória para busca binária
                buscarPorNome(copia, n, chave);
                break;

            case 0:
                printf("\nEncerrando o sistema. Boa sorte na fuga!\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
