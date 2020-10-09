#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int chave;
    struct no *esq, *dir;
} No;

void preordem(No *pt);
void buscar(int x, No **pt, int *f);

int main()
{
    int f = -1;
    No *ptraiz = NULL, *pt = NULL, A, B, C;

    A.chave = 10;
    B.chave = 5;
    C.chave = 15;

    ptraiz = &A;
    A.esq = &B;
    A.dir = &C;
    B.dir = B.esq = NULL;
    C.dir = C.esq = NULL;

    printf("%d ", ptraiz->chave);
    printf("%d ", ptraiz->esq->chave);
    printf("%d ", ptraiz->dir->chave);

    return 0;
}

void preordem(No *pt)
{
    printf("%d ", pt->chave);
    if (pt->esq != NULL)
        preordem(pt->esq);
    if (pt->dir != NULL)
        preordem(pt->dir);
}

void buscar(int x, No **pt, int *f)
{
    if ((*pt) == NULL)
    {
        *f = 0;
    }
    else
    {
        if (x == (*pt)->chave)
        {
            *f = 1;
        }
        else
        {
            if (x < (*pt)->chave)
            {
                if ((*pt)->esq == NULL)
                {
                    *f = 2;
                }
                else
                {
                    (*pt) = (*pt)->esq;
                    buscar(x, pt, f);
                }
            }
            else
            {
                if ((*pt)->dir == NULL)
                {
                    *f = 3;
                }
                else
                {
                    (*pt) = (*pt)->dir;
                    buscar(x, pt, f);
                }
            }
        }
    }
}