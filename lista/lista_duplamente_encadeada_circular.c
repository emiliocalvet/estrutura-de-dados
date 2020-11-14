#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
	int valor;
	struct no *prox;
	struct no *ant;
} No;

No *inicio;
int contador = 0;

void adicionar_inicio(int valor)
{
	No *novo = (No *)malloc(sizeof(No));
	novo->valor = valor;

	if (contador == 0)
	{
		inicio = novo;
		inicio->prox = inicio;
		inicio->ant = inicio;
	}
	else
	{
		novo->prox = inicio;
		inicio->ant->prox = novo;
		novo->ant = inicio->ant;
		inicio->ant = novo;
		inicio = novo;
	}
	contador++;
}

void adicionar_fim(int valor)
{
	if (contador == 0)
		adicionar_inicio(valor);
	else
	{
		No *novo = (No *)malloc(sizeof(No));
		novo->valor = valor;

		novo->prox = inicio;
		novo->ant = inicio->ant;
		novo->ant->prox = novo;
		inicio->ant = novo;
		contador++;
	}
}

void adicionar_meio(int posicao, int valor)
{
	if (posicao == 0 || posicao > contador)
		printf("Posicao invalida!");

	else if (posicao == 1)
		adicionar_inicio(valor);

	else if (posicao == contador)
		adicionar_fim(valor);

	else
	{
		int i;
		No *aux;
		aux = inicio;
		No *novo = (No *)malloc(sizeof(No));
		novo->valor = valor;

		for (i = 0; i < posicao - 1; i++)
		{
			aux = aux->prox;
		}

		novo->prox = aux;
		aux->ant->prox = novo;
		novo->ant = aux->ant;
		aux->ant = novo;
		contador++;
	}
}

void remover_inicio()
{
	No *aux;
	aux = inicio;
	inicio->ant->prox = inicio->prox;
	inicio->prox->ant = inicio->ant;
	inicio = inicio->prox;
	free(aux);
	contador--;
}

void remover_meio(int posicao)
{
	int i;
	No *aux;
	aux = inicio;

	if (posicao == 1)
		remover_inicio();

	else if (posicao < contador)
	{
		for (i = 0; i < posicao - 1; i++)
		{
			aux = aux->prox;
		}

		aux->prox->ant = aux->ant;
		aux->ant->prox = aux->prox;
		free(aux);
		contador--;
	}
	else
		printf("\nPosicao invalida!\n");
}

void remover_fim()
{
	No *aux;
	aux = inicio->ant;
	aux->prox->ant = aux->ant;
	aux->ant->prox = aux->prox;
	free(aux);
	contador--;
}

void imprimir()
{
	int i;
	No *aux;
	aux = inicio;

	for (i = 0; i < contador; i++)
	{
		printf("-%i", aux->valor);
		aux = aux->prox;
	}
}

int main()
{
	adicionar_inicio(18);
	adicionar_inicio(90);
	adicionar_inicio(72);
	adicionar_inicio(40);
	adicionar_inicio(24);
	adicionar_inicio(14);
	adicionar_inicio(12);
	adicionar_fim(35);
	adicionar_meio(3, 15);
	adicionar_meio(1, 9);
	remover_inicio();
	remover_fim();
	remover_meio(3);
	imprimir();

	getchar();
	return 0;
}