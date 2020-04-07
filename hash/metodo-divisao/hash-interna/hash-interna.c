#include <stdio.h>
#include <stdlib.h>

#define P 100     //Endereços base.
#define S 37      //Zona de colisão.
#define M (P + S) //Tamanho da tabela (n° primo).

typedef struct no
{
    int chave;
    int info;
    int prox;
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

        printf(" ___________________________________________ \n");
        printf("|############### HASH-INTERNA ##############|\n");
        printf("|                                           |\n");
        printf("|                [1] INSERIR                |\n");
        printf("|                [2] BUSCAR                 |\n");
        printf("|                [3] REMOVER                |\n");
        printf("|                [4] SAIR                   |\n");
        printf("|___________________________________________|\n");

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
            aux->prox = -1;
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
                //Percorre a lista de colisão interna até o último elemento.
                while (aux->prox != -1)
                    aux = tabela[aux->prox];
                aux->prox = h;
                //Insere elemento.
                aux = (No *)malloc(sizeof(No));
                aux->chave = chave;
                aux->info = info;
                aux->prox = -1;
                tabela[h] = aux;
                return h;
            }
        }
    }
    return -2;
}

No *busca(Hash tabela, int chave)
{
    int h = hash(chave);
    No *aux = tabela[h];

    if (aux != NULL)
    {
        if (aux->prox == -1)
        {
            if (aux->chave == chave)
                return aux;
        }
        else
        {
            while (aux->prox != -1)
            {
                if (aux->chave == chave)
                    return aux;
                aux = tabela[aux->prox];
                if (aux->prox == -1)
                    if (aux->chave == chave)
                        return aux;
            }
        }
    }
    return NULL;
}

int remover(Hash tabela, int chave)
{
    No *aux = busca(tabela, chave);
    if (aux != NULL)
    {
        free(aux);
        aux = NULL;
        return 1;
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