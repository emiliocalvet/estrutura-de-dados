#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

void Adicionar_inicio(int);
void Adicionar_meio(int, int);
void Adicionar_fim(int);
int Remover_inicio(void);
void Remover_meio(int);
int Remover_fim(void);
int Buscar(int);
void Alterar(int, int);
void Imprimir_lista(void);

int tam = 0;
int lista[20];
int n, p;

int main(void)
{
	setlocale(LC_ALL, "Portuguese");

	int opcao = 0;

	while (opcao != 6)
	{

		system("cls");

		printf("\n ________________________________");
		printf("\n|************* MENU *************|");
		printf("\n|                                |");
		printf("\n|         [1] Adicionar          |");
		printf("\n|         [2]  Remover           |");
		printf("\n|         [3]  Buscar            |");
		printf("\n|         [4]  Alterar           |");
		printf("\n|         [5] Imprimir           |");
		printf("\n|         [6]   Sair             |");
		printf("\n|________________________________|");

		printf("\n\nDigíte a opção desejada:");
		scanf("%d", &opcao);

		if (opcao < 1 || opcao > 6)
		{
			printf("\nOpção Inválida!\n\n");
			system("pause");
		}

		else
		{
			switch (opcao)
			{
			case 1:
				printf("\nDigíte o número: ");
				scanf("%d", &n);
				printf("\nDigíte a posição: ");
				scanf("%d", &p);
				Adicionar_meio(n, p);
				break;

			case 2:
				printf("\nDigíte a posição: ");
				scanf("%d", &p);
				Remover_meio(p);
				break;

			case 3:
				printf("\nDigíte o número: ");
				scanf("%d", &n);
				p = Buscar(n);

				if (p == -1)
					printf("\nNúmero não encontrado!\n");
				else
					printf("\nEncontrado na posição %d.\n", p);
				system("pause");
				break;

			case 4:
				printf("\nDigíte o número: ");
				scanf("%d", &n);
				printf("\nDigíte a posição: ");
				scanf("%d", &p);
				Alterar(n, p);
				break;

			case 5:
				Imprimir_lista();
				system("pause");
				break;
			}
		}
	}

	printf("\n\n");

	system("Pause");
	return 0;
}

void Adicionar_inicio(int num)
{

	int i;

	if (tam == 20)
		printf("\nLista cheia!");

	else if (tam == 0)
	{
		lista[0] = num;
		tam++;
	}

	else
	{
		for (i = tam; i > 0; i--)
			lista[i] = lista[i - 1];

		lista[0] = num;
		tam++;
	}
}

void Adicionar_meio(int num, int posicao)
{

	int i;

	if (posicao > tam)
	{
		printf("\nPosição Inválida! (max %d)\n", tam);
		system("pause");
	}

	else if (posicao == 0)
		Adicionar_inicio(num);

	else if (posicao == tam)
		Adicionar_fim(num);

	else
	{
		for (i = tam; i > posicao; i--)
			lista[i] = lista[i - 1];

		lista[posicao] = num;
		tam++;
	}
}

void Adicionar_fim(int num)
{

	if (tam < 20)
	{
		lista[tam] = num;
		tam++;
	}
	else
		printf("Lista cheia");
}

int Remover_inicio(void)
{

	int i;
	int retorno = lista[0];

	for (i = 0; i < tam; i++)
		lista[i] = lista[i + 1];

	tam--;
	return retorno;
}

void Remover_meio(int posicao)
{

	int i, retorno;

	if (posicao >= tam || posicao < 0)
	{
		printf("Posição inválida! [min 0|max %d]\n", tam - 1);
		system("pause");
	}

	else
	{
		retorno = lista[posicao];
		for (i = posicao; i < tam; i++)
			lista[i] = lista[i + 1];
		tam--;
		printf("\nNúmero %d removido.\n", retorno);
		system("pause");
	}
}

int Remover_fim(void)
{

	int retorno = lista[tam - 1];
	tam--;
	return retorno;
}

int Buscar(int elemento)
{

	int i;

	for (i = 0; i < tam; i++)
		if (lista[i] == elemento)
			return i;
	return -1;
}

void Alterar(int num, int posicao)
{

	if (tam == 0)
		printf("\nLista vazia!");
	else if (posicao > tam)
	{
		printf("\nPosição inválida! (max %d)\n", tam - 1);
		system("pause");
	}
	else
		lista[posicao] = num;
}

void Imprimir_lista(void)
{

	int i;

	printf("\n");

	for (i = 0; i < tam; i++)
		printf("%d ", lista[i]);

	printf("\n\n");
}
