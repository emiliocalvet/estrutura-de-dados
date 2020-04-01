#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 100        //Tamanho da tabela.
#define QTD_CHAVE 20 //Quantidade de chaves - (CASO ALTERADO, ATUALIZAR VETOR DE CHAVES).
#define TAM_CHAVE 5  //Quantidade de digitos da chave - (CASO ALTERADO, ATUALIZAR VETOR DE CHAVES).
#define TAM_POS 2    //Quantidade de digitos da posição gerada - (CASO ALTERADO, ATUALIZAR TAMANHO DA TABELA).

typedef struct no
{
    int chave;
    int info;
    struct no *prox;
} No;

typedef No *Hash[N];

/*======================================== Escopo Funções ========================================*/
int hash(int chave, int tam_chave, int tam_pos);
int insere(Hash tabela, int chave, int tam_chave, int info, int tam_pos);
No *busca(Hash tabela, int chave, int tam_chave, int tam_pos);
int remover(Hash tabela, int chave, int tam_chave, int tam_pos);
void dec_to_vetor(int decimal, int *vetor, int tam);
int formar_posicao(int *chave, int tam_chave, int tam_pos);
void contar_digitos(int tam_chave, int qtd_chave);
void calcular_dist(int tam_chave, int qtd_chave);
void analisar_dist(int tam_chave, int tam_pos);
void analisar_digitos(int *chaves, int tam_chave, int qtd_chave, int tam_pos);
void exibir_analise(int tam_chave, int qtd_chave);
void limpar_analise(int tam_chave, int qtd_chave);
void insertion_sort(float *vetor, int tam);
void copia_vetor(float *vetor_origem, float *vetor_destino, int tam);

/*======================================== Variáveis Globais ======================================*/
int vetor_chaves[QTD_CHAVE] = {87437, 15568, 78694, 41491, 50159,
                               69749, 71395, 84251, 97075, 49598,
                               47987, 18470, 10033, 71079, 98093,
                               79545, 20370, 31497, 40554, 79228};

int matriz_chaves[QTD_CHAVE][TAM_CHAVE]; //cada chave em formato de vetor.
int quantidade_digitos[TAM_CHAVE][10];   //contagem de dígitos das chaves.
float distribuicao_digitos[TAM_CHAVE];   //distribuicao de cada digito.
int posicao_digitos[TAM_POS];            //posição dos dígitos de menor distribuição.

/*======================================== Função Main ============================================*/
int main()
{
    int info = 0;
    int chave = 0;
    int escolha_menu = 0;
    int analisado = 0;

    Hash tabela;
    No *aux = NULL;

    for (int i = 0; i < N; i++) //Inicializando meu vetor de ponteiros para No com endereços vazios.
        tabela[i] = NULL;

    while (escolha_menu != -1)
    {
        system("clear");

        printf(" ________________________________________ \n");
        printf("|############## HASH-EXTERNA ############|\n");
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
            limpar_analise(TAM_CHAVE, QTD_CHAVE);
            analisar_digitos(vetor_chaves, TAM_CHAVE, QTD_CHAVE, TAM_POS);
            analisado = 1;
            printf("\nDigitos Analisados");
            printf("\nPressione [ENTER] para retornar ao menu.");
            setbuf(stdin, NULL);
            getchar();
            break;

        case 2:
            if (analisado)
                exibir_analise(TAM_CHAVE, QTD_CHAVE);
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
                int aux;
                printf("\nDigite o numero deseja guardar: ");
                scanf("%d", &info);
                setbuf(stdin, NULL);
                printf("\nDigite o numero da chave de acesso: ");
                scanf("%d", &chave);
                setbuf(stdin, NULL);
                aux = insere(tabela, chave, TAM_CHAVE, info, TAM_POS);
                printf("\nInserido na posicao %d!", aux);
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
                aux = busca(tabela, chave, TAM_CHAVE, TAM_POS);
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
                if (remover(tabela, chave, TAM_CHAVE, TAM_POS))
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
int insere(Hash tabela, int chave, int tam_chave, int info, int tam_pos)
{
    No *aux = busca(tabela, chave, tam_chave, tam_pos);
    int h = hash(chave, tam_chave, tam_pos);

    if (aux == NULL) // não encontrou o elemento.
    {
        aux = (No *)malloc(sizeof(No));
        aux->chave = chave;
        aux->info = info;
        aux->prox = tabela[h];
        tabela[h] = aux;
    }
    return h;
}

No *busca(Hash tabela, int chave, int tam_chave, int tam_pos)
{
    int h = hash(chave, tam_chave, tam_pos);
    No *aux = tabela[h];

    while (aux != NULL)
    {
        if (aux->chave == chave)
            return aux;
        aux = aux->prox;
    }
    return NULL;
}

int remover(Hash tabela, int chave, int tam_chave, int tam_pos)
{
    No *aux = busca(tabela, chave, tam_chave, tam_pos);
    if (aux != NULL)
    {
        free(aux);
        aux = NULL;
        return 1;
    }
    return 0;
}

/*================================ Funções para análise dos dígitos ==================================*/
int hash(int chave, int tam_chave, int tam_pos)
{
    int posicao = 0;
    int aux[tam_chave];
    int mult = pow(10, (tam_pos - 1));
    dec_to_vetor(chave, aux, tam_chave);
    for (int i = 0; i < tam_pos; i++)
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

void contar_digitos(int tam_chave, int qtd_chave)
{
    for (int i = 0; i < tam_chave; i++)
        for (int j = 0; j < qtd_chave; j++)
            for (int k = 0; k < 10; k++)
                if (matriz_chaves[j][i] == k)
                    quantidade_digitos[i][k]++;
}

void calcular_dist(int tam_chave, int qtd_chave)
{
    for (int i = 0; i < tam_chave; i++)
        for (int j = 0; j < 10; j++)
            distribuicao_digitos[i] =
                distribuicao_digitos[i] +
                (quantidade_digitos[i][j] *
                 pow((j - (qtd_chave / 10)), 2));
}

void analisar_dist(int tam_chave, int tam_pos)
{
    float aux[tam_chave];
    copia_vetor(distribuicao_digitos, aux, tam_chave);
    insertion_sort(aux, tam_chave);
    for (int i = 0; i < tam_pos; i++)
        for (int j = 0; j < tam_chave; j++)
            if (aux[i] == distribuicao_digitos[j])
                posicao_digitos[i] = j;
}

void analisar_digitos(int *chaves, int tam_chave, int qtd_chave, int tam_pos)
{
    for (int i = 0; i < qtd_chave; i++)
        dec_to_vetor(chaves[i], matriz_chaves[i], tam_chave);

    contar_digitos(tam_chave, qtd_chave);
    calcular_dist(tam_chave, qtd_chave);
    analisar_dist(tam_chave, tam_pos);
}

void exibir_analise(int tam_chave, int qtd_chave)
{
    printf("\n== INFORMACOES SOBRE A ANALISE ==\n\n");
    for (int i = 0; i < qtd_chave; i++)
    {
        printf("Chave %2.d -> %d", i + 1, matriz_chaves[i][0]);
        for (int j = 1; j < tam_chave; j++)
            printf("%d", matriz_chaves[i][j]);
        printf("\n");
    }
    printf("=================================\n");
    for (int i = 0; i < tam_chave; ++i)
    {
        for (int j = 0; j < 10; j++)
            printf("Digito %d -> numero: %d -> qtd. = %d\n", i + 1, j, quantidade_digitos[i][j]);
        printf("=================================\n");
    }
    for (int i = 0; i < tam_chave; i++)
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

void limpar_analise(int tam_chave, int qtd_chave)
{
    for (int i = 0; i < tam_chave; i++)
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