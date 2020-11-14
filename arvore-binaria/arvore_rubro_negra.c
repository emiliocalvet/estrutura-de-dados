//Implementação retirada do livro: ALgoritmos / Thomas H. CORMEN.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PRETO 0
#define VERMELHO 1

typedef struct No
{
    int chave;
    struct No *esquerda;
    struct No *direita;
    struct No *pai;
    int cor;
} No;

void rotacaoEsquerdaRn(No **, No **, No **);
void rotacaoDireitaRn(No **, No **, No **);
void inserirConsertoRn(No **, No **, No **);
void inserirRn(No **, No *, No **);
void transplanteRn(No **, No **, No **, No **);
No *arvoreMinima(No **, No **);
void removerRn(No **, No *, No **);
void removerConsertoRn(No **, No **, No **);
void contaNo(No *);
void preOrdem(No *);
void inOrdem(No *);
void posOrdem(No *);

//Funções para facilitar o debug.
void teste(int);
void teste2(No *);

int quantidadeNos;

int main()
{
    //No externo preto (NIL).
    No *externo = (No *)malloc(sizeof(No));
    externo->cor = PRETO;

    No *ptraiz, A, B, C, D;
    ptraiz = externo;

    A.chave = 12;
    A.cor = VERMELHO;

    B.chave = 3;
    B.cor = VERMELHO;

    C.chave = 15;
    C.cor = VERMELHO;

    D.chave = 2;
    D.cor = VERMELHO;   


    inserirRn(&ptraiz, &A, &externo);  
    inserirRn(&ptraiz, &B, &externo);  
    inserirRn(&ptraiz, &C, &externo);  
    inserirRn(&ptraiz, &D, &externo);  
    

    printf("\n========== Pre-Ordem ==========\n\n");
    preOrdem(ptraiz);

    quantidadeNos = 0;
    contaNo(ptraiz);
    printf("\nQuantidade de Nos: %d\n\nTeste Inserir 100 Nos:\n\n", quantidadeNos);

    return 0;
}

//Função de rotação para esquerda.
void rotacaoEsquerdaRn(No **ptraiz, No **alvo, No **externo)
{
    No *x = *alvo;
    No *y = x->direita;

    x->direita = y->esquerda;

    if (y->esquerda != *externo)
    {
        y->esquerda->pai = x;
    }
    y->pai = x->pai;
    if (x->pai == *externo)
    {
        *ptraiz = y;
    }
    else if (x == x->pai->esquerda)
    {
        x->pai->esquerda = y;
    }
    else
    {
        x->pai->direita = y;
    }
    y->esquerda = x;
    x->pai = y;
}

//Função de rotação para direita.
void rotacaoDireitaRn(No **ptraiz, No **alvo, No **externo)
{
    No *x = *alvo;
    No *y = x->esquerda;

    x->esquerda = y->direita;

    if (y->direita != *externo)
    {
        y->direita->pai = x;
    }
    y->pai = x->pai;
    if (x->pai == *externo)
    {
        *ptraiz = y;
    }
    else if (x == x->pai->direita)
    {
        x->pai->direita = y;
    }
    else
    {
        x->pai->direita = y;
    }
    y->direita = x;
    x->pai = y;
}

//Função rota para recolorir Nos e executar rotações.
void inserirConsertoRn(No **ptraiz, No **novo, No **externo)
{
    No *z = *novo;
    No *y = NULL;

    while (z->pai->cor == VERMELHO)
    {
        //Caso neto esquerdo.
        if (z->pai == z->pai->pai->esquerda)
        {
            y = z->pai->pai->direita;
            if (y->cor == VERMELHO)
            {
                z->pai->cor = PRETO;            //caso 1
                y->cor = PRETO;                 //caso 1
                z->pai->pai->cor = VERMELHO;    //caso 1
                z = z->pai->pai;                //caso 1
            }
            else
            {
                if (z == z->pai->direita)
                {
                    z = z->pai;                                         //caso 2
                    rotacaoEsquerdaRn(&(*ptraiz), &z, &(*externo));     //caso 2
                }
                z->pai->cor = PRETO;                                        //caso 3
                z->pai->pai->cor = VERMELHO;                                //caso 3
                rotacaoDireitaRn(&(*ptraiz), &z->pai->pai, &(*externo));    //caso 3
            }
        }
        //Caso neto direito.
        else
        {
            y = z->pai->pai->esquerda;
            if (y->cor == VERMELHO)
            {
                z->pai->cor = PRETO;            //caso 1
                y->cor = PRETO;                 //caso 1
                z->pai->pai->cor = VERMELHO;    //caso 1
                z = z->pai->pai;                //caso 1
            }
            else
            {
                if (z == z->pai->esquerda)
                {
                    z = z->pai;                                     //caso 2
                    rotacaoDireitaRn(&(*ptraiz), &z, &(*externo));  //caso 2
                }   
                z->pai->cor = PRETO;                                        //caso 3
                z->pai->pai->cor = VERMELHO;                                //caso 3
                rotacaoEsquerdaRn(&(*ptraiz), &z->pai->pai, &(*externo));   //caso 3
            }
        }
    }
    (*ptraiz)->cor = PRETO;
}

//Insere, pinta de vermelho e chama rota para preservar propriedades RN.
void inserirRn(No **ptraiz, No *novo, No **externo)
{
    No *x = *ptraiz;
    No *y = *externo;

    //Ponteiro para No ser inserido.
    No *z = novo;

    //Buscapara achar local de inserção.
    while (x != *externo)
    {
        y = x;
        if (z->chave < x->chave)
        {
            x = x->esquerda;
        }
        else
        {
            x = x->direita;
        }
    }
    z->pai = y;

    //Caso não tenha nenhum elemento na árvore.
    if (y == *externo)
    {
        *ptraiz = z;
    }

    //
    else if (z->chave < y->chave)
    {
        y->esquerda = z;
    }
    else
    {
        y->direita = z;
    }
    z->esquerda = *externo;
    z->direita = *externo;
    z->cor = VERMELHO;
    inserirConsertoRn(&(*ptraiz), &z, &(*externo));
}

//Função mover pai, utilizada nas rotações.
void transplanteRn(No **ptraiz, No **externo, No **origem, No **destino)
{
    No *u = *origem;
    No *v = *destino;

    //Verifica se u é raiz.
    if (u->pai == *externo)
    {
        *ptraiz = v;
    }
    else
    {
        if (u == u->pai->esquerda)
        {
            u->pai->esquerda = v;
        }
        else
        {
            u->pai->direita = v;
        }
    }
    v->pai = u->pai;
}

//Função que percorre a árvore pela esquerda até NIL.
No *arvoreMinima(No **externo, No **alvo)
{
    No *x = *alvo;
    while (x->esquerda != *externo)
    {
        x = x->esquerda;
    }
    return x;
}

//Função de remover com erros, bagunça ponteiros da RN.
void removerRn(No **ptraiz, No *alvo, No **externo)
{
    No *z = alvo;
    No *x = NULL;
    No *y = z;
    int y_cor_original = y->cor;

    if (z->esquerda == *externo)
    {
        x = z->direita;
        transplanteRn(&(*ptraiz), &(*externo), &z, &z->direita);
    }
    else if (z->direita == *externo)
    {
        x = z->esquerda;
        transplanteRn(&(*ptraiz), &(*externo), &z, &z->esquerda);
    }
    else //problema aqui!
    {
        y = arvoreMinima(&(*externo), &z->direita);
        y_cor_original = y->cor;
        x = y->direita;
        if (y->pai == z)
        {
            x->pai = y;
        }
        else
        {
            transplanteRn(&(*ptraiz), &(*externo), &y, &y->direita);
            y->direita = z->direita;
            y->direita->pai = y;
        }
        transplanteRn(&(*ptraiz), &(*externo), &z, &y);
        y->esquerda = z->esquerda;
        y->esquerda->pai = y;
        y->cor = z->cor;
    }
    if (y_cor_original == PRETO)
    {
        removerConsertoRn(&(*ptraiz), &(*externo), &x);
    }
}

//Função para preservar propriedades RN após remoção.
void removerConsertoRn(No **ptraiz, No **externo, No **alvo)
{
    No *x = *alvo;
    No *w = NULL;

    while (x != *ptraiz && x->cor == PRETO)
    {
        if (x == x->pai->esquerda)
        {
            w = x->pai->direita;
            if (w->cor == VERMELHO)
            {
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacaoEsquerdaRn(&(*ptraiz), &(*externo), &x->pai);
                w = x->pai->direita;
            }
            else
            {
                if (w->esquerda->cor == PRETO && w->direita->cor == PRETO)
                {
                    w->cor = VERMELHO;
                    x = x->pai;
                }
                else
                {
                    if (w->direita->cor == PRETO)
                    {
                        w->esquerda->cor == PRETO;
                        w->cor = VERMELHO;
                        rotacaoDireitaRn(&(*ptraiz), &(*externo), &w);
                        w = x->pai->direita;
                    }
                    w->cor = x->pai->cor;
                    x->pai->cor = PRETO;
                    w->direita->cor = PRETO;
                    rotacaoEsquerdaRn(&(*ptraiz), &(*externo), &x->pai);
                    x = *ptraiz;
                }
            }
        }
        else
        {
            w = x->pai->esquerda;
            if (w->cor == VERMELHO)
            {
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacaoDireitaRn(&(*ptraiz), &(*externo), &x->pai);
                w = x->pai->esquerda;
            }
            else
            {
                if (w->direita->cor == PRETO && w->esquerda->cor == PRETO)
                {
                    w->cor = VERMELHO;
                    x = x->pai;
                }
                else
                {
                    if (w->esquerda->cor == PRETO)
                    {
                        w->direita->cor == PRETO;
                        w->cor = VERMELHO;
                        rotacaoEsquerdaRn(&(*ptraiz), &(*externo), &w);
                        w = x->pai->esquerda;
                    }
                    w->cor = x->pai->cor;
                    x->pai->cor = PRETO;
                    w->esquerda->cor = PRETO;
                    rotacaoDireitaRn(&(*ptraiz), &(*externo), &x->pai);
                    x = *ptraiz;
                }
            }
        }
    }
    x->cor = PRETO;
}

//Recebe raiz e retorna quantidade de nós na RN.
void contaNo(No *aux)
{
    if (aux)
    {
        if (aux->chave != 0)
        {
            quantidadeNos++;
        }
        contaNo(aux->esquerda);
        contaNo(aux->direita);
    }
}

//Imprimir em pre-ordem.
void preOrdem(No *aux)
{
    if (aux)
    {
        if (aux->chave != 0)
        {
            printf("No: %d (cor:%d)\n", aux->chave, aux->cor);
        }
        preOrdem(aux->esquerda);
        preOrdem(aux->direita);
    }
}

//Imprimir em in-ordem.
void inOrdem(No *aux)
{
    if (aux)
    {
        inOrdem(aux->esquerda);
        if (aux->chave != 0)
        {
            printf("No: %d (cor:%d)\n", aux->chave, aux->cor);
        }
        inOrdem(aux->direita);
    }
}

//Imprimir em pos-ordem.
void posOrdem(No *aux)
{
    posOrdem(aux->direita);
    posOrdem(aux->esquerda);
    if (aux->chave != 0)
    {
        printf("No: %d (cor:%d)\n", aux->chave, aux->cor);
    }
}

//Funções para facilitar debug.
void teste(int num)
{
    printf("Passei aqui %i!\n", num);
    getchar();
}
void teste2(No *aux)
{
    printf("No: %d (cor:%d)\n", aux->chave, aux->cor);
    getchar();
}