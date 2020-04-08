#include <stdio.h>
#include <stdlib.h>
#define TAM 50

void construir(int *vetor, int n);
int inserir(int *vetor, int valor, int n, int tam);
int remover(int *vetor, int n);
void subir(int *vetor, int posicao);
void descer(int *vetor, int posicao, int n);
void imprimir(int *vetor, int n);

int vetor[TAM];
int n = 0;
int escolha_menu, numero, verificador;

int main()
{
    vetor[1] = 7;
    vetor[2] = 35;
    vetor[3] = 12;
    vetor[4] = 48;
    vetor[5] = 90;
    vetor[6] = 32;
    vetor[7] = 16;
    vetor[8] = 1;
    vetor[9] = 92;
    vetor[10] = 24;

    n = 10; //Guarda a quantidade de elementos na heap.
    construir(vetor, n);

    while (escolha_menu != -1)
    {
        system("clear");

        printf(" ___________________________________________ \n");
        printf("|################# HEAP-MAX ################|\n");
        printf("|                                           |\n");
        printf("|                [1] INSERIR                |\n");
        printf("|                [2] REMOVER                |\n");
        printf("|                [3] IMPRIMIR               |\n");
        printf("|                [4]  SAIR                  |\n");
        printf("|___________________________________________|\n");

        printf("\n");

        printf("Digíte a opcao desejada: ");
        scanf("%i", &escolha_menu);

        switch (escolha_menu)
        {
        case 1:
            printf("\nQual numero deseja inserir: ");
            scanf("%i", &numero);
            verificador = inserir(vetor, numero, n, TAM);
            if (verificador)
            {
                printf("Heap cheia! Pressione [ENTER] para retornar ao menu.");
                setbuf(stdin, NULL);
                getchar();
            }
            break;

        case 2:
            verificador = remover(vetor, n);
            if (verificador)
            {
                printf("Heap vazia! Pressione [ENTER] para retornar ao menu.");
                setbuf(stdin, NULL);
                getchar();
            }
            break;

        case 3:
            imprimir(vetor, n);
            printf("\nPressione [ENTER] para retornar ao menu.");
            setbuf(stdin, NULL);
            getchar();
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

void construir(int *vetor, int n)
{
    for (int i = (n / 2); i != 0; i--)
    {
        descer(vetor, i, n);
    }
}

int inserir(int *vetor, int valor, int n, int tam)
{
    if (n < tam - 1)
    {
        vetor[n + 1] = valor;
        n = n + 1;
        subir(vetor, n);
        return 0;
    }
    return 1;
}

int remover(int *vetor, int n)
{
    if (n != 0)
    {
        vetor[1] = vetor[n];
        n = n - 1;
        descer(vetor, 1, n);
        return 0;
    }
    return 1;
}

void subir(int *vetor, int posicao)
{
    int pai = (posicao / 2); //Pega o piso da divisão, pois a variável é do tipo inteiro.
    int auxiliar;
    if (pai >= 1)
    {
        if (vetor[pai] < vetor[posicao])
        {
            auxiliar = vetor[pai];
            vetor[pai] = vetor[posicao];
            vetor[posicao] = auxiliar;
            subir(vetor, pai);
        }
    }
}

void descer(int *vetor, int posicao, int n)
{
    int filho = 2 * posicao;
    int auxiliar;
    if (filho <= n) //Para que a verificação do filho direito seja possível sem estourar o tamanho do vetor.
    {
        if (filho < n)
        {
            if (vetor[filho] < vetor[filho + 1]) //Escolhe o filho de maior chave.
                filho++;
        }

        if (vetor[posicao] < vetor[filho]) //Verifica se o pai é menor que o filho para realizar a troca.
        {
            auxiliar = vetor[posicao];
            vetor[posicao] = vetor[filho];
            vetor[filho] = auxiliar;
            descer(vetor, filho, n);
        }
    }
}

void imprimir(int *vetor, int n)
{
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

