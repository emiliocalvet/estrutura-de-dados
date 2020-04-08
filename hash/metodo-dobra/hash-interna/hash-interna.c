#include <stdio.h>
#include <stdlib.h>

#define P 100     //Endereços base.
#define S 37      //Zona de colisão.
#define M (P + S) //Tamanho da tabela.

typedef struct no
{
    int chave;
    int info;
    int pos;
    struct no *prox;
} No;

typedef No *Hash[M];

int hash(int chave);
int insere(Hash tabela, int chave, int info);
No *busca(Hash tabela, int chave);
int remover(Hash tabela, int chave);
int colisao(Hash tabela);

int main()
{
    int info = 0;
    int chave = 0;
    int escolha_menu = 0;

    Hash tabela;
    No *aux = NULL;

    for (int i = 0; i < M; i++) //Inicializando meu vetor de ponteiros para No com endereços vazios.
        tabela[i] = NULL;

    while (escolha_menu != -1)
    {
        system("clear");

        printf(" ________________________________ \n");
        printf("|######### HASH-INTERNA #########|\n");
        printf("|                                |\n");
        printf("|          [1] INSERIR           |\n");
        printf("|          [2] BUSCAR            |\n");
        printf("|          [3] REMOVER           |\n");
        printf("|          [4] SAIR              |\n");
        printf("|________________________________|\n");
        printf("\n");

        printf("Digite a opcao desejada: ");
        scanf("%d", &escolha_menu);

        switch (escolha_menu)
        {
        case 1:;
            int pos;
            printf("\nDigite o numero deseja guardar: ");
            scanf("%d", &info);
            setbuf(stdin, NULL);
            printf("\nDigite o numero da chave de acesso: ");
            scanf("%d", &chave);
            setbuf(stdin, NULL);
            pos = insere(tabela, chave, info);
            printf("\nInserido na posicao %d!", pos);
            printf("\nPressione [ENTER] para retornar ao menu.");
            setbuf(stdin, NULL);
            getchar();
            break;

        case 2:
            printf("\nDigite o numero da chave de acesso: ");
            scanf("%d", &chave);
            aux = busca(tabela, chave);
            if (aux != NULL)
            {
                printf("\nNumero guardado: %d", aux->info);
                printf("\nPressione [ENTER] para retornar ao menu.");
                setbuf(stdin, NULL);
                getchar();
            }
            else
            {
                printf("Nao encontrado!");
                printf("\nPressione [ENTER] para retornar ao menu.");
                setbuf(stdin, NULL);
                getchar();
            }
            break;

        case 3:
            printf("\nDigite o numero da chave de acesso: ");
            scanf("%d", &chave);
            if (remover(tabela, chave))
            {
                printf("Removido com sucesso!");
                printf("\nPressione [ENTER] para retornar ao menu.");
                setbuf(stdin, NULL);
                getchar();
            }
            else
            {
                printf("Nao encontrado!");
                printf("\nPressione [ENTER] para retornar ao menu.");
                setbuf(stdin, NULL);
                getchar();
            }
            break;

        case 4:
            escolha_menu = -1;
            printf("Bye!\n\n");
            break;

        default:
            printf("\nOpção incorreta, pressione [ENTER] e tente novamente!");
            escolha_menu = 0;
            setbuf(stdin, NULL);
            getchar();
            break;
        }
    }
    return 0;
}

int hash(int chave) //Método da divisão.
{
    return (chave % M);
}

int insere(Hash tabela, int chave, int info)
{
    No *aux = busca(tabela, chave);
    int h = hash(chave);

    if (aux == NULL)
    {
        aux = tabela[h];
        //Verifica colisão.
        if (aux == NULL)
        {
            //Insere elemento.
            aux = (No *)malloc(sizeof(No));
            aux->chave = chave;
            aux->info = info;
            aux->pos = h;
            aux->prox = NULL;
            tabela[h] = aux;
            return h;
        }
        else
        {
            h = colisao(tabela);
            if (h == -1)
            {
                printf("\nOVERFLOW\n");
                return h;
            }
            else
            {
                while (aux->prox != NULL)
                    aux = aux->prox;
                //Insere elemento.
                aux->prox = (No *)malloc(sizeof(No));
                aux = aux->prox;
                aux->chave = chave;
                aux->info = info;
                aux->pos = h;
                aux->prox = NULL;
                tabela[h] = aux;
                return h;
            }
        }
    }
}

No *busca(Hash tabela, int chave)
{
    int h = hash(chave);
    No *aux = tabela[h];

    while (aux != NULL)
    {
        if (aux->chave == chave)
            return aux;
        aux = aux->prox;
    }
    return NULL;
}

int remover(Hash tabela, int chave)
{
    No *aux = busca(tabela, chave);

    if (aux != NULL)
    {
        int h = hash(chave);
        aux = tabela[h];

        if (aux != NULL)
        {
            No *ant;

            if (aux->chave == chave)
            {
                ant = aux;
                aux = aux->prox;
                tabela[aux->pos] = NULL;
                free(ant);
                return 1;
            }
            else
            {
                while (aux->prox != NULL)
                {
                    ant = aux;
                    aux = aux->prox;
                    if (aux->chave == chave)
                    {
                        ant->prox = aux->prox;
                        tabela[aux->pos] = NULL;
                        free(aux);
                        return 1;
                    }
                }
                if (aux->chave == chave)
                {
                    tabela[aux->pos] = NULL;
                    free(aux);
                    return 1;
                }
            }
        }
    }
    return 0;
}

int colisao(Hash tabela) //Verifica posicao disponível na zona de colisão.
{
    for (int i = P; i < M; i++)
        if (tabela[i] == NULL)
            return i;
    return -1;
}
