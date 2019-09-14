#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

void imprimirCidades(float vetor[][2], int quantcidade)
{
    int k;
    for (k = 0; k < quantcidade; k++)
    {
        printf("%f %f\n", vetor[k][0], vetor[k][1]);
    }
}

void readArchive(float cities[][2], char nome[])
{
    FILE *arq_palavras;
    arq_palavras = fopen(nome, "rt"); // abre o arquivo txt

    char ch;
    char v[10];
    int i = 0;
    int counter = 0;
    int j = 0;
    int k = 0;
    while ((ch = fgetc(arq_palavras)) != EOF)
    {
        if (ch != 10 && ch != 32)
        {
            if (counter > 8)
            {
                cities[i][k] = atof(v);

                counter = 0;
                if (k == 1)
                {
                    i++;
                }

                k = k == 0 ? 1 : 0;
            }
            else
            {
                v[counter] = ch;
                counter++;
            }
        }
        else
        {
            counter = 0;
        }
    }

    fclose(arq_palavras);
}