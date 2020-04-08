#include <stdio.h>
#include <stdlib.h>
#define TAM 50

void construir(int *vetor, int n);
void heapSort(int *vetor, int n);
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

    while (escolha_menu != -1)
    {
        system("clear");

        printf(" ________________________________ \n");
        printf("|######## HEAP-SORT_MIN ########|\n");
        printf("|                               |\n");
        printf("|         [1] IMPRIMIR          |\n");
        printf("|         [2] ORDENAR           |\n");
        printf("|         [3] SAIR              |\n");
        printf("|_______________________________|\n");

        printf("\n");

        printf("Digíte a opcao desejada: ");
        scanf("%i", &escolha_menu);

        switch (escolha_menu)
        {
        case 1:
            imprimir(vetor, n);
            printf("\nPressione [ENTER] para retornar ao menu!");
            setbuf(stdin, NULL);
            getchar();
            break;

        case 2:
            heapSort(vetor, n);
            break;

        case 3:
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

void heapSort(int *vetor, int n)
{
    int i = n, aux;
    construir(vetor, n);
    while (i > 1)
    {
        aux = vetor[i];
        vetor[i] = vetor[1];
        vetor[1] = aux;
        i--;
        descer(vetor, 1, i);
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
            if (vetor[filho] > vetor[filho + 1]) //Escolhe o filho de maior chave.
                filho++;
        }

        if (vetor[posicao] > vetor[filho]) //Verifica se o pai é menor que o filho para realizar a troca.
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
