#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
	int valor;
	struct no *prox;
	struct no *ant;
} No;

No *inicio;
No *fim;
int contador = 0;

void adicionar_inicio(int valor)
{
	No *novo = (No *)malloc(sizeof(No));
	novo->valor = valor;

	if (contador == 0)
	{
		inicio = novo;
		fim = novo;
	}
	else
	{
		novo->prox = inicio;
		inicio->ant = novo;
		inicio = novo;
	}
	contador++;
}

void adicionar_fim(int valor)
{
	No *novo = (No *)malloc(sizeof(No));
	novo->valor = valor;

	fim->prox = novo;
	novo->ant = fim;
	fim = novo;
	contador++;
}

void adicionar_meio(int posicao, int valor)
{
	if (posicao == 0)
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

		for (i = 0; i < posicao - 1; i++)
		{
			aux = aux->prox;
		}
		novo->prox = aux->prox;
		aux->prox->ant = novo;
		novo->ant = aux;
		aux->prox = novo;
		contador++;
	}
}

void remover_inicio()
{
	inicio = inicio->prox;
	free(inicio->ant);
	contador--;
}

void remover_fim()
{
	fim = fim->ant;
	free(fim->prox);
	contador--;
}

void remover_meio(int posicao)
{
	if (posicao == 0)
	{
		remover_inicio();
	}
	else if (posicao == contador - 1)
	{
		remover_fim();
	}
	else
	{
		int i;
		No *aux;
		aux = inicio;

		for (i = 0; i < posicao; i++)
		{
			aux = aux->prox;
		}
		aux->ant->prox = aux->prox;
		aux->prox->ant = aux->ant;
		free(aux);
		contador--;
	}
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
	adicionar_meio(0, 9);
	remover_inicio();
	remover_fim();
	remover_meio(3);
	imprimir();

	getchar();
	return 0;
}