#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int buffer_bin[10];

int *dec_to_bin(int dec)
{
    for (int i = 9; i >= 0; i--)
    {
        if (dec % 2 == 0)
            buffer_bin[i] = 0;
        else
            buffer_bin[i] = 1;
        dec = dec / 2;
    }
    return buffer_bin;
}

int bin_to_dec(int *bin)
{
    int dec = 0;

    for (int i = 4; i >= 0; i--)
    {
        dec = dec + (bin[i] * pow(2, (4 - i)));
    }

    return dec;
}

int and (int bit1, int bit2)
{
    return bit1 & bit2;
}

int or (int bit1, int bit2)
{
    return bit1 | bit2;
}

int xor (int bit1, int bit2)
{
    return bit1 ^ bit2;
}

int hash(int chave) //Método da dobra.
{
    int *chave_bin = dec_to_bin(chave);
    int pos_bin[4];

    for (int i = 0; i < 5; i++)
    {
        pos_bin[i] = xor(chave_bin[i], chave_bin[i + 5]);
    }

    int posicao = bin_to_dec(pos_bin);
    return posicao;
}

int main()
{
    int retorno = hash(46);
    printf("%d\n", retorno);

    getchar();
    return 0;
}
