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
int inserir(Hash tabela, int chave, int info);
No *buscar(Hash tabela, int chave);
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
        printf("|########## HASH-INTERNA ########|\n");
        printf("|                                |\n");
        printf("|          [3] INSERIR           |\n");
        printf("|          [4] BUSCAR            |\n");
        printf("|          [5] REMOVER           |\n");
        printf("|          [6] SAIR              |\n");
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
            pos = inserir(tabela, chave, info);
            if (pos != -1)
                printf("\nInserido na posicao %d!", pos);
            else
                printf("\nErro. Tente uma chave diferente!");
            printf("\nPressione [ENTER] para retornar ao menu.");
            setbuf(stdin, NULL);
            getchar();
            break;

        case 2:
            printf("\nDigite o numero da chave de acesso: ");
            scanf("%d", &chave);
            aux = buscar(tabela, chave);
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

//Método da multiplicacao.
int hash(int chave)
{
    int posicao;
    int aux[7];
    chave = chave * chave;

    for (int i = 0; i < 7; i++)
    {
        aux[6 - i] = chave % 10;
        chave = chave / 10;
    }

    posicao = (aux[2] * 100) + (aux[3] * 10) + aux[4];

    if (posicao > M)
    {
        posicao = posicao - (aux[2] * 100);
    }

    return posicao;
}

int inserir(Hash tabela, int chave, int info)
{
    No *aux = buscar(tabela, chave);
    int h = hash(chave);

    //Verifica chave repetida.
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

No *buscar(Hash tabela, int chave)
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
    No *aux = buscar(tabela, chave);

    if (aux != NULL) //Verifica se a chave está cadastrada.
    {
        int h = hash(chave);
        aux = tabela[h];

        if (aux != NULL) //Sem utilidade, REMOVER IF INUTIL.
        {
            No *ant;

            //Verifica primeiro nó da lista.
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
                //Verifica nós intermediários.
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
                //Verifica último nó da lista.
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

//Verifica posicao disponível na zona de colisão.
int colisao(Hash tabela)
{
    for (int i = P; i < M; i++)
        if (tabela[i] == NULL)
            return i;
    return -1;
}
