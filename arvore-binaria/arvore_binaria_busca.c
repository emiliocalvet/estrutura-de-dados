#include <stdio.h>
#include <stdlib.h>

struct no
{
    int chave;
    struct no *esq, *dir;
};
typedef struct no No;

void preordem(No *pt);
void buscar(int x, No **pt, int *f);
void inserir(int x, No **ptraiz);

void remover(int x, No **ptraiz)
{
    No **pt = ptraiz;

    while ((*pt) != NULL && (*pt)->chave != x)
    {
        if (x < (*pt)->chave)
            pt = &(*pt)->esq;
        else
            pt = &(*pt)->dir;
    }

    if ((*pt) == NULL)
    {
        printf("elemento n encontrado");
    }
    else
    {
        No *aux = (*pt);
        if ((*pt)->esq == NULL)
        {
            (*pt) = (*pt)->dir;
        }
        else
        {
            if ((*pt)->dir == NULL)
            {
                (*pt) = (*pt)->esq;
            }
            else
            {
                No *s = (*pt)->dir;
                if (s->esq != NULL)
                {
                    No *PaiS = s;
                    while (s->esq != NULL)
                    {
                        PaiS = s;
                        s = s->esq;
                    }
                    PaiS->esq = s->dir;
                    s->dir = (*pt)->dir;
                }
                s->esq = (*pt)->esq;
                (*pt) = s;
            }
        }
        free(aux);
    }
}

int main()
{
    int f = -1;
    No *ptraiz = NULL, A, B, C, *pt = NULL;

    A.chave = 10;
    B.chave = 5;
    C.chave = 15;

    ptraiz = &A;
    A.esq = &B;
    A.dir = &C;
    B.dir = B.esq = C.dir = C.esq = NULL;

    pt = ptraiz;

    buscar(10, &pt, &f);
    printf("\n%d ", f);
    if (pt != NULL)
        printf("%d ", pt->chave);

    pt = ptraiz;
    buscar(14, &pt, &f);
    printf("\n%d ", f);
    if (pt != NULL)
        printf("%d ", pt->chave);
    pt = ptraiz;
    buscar(6, &pt, &f);
    printf("\n%d ", f);
    if (pt != NULL)
        printf("%d ", pt->chave);

    ptraiz = NULL;

    //printf("%d %d %d\n", ptraiz->chave,ptraiz->esq->chave,ptraiz->dir->chave);
    inserir(10, &ptraiz);
    inserir(5, &ptraiz);
    inserir(15, &ptraiz);
    inserir(13, &ptraiz);
    inserir(14, &ptraiz);
    inserir(20, &ptraiz);
    if (ptraiz != NULL)
        preordem(ptraiz);

        remover(10,&ptraiz);
        printf("\n\n");
    if (ptraiz != NULL)
        preordem(ptraiz);
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
                    *f = 2;

                else
                {
                    (*pt) = (*pt)->esq;
                    buscar(x, pt, f);
                }
            }
            else
            {
                if ((*pt)->dir == NULL)
                    *f = 3;
                else
                {
                    (*pt) = (*pt)->dir;
                    buscar(x, pt, f);
                }
            }
        }
    }
}

void inserir(int x, No **ptraiz)
{
    int f = -1;

    No *pt = *ptraiz;
    buscar(x, &pt, &f);

    if (f == 1)
    {
        printf("Elemento já  existe");
    }
    else
    {
        No *novo = malloc(sizeof(No));
        novo->chave = x;
        novo->esq = novo->dir = NULL;

        switch (f)
        {
        case 0:
            *ptraiz = novo;
            break;
        case 2:
            pt->esq = novo;
            break;
        case 3:
            pt->dir = novo;
            break;
        default:
            printf("inserção invalida");
        }
    }
}