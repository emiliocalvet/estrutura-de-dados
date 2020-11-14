#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int chave, bal;
    struct no *esq, *dir;
} No;

void inserir(int, No **, int *);
void rot_direita(No **, int *);
void rot_esquerda(No **, int *);
void pre_ordem(No *);
void in_ordem(No *);
void pos_ordem(No *);
void conta_no(No *);
int altura(No *);
No *buscar(No **, int);
void remover(No **ptraiz, int chave);

int qtd_no = 0;

int main()
{
    int h = 0;
    No *ptraiz = NULL;

    inserir(8, &ptraiz, &h);
    inserir(5, &ptraiz, &h);
    inserir(7, &ptraiz, &h);
    inserir(4, &ptraiz, &h);
    inserir(12, &ptraiz, &h);
    inserir(14, &ptraiz, &h);
    inserir(10, &ptraiz, &h);
    inserir(9, &ptraiz, &h);
    inserir(3, &ptraiz, &h);
    inserir(6, &ptraiz, &h);

    printf("\nPrint pre-ordem:\n");
    pre_ordem(ptraiz);

    printf("\nPrint in-ordem:\n");
    in_ordem(ptraiz);

    printf("\nPrint pos-ordem:\n");
    pos_ordem(ptraiz);

    printf("\nAltura: ");
    printf("%d", altura(ptraiz));

    conta_no(ptraiz);
    printf("\nQuantidade de Nos: %d\n\n", qtd_no);

    return 0;
}

void inserir(int x, No **ptraiz, int *h)
{
    No *pt = *ptraiz;

    if (!(*ptraiz))
    {
        *ptraiz = (No *)malloc(sizeof(No));
        (*ptraiz)->chave = x;
        (*ptraiz)->bal = 0;
        (*ptraiz)->dir = NULL;
        (*ptraiz)->esq = NULL;
        *h = 1;
    }
    else
    {
        if (x == pt->chave)
        {
            printf("Elemento já existe!\n");
            getchar();
        }
        else
        {
            if (x < pt->chave)
            {
                inserir(x, &pt->esq, h);
                if (*h)
                {
                    switch (pt->bal)
                    {
                    case 1:
                        pt->bal = 0;
                        *h = 0;
                        break;
                    case 0:
                        pt->bal = -1;
                        break;
                    case -1:
                        rot_direita(&pt, h);
                        *ptraiz = pt;
                        break;
                    }
                }
            }
            else
            {
                inserir(x, &pt->dir, h);
                if (*h)
                {
                    switch (pt->bal)
                    {
                    case -1:
                        pt->bal = 0;
                        *h = 1;
                        break;
                    case 0:
                        pt->bal = 1;
                        break;
                    case 1:
                        rot_esquerda(&pt, h);
                        *ptraiz = pt;
                        break;
                    }
                }
            }
        }
    }
}

void rot_direita(No **pt, int *h)
{
    No *ptv = NULL;
    No *ptu = (*pt)->esq;

    if (ptu->bal == -1)
    {
        (*pt)->esq = ptu->dir;
        ptu->dir = *pt;
        (*pt)->bal = 0;
        *pt = ptu;
    }
    else
    {
        ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = *pt;

        if (ptv->bal == -1)
            (*pt)->bal = 1;
        else
            (*pt)->bal = 0;

        if (ptv->bal == 1)
            ptu->bal = -1;
        else
            ptu->bal = 0;

        *pt = ptv;
    }
    (*pt)->bal = 0;
    *h = 0;
}

void rot_esquerda(No **pt, int *h)
{
    No *ptv = NULL;
    No *ptu = (*pt)->dir;

    if (ptu->bal == 1)
    {
        (*pt)->dir = ptu->esq;
        ptu->esq = *pt;
        (*pt)->bal = 0;
        (*pt) = ptu;
    }
    else
    {
        ptv = ptu->esq;
        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = *pt;

        if (ptv->bal == 1)
            (*pt)->bal = -1;

        else
            (*pt)->bal = 0;

        if (ptv->bal == -1)
            ptu->bal = 1;

        else
            ptu->bal = 0;

        *pt = ptv;
    }
    (*pt)->bal = 0;
    *h = 0;
}

void pre_ordem(No *aux)
{
    if (aux)
    {
        printf("No: %d(bal:%d)\n", aux->chave, aux->bal);
        pre_ordem(aux->esq);
        pre_ordem(aux->dir);
    }
}

void in_ordem(No *aux)
{
    if (aux)
    {
        in_ordem(aux->esq);
        printf("No: %d(bal:%d)\n", aux->chave, aux->bal);
        in_ordem(aux->dir);
    }
}

void pos_ordem(No *aux)
{
    if (aux)
    {
        pos_ordem(aux->esq);
        pos_ordem(aux->dir);
        printf("No: %d(bal:%d)\n", aux->chave, aux->bal);
    }
}

void conta_no(No *pt)
{
    if (pt)
    {
        qtd_no++;
        conta_no(pt->esq);
        conta_no(pt->dir);
    }
}

int altura(No *pt)
{
    if (!pt)
    {
        return 0;
    }

    int ae = altura(pt->esq);
    int ad = altura(pt->dir);

    return (ae > ad) ? ae + 1 : ad + 1;
}

No *buscar(No **ptraiz, int chave)
{
    No *aux = *ptraiz;

    while (aux && aux->chave != chave)
    {
        if (chave < aux->chave)
            aux = aux->esq;

        else
            aux = aux->dir;
    }
    return aux;
}

void remover(No **ptraiz, int chave)
{
    No *aux;

    aux = buscar(&(*ptraiz), chave);

    if (!aux)
        printf("Numero nao encontrado!\n");  
}