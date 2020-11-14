#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
	int valor;
	struct no *prox;
} No;

void adicionar_inicio(int x);
void adicionar_fim(int x);
void adicionar_meio(int x, int y);
void remover_inicio();
void remover_fim();
void remover_meio();
void imprimir();

No *inicio;
int contador = 0;

int main()
{
	int escolha_menu, numero, posicao;

	while (escolha_menu != -1)
	{
		system("clear");

		printf(" ___________________________________________ \n");
		printf("|############## LISTA-ENCADEADA ############|\n");
		printf("|                                           |\n");
		printf("|             [1] INSERIR INICIO            |\n");
		printf("|             [2] INSERIR POSICAO           |\n");
		printf("|             [3] INSERIR FIM               |\n");
		printf("|             [4] REMOVER INICIO            |\n");
		printf("|             [5] REMOVER POSICAO           |\n");
		printf("|             [6] REMOVER FIM               |\n");
		printf("|             [7] IMPRIMIR                  |\n");
		printf("|             [0] SAIR                      |\n");
		printf("|___________________________________________|\n");

		printf("\n");

		printf("Digíte a opcao desejada: ");
		scanf("%i", &escolha_menu);

		switch (escolha_menu)
		{
		case 1:
			printf("\nValor: ");
			scanf("%i", &numero);
			adicionar_inicio(numero);
			break;

		case 2:
			printf("\nValor: ");
			scanf("%i", &numero);
			printf("\nPosicao: ");
			scanf("%i", &posicao);
			adicionar_meio(numero, posicao);
			break;

		case 3:
			printf("\nValor: ");
			scanf("%i", &numero);
			adicionar_fim(numero);
			break;

		case 4:
			remover_inicio();
			break;

		case 5:
			printf("\nPosicao: ");
			scanf("%i", &posicao);
			remover_meio(posicao);
			break;

		case 6:
			remover_fim();
			break;

		case 7:
			printf("\n");
			imprimir();
			setbuf(stdin, NULL);
			getchar();
			break;

		case 0:
			escolha_menu = -1;
			printf("Bye!\n\n");
			break;

		default:
			printf("\nOpção incorreta, pressione [ENTER] e tente novamente!");
			escolha_menu = -2;
			setbuf(stdin, NULL);
			getchar();
			break;
		}
	}
	return 0;
}

void adicionar_inicio(int valor)
{
	No *novo = (No *)malloc(sizeof(No));
	novo->valor = valor;

	if (contador == 0)
	{
		inicio = novo;
	}
	else
	{
		novo->prox = inicio;
		inicio = novo;
	}
	contador++;
}

void adicionar_fim(int valor)
{
	if (contador == 0)
	{
		adicionar_inicio(valor);
	}
	else
	{
		int i;
		No *aux;
		aux = inicio;
		No *novo = (No *)malloc(sizeof(No));
		novo->valor = valor;

		for (i = 0; i < contador - 1; i++)
		{
			aux = aux->prox;
		}
		aux->prox = novo;
		contador++;
	}
}

void adicionar_meio(int valor, int posicao)
{
	if (posicao == 1)
	{
		adicionar_inicio(valor);
	}
	else if (posicao == contador)
	{
		adicionar_fim(valor);
	}
	else
	{
		int i;
		No *aux;
		aux = inicio;
		No *novo = (No *)malloc(sizeof(No));
		novo->valor = valor;

		for (i = 1; i < posicao - 1; i++)
		{
			aux = aux->prox;
		}
		novo->prox = aux->prox;
		aux->prox = novo;
		contador++;
	}
}

void remover_inicio()
{
	No *aux;
	aux = inicio;
	inicio = inicio->prox;
	free(aux);
	contador--;
}

void remover_fim()
{
	if (contador != 0)
	{
		if (contador == 1)
			remover_inicio();
		else
		{
			No *aux;
			aux = inicio;

			for (int i = 1; i < contador - 1; i++)
			{
				aux = aux->prox;
			}
			free(aux->prox);
			aux->prox = NULL;
		}
		contador--;
	}
}

void remover_meio(int posicao)
{
	if (posicao == 1)
	{
		remover_inicio();
	}
	else if (posicao == contador)
	{
		remover_fim();
	}
	else
	{
		No *aux = inicio;
		No *ant;

		for (int i = 1; i < posicao; i++)
		{
			ant = aux;
			aux = aux->prox;
		}
		ant->prox = aux->prox;
		aux->prox = NULL;
		free(aux);
		contador--;
	}
}

void imprimir()
{
	No *aux;
	aux = inicio;

	while (aux)
	{
		printf("%i -> ", aux->valor);
		aux = aux->prox;
	}
	printf("NULL");
}