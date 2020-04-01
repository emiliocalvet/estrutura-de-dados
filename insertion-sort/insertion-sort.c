#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int *array, int tam);
void print_array(int *array, int tam);

int main()
{

    int array[] = {7, 5, 10, 3, 32, 65, 12, 13, 1, 9};

    insertion_sort(array, (sizeof(array)/sizeof(int)));
    print_array(array, (sizeof(array)/sizeof(int)));

    printf("\n\n");

    return 0;
}

void insertion_sort(int *array, int tam)
{
    int i, j, aux;

    for (i = 1; i < tam; i++)
    {
        j = i - 1;
        aux = array[i];
        while (array[j] > aux && j >= 0)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = aux;
    }
}

void print_array(int *array, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        printf("-%d", array[i]);
    }
}