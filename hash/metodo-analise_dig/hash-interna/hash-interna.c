#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define P 100     //Endereços base.
#define S 50      //Zona de colisão.
#define M (P + S) //Tamanho da tabela.
#define N 20      //Quantidade de chaves - (CASO ALTERADO, ATUALIZAR VETOR DE CHAVES).

#define TAM_CHAVE 5 //Quantidade de digitos da chave - (CASO ALTERADO, ATUALIZAR VETOR DE CHAVES).
#define TAM_POS 2   //Quantidade de digitos da posição gerada - (CASO ALTERADO, ATUALIZAR TAMANHO DA TABELA).

typedef struct no
{
    int chave;
    int info;
    int pos;
    struct no *prox;
} No;

typedef No *Hash[M]; //Define o tipo Hash como um vetor de ponteiros para No de tamanho M.
/*======================================== Escopo Funções ========================================*/

int hash(int chave);
int insere(Hash tabela, int chave, int info);
No *busca(Hash tabela, int chave);
int remover(Hash tabela, int chave);
int colisao(Hash tabela);
void dec_to_vetor(int decimal, int *vetor, int tam);
int formar_posicao(int *chave);
void contar_digitos();
void calcular_dist();
void analisar_dist();
void analisar_digitos(int *chaves);
void exibir_analise();
void limpar_analise();
void insertion_sort(float *vetor, int tam);
void copia_vetor(float *vetor_origem, float *vetor_destino, int tam);
/*======================================== Variáveis Globais ======================================*/

int vetor_chaves[N] = {87437, 15568, 78694, 41491, 50159,
                       69749, 71395, 84251, 97075, 49598,
                       47987, 18470, 10033, 71079, 98093,
                       79545, 20370, 31497, 40554, 79228};

int matriz_chaves[N][TAM_CHAVE];       //cada chave em formato de vetor.
int quantidade_digitos[TAM_CHAVE][10]; //contagem de dígitos das chaves.
float distribuicao_digitos[TAM_CHAVE]; //distribuicao de cada digito.
int posicao_digitos[TAM_POS];          //posição dos dígitos de menor distribuição.
/*======================================== Função Main ============================================*/

int main()
{
    int info = 0;
    int chave = 0;
    int escolha_menu = 0;
    int analisado = 0;

    Hash tabela;
    No *aux = NULL;

    for (int i = 0; i < M; i++) //Inicializando meu vetor de ponteiros para No com endereços vazios.
        tabela[i] = NULL;

    while (escolha_menu != -1)
    {
        system("clear");

        printf(" ________________________________________ \n");
        printf("|############# HASH-INTERNA #############|\n");
        printf("|                                        |\n");
        printf("|          [1] ANALISAR DIGITOS          |\n");
        printf("|          [2] EXIBIR ANALISE            |\n");
        printf("|          [3] INSERIR                   |\n");
        printf("|          [4] BUSCAR                    |\n");
        printf("|          [5] REMOVER                   |\n");
        printf("|          [6] SAIR                      |\n");
        printf("|________________________________________|\n");
        printf("\n");

        printf("Digite a opcao desejada: ");
        scanf("%d", &escolha_menu);

        switch (escolha_menu)
        {
        case 1:
            limpar_analise();
            analisar_digitos(vetor_chaves);
            analisado = 1;
            printf("\nDigitos Analisados");
            printf("\nPressione [ENTER] para retornar ao menu.");
            setbuf(stdin, NULL);
            getchar();
            break;

        case 2:
            if (analisado)
                exibir_analise(TAM_CHAVE, N);
            else
            {
                printf("\nAnalisar digitos primeiro!");
                printf("\nPressione [ENTER] para retornar ao menu.");
                setbuf(stdin, NULL);
                getchar();
            }
            break;

        case 3:
            if (analisado)
            {
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
            }
            else
            {
                printf("\nAnalisar digitos primeiro!");
                printf("\nPressione [ENTER] para retornar ao menu.");
                setbuf(stdin, NULL);
                getchar();
            }
            break;

        case 4:
            if (analisado)
            {
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
                    printf("\nNao encontrado!");
                    printf("\nPressione [ENTER] para retornar ao menu.");
                    setbuf(stdin, NULL);
                    getchar();
                }
            }
            else
            {
                printf("\nAnalisar digitos primeiro!");
                printf("\nPressione [ENTER] para retornar ao menu.");
                setbuf(stdin, NULL);
                getchar();
            }
            break;

        case 5:
            if (analisado)
            {
                printf("\nDigite o numero da chave de acesso: ");
                scanf("%d", &chave);
                if (remover(tabela, chave))
                {
                    printf("\nRemovido com sucesso!");
                    printf("\nPressione [ENTER] para retornar ao menu.");
                    setbuf(stdin, NULL);
                    getchar();
                }
                else
                {
                    printf("\nNao encontrado!");
                    printf("\nPressione [ENTER] para retornar ao menu.");
                    setbuf(stdin, NULL);
                    getchar();
                }
            }
            else
            {
                printf("\nAnalisar digitos primeiro!");
                printf("\nPressione [ENTER] para retornar ao menu.");
                setbuf(stdin, NULL);
                getchar();
            }
            break;

        case 6:
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
/*================================= Funções para tratamento de colisão ================================*/

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
/*================================ Funções para análise dos dígitos ==================================*/

int hash(int chave)
{
    int posicao = 0;
    int aux[TAM_CHAVE];
    int mult = pow(10, (TAM_POS - 1));
    dec_to_vetor(chave, aux, TAM_CHAVE);
    for (int i = 0; i < TAM_POS; i++)
    {
        posicao = posicao + aux[posicao_digitos[i]] * mult;
        mult = mult / 10;
    }
    return posicao;
}

void dec_to_vetor(int decimal, int *vetor, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        vetor[(tam - 1) - i] = decimal % 10;
        decimal = decimal / 10;
    }
}

void contar_digitos()
{
    for (int i = 0; i < TAM_CHAVE; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < 10; k++)
                if (matriz_chaves[j][i] == k)
                    quantidade_digitos[i][k]++;
}

void calcular_dist()
{
    for (int i = 0; i < TAM_CHAVE; i++)
        for (int j = 0; j < 10; j++)
            distribuicao_digitos[i] =
                distribuicao_digitos[i] +
                (quantidade_digitos[i][j] *
                 pow((j - (N / 10)), 2));
}

void analisar_dist()
{
    float aux[TAM_CHAVE];
    copia_vetor(distribuicao_digitos, aux, TAM_CHAVE);
    insertion_sort(aux, TAM_CHAVE);
    for (int i = 0; i < TAM_POS; i++)
        for (int j = 0; j < TAM_CHAVE; j++)
            if (aux[i] == distribuicao_digitos[j])
                posicao_digitos[i] = j;
}

void analisar_digitos(int *chaves)
{
    for (int i = 0; i < N; i++)
        dec_to_vetor(chaves[i], matriz_chaves[i], TAM_CHAVE);

    contar_digitos();
    calcular_dist();
    analisar_dist();
}

void exibir_analise()
{
    printf("\n== INFORMACOES SOBRE A ANALISE ==\n\n");
    for (int i = 0; i < N; i++)
    {
        printf("Chave %2.d -> %d", i + 1, matriz_chaves[i][0]);
        for (int j = 1; j < TAM_CHAVE; j++)
            printf("%d", matriz_chaves[i][j]);
        printf("\n");
    }
    printf("=================================\n");
    for (int i = 0; i < TAM_CHAVE; ++i)
    {
        for (int j = 0; j < 10; j++)
            printf("Digito %d -> numero: %d -> qtd. = %d\n", i + 1, j, quantidade_digitos[i][j]);
        printf("=================================\n");
    }
    for (int i = 0; i < TAM_CHAVE; i++)
        printf("Distribuicao digito %d -> %.2f\n", i + 1, distribuicao_digitos[i]);
    printf("=================================\n");
    printf("Hash -> ");
    for (int i = 0; i < TAM_POS; i++)
        printf("|digito %d", posicao_digitos[i] + 1);
    printf("|\n");
    printf("\nPressione [ENTER] para retornar ao menu.");
    setbuf(stdin, NULL);
    getchar();
}

void limpar_analise()
{
    for (int i = 0; i < TAM_CHAVE; i++)
    {
        for (int j = 0; j < 10; j++)
            quantidade_digitos[i][j] = 0;
        distribuicao_digitos[i] = 0.0;
    }
}

void insertion_sort(float *vetor, int tam)
{
    int i, j;
    float aux;

    for (i = 1; i < tam; i++)
    {
        j = i - 1;
        aux = vetor[i];
        while (vetor[j] > aux && j >= 0)
        {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = aux;
    }
}

void copia_vetor(float *vetor_origem, float *vetor_destino, int tam)
{
    for (int i = 0; i < tam; i++)
        vetor_destino[i] = vetor_origem[i];
}