#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int chave, bal;
    struct no *esq, *dir;
} No;

inserir(int x, No *pt, int h);
rot_direita(No *pt, int h);
rot_esquerda(No *pt, int h);

int qtd_no = 0;

int main()
{
    return 0;
}

rot_direita(No *pt, int h) {
    No *ptv = NULL;
    No *ptu = pt->esq;

    if (ptu->bal == -1)
    {
        pt->esq = ptu->dir;
        ptu->dir = pt;
        pt = ptu;
        pt->bal = pt->dir->bal = 0;
    }
    else
    {
        ptv = ptu->dir;
        ptu->dir = ptv->esq;
        pt->esq = ptv->dir;
        ptv->esq = ptu;
        ptv->dir = pt;
        pt = ptv;
        if (ptv->bal == -1)
        {
            ptu->bal = 0;
            pt->dir->bal = 1;
        }
        else
        {
            ptu->bal = -1;
            pt->dir->bal = 0;
        }
    }
}

rot_esquerda(No *pt, int h) {}

inserir(int x, No *pt, int h)
{
    if (pt == NULL)
    {
        pt = (No *)malloc(sizeof(No));
        pt->chave = x;
        pt->dir = NULL;
        pt->esq = NULL;
        h = 0;
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
                inserir(x, pt->esq, h);
                if (h)
                {
                    switch (pt->bal)
                    {
                    case 1:
                        pt->bal = 0;
                        h = 1;
                        break;
                    case 0:
                        pt->bal = -1;
                        break;
                    case -1:
                        rot_direita(pt, h);
                        break;

                    default:
                        printf("Erro!");
                        getchar();
                        break;
                    }
                }
            }
            else
            {
                inserir(x, pt->dir, h);
                if (h)
                {
                    switch (pt->bal)
                    {
                    case -1:
                        pt->bal = 0;
                        h = 1;
                        break;
                    case 0:
                        pt->bal = 1;
                        break;
                    case 1:
                        rot_esquerda(pt, h);
                        break;

                    default:
                        printf("Erro!");
                        getchar();
                        break;
                    }
                }
            }
        }
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