#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Arquivo
{
    char nome[500];
    int tamanho;
    struct Arquivo *proximo;
};

void mostrarMenu(void);

struct Arquivo *criarArquivo(const char *nome, int tamanho);

void adicionarArquivo(struct Arquivo **inicio, struct Arquivo *novo);

struct Arquivo *buscarArquivo(struct Arquivo *inicio, const char *nome);

void removerArquivo(struct Arquivo **inicio, const char *nome);

void liberarLista(struct Arquivo *inicio);

int main()
{

    long long totalTamanho = 0;
    char nome[500];
    int tamanho;
    int opcao = -1;

    struct Arquivo *arquivo = NULL;

    do
    {
        mostrarMenu();

        int leitura = scanf("%d", &opcao);

        if (leitura == EOF)
        {
            printf("\nEncerrando FileManager...\n");
            break;
        }

        if (leitura != 1)
        {
            printf("\nOpcao invalida!\n");

            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;

            continue;
        }

        switch (opcao)
        {

        case 1:
        {
            printf("\nCriar arquivo selecionado!\n");
            printf("\nDigite o nome do arquivo: ");
            if (scanf("%499s", nome) != 1)
            {
                printf("\nErro ao ler o nome!\n");
                break;
            }
            printf("Digite o tamanho do arquivo em bytes: ");

            if (scanf("%d", &tamanho) != 1 || tamanho < 0)
            {
                printf("\nTamanho invalido!\n");

                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;

                break;
            }

            if (buscarArquivo(arquivo, nome) != NULL)
            {
                printf("\nJa existe um arquivo com esse nome!\n");
                break;
            }

            struct Arquivo *novo = criarArquivo(nome, tamanho);

            if (novo == NULL)
            {
                printf("\nErro ao criar arquivo!\n");
                break;
            }

            adicionarArquivo(&arquivo, novo);

            printf("\nArquivo criado com sucesso!\n");
            break;
        }
        case 2:
        {
            printf("\nListar arquivos selecionado!\n");
            printf("\n========== ARQUIVOS ==========\n");

            if (arquivo == NULL)
            {
                printf("Nenhum arquivo encontrado!\n");
                break;
            }

            struct Arquivo *atual = arquivo;

            while (atual != NULL)
            {
                printf("\nNome: %s\n", atual->nome);
                printf("Tamanho: %d bytes\n", atual->tamanho);

                atual = atual->proximo;
            }

            printf("==============================\n");
            break;
        }
        case 3:
        {
            printf("\nBuscar arquivo selecionado!\n");
            printf("\n========== BUSCAR ARQUIVO ==========\n");

            printf("Digite o nome do arquivo: ");
            if (scanf("%499s", nome) != 1)
            {
                printf("\nErro ao ler o nome!\n");
                break;
            }
            struct Arquivo *encontrado = buscarArquivo(arquivo, nome);

            if (encontrado != NULL)
            {
                printf("\nArquivo encontrado!\n");
                printf("Nome: %s\n", encontrado->nome);
                printf("Tamanho: %d bytes\n", encontrado->tamanho);
            }
            else
            {
                printf("\nArquivo nao encontrado!\n");
            }

            break;
        }
        case 4:
        {
            printf("\nRemover arquivo selecionado!\n");
            printf("\n========== REMOVER ARQUIVO ==========\n");

            printf("Digite o nome do arquivo: ");
            if (scanf("%499s", nome) != 1)
            {
                printf("\nErro ao ler o nome!\n");
                break;
            }

            if (buscarArquivo(arquivo, nome) == NULL)
            {
                printf("\nArquivo nao encontrado!\n");
                break;
            }

            removerArquivo(&arquivo, nome);

            printf("\nArquivo removido com sucesso!\n");
            break;
        }
        case 5:
        {
            printf("\nVer armazenamento selecionado!\n");
            printf("\n========== ARMAZENAMENTO ==========\n");

            totalTamanho = 0;

            struct Arquivo *atual = arquivo;

            while (atual != NULL)
            {
                totalTamanho += atual->tamanho;
                atual = atual->proximo;
            }

            printf("Espaco utilizado: %lld bytes\n", totalTamanho);
            printf("===================================\n");

            break;
        }
        case 0:
            printf("\nEncerrando FileManager...\n");
            break;

        default:
            printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);

    liberarLista(arquivo);

    return 0;
}

void mostrarMenu(void)
{
    printf("\n");
    printf("\n");
    printf("|------------------------------------------|\n");
    printf("|               FILE MANAGER               |\n");
    printf("|------------------------------------------|\n");
    printf("|                                          |\n");
    printf("|  [1] Criar arquivo                       |\n");
    printf("|  [2] Listar arquivos                     |\n");
    printf("|  [3] Buscar arquivo                      |\n");
    printf("|  [4] Remover arquivo                     |\n");
    printf("|  [5] Ver armazenamento                   |\n");
    printf("|  [0] Sair                                |\n");
    printf("|                                          |\n");
    printf("|------------------------------------------|\n");
    printf("\nEscolha uma opcao: ");
}

struct Arquivo *criarArquivo(const char *nome, int tamanho)
{
    struct Arquivo *novo = malloc(sizeof(struct Arquivo));

    if (novo == NULL)
    {
        return NULL;
    }

    if (strlen(nome) >= sizeof(novo->nome))
    {
        free(novo);
        return NULL;
    }

    strcpy(novo->nome, nome);
    novo->tamanho = tamanho;
    novo->proximo = NULL;

    return novo;
}

void adicionarArquivo(struct Arquivo **inicio, struct Arquivo *novo)
{

    if (*inicio == NULL)
    {
        *inicio = novo;
        return;
    }

    struct Arquivo *atual = *inicio;

    while (atual->proximo != NULL)
    {
        atual = atual->proximo;
    }
    atual->proximo = novo;
}

struct Arquivo *buscarArquivo(struct Arquivo *inicio, const char *nome)
{
    struct Arquivo *atual = inicio;
    while (atual != NULL)
    {
        if (strcmp(atual->nome, nome) == 0)
        {
            return atual;
        }
        atual = atual->proximo;
    }

    return NULL;
}

void removerArquivo(struct Arquivo **inicio, const char *nome)
{
    struct Arquivo *atual = *inicio;
    struct Arquivo *anterior = NULL;
    while (atual != NULL)
    {
        if (strcmp(atual->nome, nome) == 0)
        {
            if (anterior == NULL)
            {
                *inicio = atual->proximo;
            }
            else
            {

                anterior->proximo = atual->proximo;
            }

            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

void liberarLista(struct Arquivo *inicio)
{
    struct Arquivo *atual = inicio;

    struct Arquivo *proximo = NULL;

    while (atual != NULL)
    {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}
