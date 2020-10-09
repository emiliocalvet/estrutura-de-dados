#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int n, fb;
    struct no *esq, *dir, *pai;
} No;

No *raiz = NULL;

int qtd_no;

void menu();
void insere();
void exibir_pre(No *);
void exibir_pos(No *);
void exibir_ordenado(No *);
void exibir_niveis(No *);
void exibir_niveis_b(No *, int, int);
void remove_p();
void remover(No *);
void conta_no(No *aux);
No *menor_dir(No *);
No *buscar(int);
void limpar_arvore(No *);
int altura(No *);
No *balanceia(No *);
No *rot_direira(No *);
No *rot_esquerda(No *);

int main()
{
    No *b;
    int op, n;

    while (1)
    {
        menu();

        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1:
            insere();
            break;

        case 2:
            remove_p();
            printf("Pronto!\n");
            getchar();
            break;

        case 3:
            printf("Digite o numero a procurar: ");
            scanf("%d", &n);
            getchar();
            b = buscar(n);

            if (b)
            {
                printf("Elemento encontrado: %d\n", b->n);
            }
            else
            {
                printf("Elemento nao encontrado!\n");
            }
            b = NULL;
            getchar();
            break;

        case 4:
            exibir_pre(raiz);
            printf("\nPronto!\n");
            getchar();
            break;

        case 5:
            exibir_pos(raiz);
            printf("\nPronto!\n");
            getchar();
            break;

        case 6:
            exibir_ordenado(raiz);
            printf("\nPronto!\n");
            getchar();
            break;

        case 7:
            exibir_niveis(raiz);
            printf("\nPronto!\n");
            getchar();
            break;

        case 8:
            printf("Altura da arvore: %d\n", altura(raiz));
            getchar();
            break;

        case 9:
            if (raiz)
            {
                limpar_arvore(raiz);
                printf("Arvore limpa!\n");
            }
            else
            {
                printf("A arvore ja estava limpa!\n");
            }
            getchar();
            break;

        case 10:
            if (raiz)
            {
                limpar_arvore(raiz);
            }
            exit(0);
            break;

        case 11:
            conta_no(raiz);
            printf("%d nos!\n", qtd_no);
            getchar();
            qtd_no = 0;
            break;

        default:
            printf("Opcao incorreta!\n");
            getchar();
            break;
        }
    }
}

void menu()
{
    system("clear");

    printf("###############################################\n");
    printf("#----------[Arvore Binaria de Busca]----------#\n");
    printf("###############################################\n\n");

    printf("1 - Inserir\n");
    printf("2 - Remover\n");
    printf("3 - Buscar\n");
    printf("4 - Exibir - Pre Ordem\n");
    printf("5 - Exibir - Pos Ordem\n");
    printf("6 - Exibir - Ordenado\n");
    printf("7 - Exibir por niveis\n");
    printf("8 - Altura da arvore\n");
    printf("9 - Limpar Arvore\n");
    printf("11 - Conta No\n");
    printf("10 - Sair\n\n");

    printf("Digite uma opcao: ");
}

void insere()
{
    No *aux1 = NULL, *aux2 = NULL;
    int n;

    printf("Digite o numero a inserir: ");
    scanf("%d", &n);
    getchar();

    if (!raiz)
    {
        raiz = (No *)malloc(sizeof(No));

        if (!raiz)
        {
            printf("Erro ao alocar =(\n");
            exit(1);
        }

        raiz->n = n;
        raiz->esq = NULL;
        raiz->dir = NULL;
        raiz->pai = NULL;

        raiz->fb = 0;
    }

    else
    {
        aux1 = raiz;
        aux2 = aux1;

        while (aux2)
        {
            if (n < aux2->n)
            {
                aux2 = aux2->esq;

                if (!aux2)
                {
                    aux1->esq = (No *)malloc(sizeof(No));

                    if (!aux1->esq)
                    {
                        printf("Erro ao alocar =(\n");
                        exit(1);
                    }

                    aux2 = aux1->esq;

                    aux2->esq = NULL;
                    aux2->dir = NULL;
                    aux2->pai = aux1;
                    aux2->n = n;
                    break;
                }
                else
                {
                    aux1 = aux2;
                }
            }

            else
            {
                aux2 = aux2->dir;

                if (!aux2)
                {
                    aux1->dir = (No *)malloc(sizeof(No));

                    if (!aux1->dir)
                    {
                        printf("Erro ao alocar =(\n");
                        exit(1);
                    }

                    aux2 = aux1->dir;

                    aux2->esq = NULL;
                    aux2->dir = NULL;
                    aux2->pai = aux1;
                    aux2->n = n;
                    break;
                }

                else
                {
                    aux1 = aux2;
                }
            }
        }
    }

    printf("Elemento Inserido!\n");
    getchar();

    if (aux2)
    {
        while (aux2)
        {
            aux2->fb = altura(aux2->dir) - altura(aux2->esq);

            if (aux2->fb > 1 || aux2->fb < -1)
            {
                aux2 = balanceia(aux2);
            }

            aux2 = aux2->pai;
        }
    }
}

void exibir_pre(No *aux)
{
    if (!raiz)
    {
        printf("Arvore vazia!");
        return;
    }

    if (aux)
    {
        printf("%d(%d) ", aux->n, aux->fb);
        exibir_pre(aux->esq);
        exibir_pre(aux->dir);
    }
}

void exibir_pos(No *aux)
{
    if (!raiz)
    {
        printf("Arvore vazia!");
        return;
    }

    if (aux)
    {
        exibir_pos(aux->esq);
        exibir_pos(aux->dir);
        printf("%d(%d) ", aux->n, aux->fb);
    }
}

void exibir_ordenado(No *aux)
{
    if (!raiz)
    {
        printf("Arvore vazia!");
        return;
    }

    if (aux)
    {
        exibir_ordenado(aux->esq);
        printf("%d(%d) ", aux->n, aux->fb);
        exibir_ordenado(aux->dir);
    }
}

void remove_p()
{
    No *aux;
    int n;

    printf("Digite o numero que deseja remover: ");
    scanf("%d", &n);
    getchar();

    aux = buscar(n);

    if (aux)
    {
        remover(aux);
    }

    else
    {
        printf("O numero nao existe na arvore!\n");
    }
}

void remover(No *aux)
{
    No *aux2, *salva = aux->pai;

    if (aux != raiz)
    {
        if (!aux->esq && !aux->dir)
        {
            if (aux->n < aux->pai->n)
            {
                aux->pai->esq = NULL;
            }
            else
            {
                aux->pai->dir = NULL;
            }

            free(aux);
        }

        else if (!aux->dir)
        {
            if (aux->n < aux->pai->n)
            {
                aux->pai->esq = aux->esq;
            }
            else
            {
                aux->pai->dir = aux->esq;
            }
            aux->esq->pai = aux->pai;
            free(aux);
        }

        else if (!aux->esq)
        {
            if (aux->n < aux->pai->n)
            {
                aux->pai->esq = aux->dir;
            }
            else
            {
                aux->pai->dir = aux->dir;
            }
            aux->dir->pai = aux->pai;
            free(aux);
        }

        else
        {
            aux2 = menor_dir(aux->dir);
            aux->n = aux2->n;

            remover(aux2);
        }
    }

    else
    {
        if (!aux->esq && !aux->dir)
        {
            free(aux);
            raiz = NULL;
        }

        else if (!aux->dir)
        {
            aux->esq->pai = NULL;
            raiz = aux->esq;
            free(aux);
        }

        else if (!aux->esq)
        {
            aux->dir->pai = NULL;
            raiz = aux->dir;
            free(aux);
        }

        else
        {
            aux2 = menor_dir(aux->dir);
            aux->n = aux2->n;

            remover(aux2);
        }
    }

    if (salva)
    {
        while (salva)
        {
            salva->fb = altura(salva->dir) - altura(salva->esq);

            if (salva->fb > 1 || salva->fb < -1)
            {
                salva = balanceia(salva);
            }

            salva = salva->pai;
        }
    }
}

No *menor_dir(No *aux)
{
    while (aux->esq)
    {
        aux = aux->esq;
    }

    return aux;
}

No *buscar(int n)
{
    No *aux;

    aux = raiz;

    while (aux && aux->n != n)
    {
        if (n < aux->n)
        {
            aux = aux->esq;
        }

        else
        {
            aux = aux->dir;
        }
    }

    return aux;
}

void limpar_arvore(No *aux)
{
    if (aux->esq)
    {
        limpar_arvore(aux->esq);
    }

    if (aux->dir)
    {
        limpar_arvore(aux->dir);
    }

    free(aux);
    raiz = NULL;
}

int altura(No *aux)
{
    if (!aux)
    {
        return 0;
    }

    int ae = altura(aux->esq);
    int ad = altura(aux->dir);

    return (ae > ad) ? ae + 1 : ad + 1;
}

No *rot_direira(No *aux)
{
    No *esq = aux->esq;

    aux->esq = esq->dir;
    esq->dir = aux;

    if (aux->esq)
    {
        aux->esq->pai = aux;
    }

    esq->pai = aux->pai;
    aux->pai = esq;

    if (aux == raiz)
    {
        raiz = esq;
    }

    if (esq->pai)
    {
        if (esq->n < esq->pai->n)
        {
            esq->pai->esq = esq;
        }
        else
        {
            esq->pai->dir = esq;
        }
    }

    esq->fb = altura(esq->dir) - altura(esq->esq);
    aux->fb = altura(aux->dir) - altura(aux->esq);

    return esq;
}

No *rot_esquerda(No *aux)
{
    No *dir = aux->dir;

    aux->dir = dir->esq;
    dir->esq = aux;

    if (aux->dir)
    {
        aux->dir->pai = aux;
    }

    dir->pai = aux->pai;
    aux->pai = dir;

    if (aux == raiz)
    {
        raiz = dir;
    }

    if (dir->pai)
    {
        if (dir->n < dir->pai->n)
        {
            dir->pai->esq = dir;
        }
        else
        {
            dir->pai->dir = dir;
        }
    }

    dir->fb = altura(dir->dir) - altura(dir->esq);
    aux->fb = altura(aux->dir) - altura(aux->esq);
    return dir;
}

No *balanceia(No *aux)
{
    if (aux->fb < -1)
    {
        if (aux->esq->fb > 0)
        {
            aux->esq = rot_esquerda(aux->esq);
        }

        aux = rot_direira(aux);
    }

    else if (aux->fb > 1)
    {
        if (aux->dir->fb < 0)
        {
            aux->dir = rot_direira(aux->dir);
        }

        aux = rot_esquerda(aux);
    }

    return aux;
}

void exibir_niveis(No *aux)
{
    int i;

    for (i = 0; i <= altura(raiz); i++)
    {
        printf("Nivel %d\n", i);
        exibir_niveis_b(raiz, i, 0);
        printf("\n\n");
    }
}

void exibir_niveis_b(No *aux, int atual, int cont)
{
    if (!raiz)
    {
        printf("A arvore esta vazia!");
        getchar();
        return;
    }

    if (aux)
    {
        exibir_niveis_b(aux->esq, atual, cont + 1);

        if (atual == cont)
        {
            printf("%d ", aux->n);
        }

        exibir_niveis_b(aux->dir, atual, cont + 1);
    }
}

void conta_no(No *aux)
{
    if (aux)
    {
        qtd_no++;
        conta_no(aux->esq);
        conta_no(aux->dir);
    }
}