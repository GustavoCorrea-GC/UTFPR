// Nome: Gustavo Luiz Andrade Correa
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Leitura.h"
#include "Grafo.h"

int main()
{
    clock_t t; 
    double time_taken; 
    char entrada;
    float Cidades[Num_City][2];
    readArchive(Cidades, "Leitura38.txt");
    //printf("ué %f\n", Cidades[0][1]);
    imprimirCidades(Cidades, Num_City);
    Grafo Simples;
    int i, j;
    int M[MAXI][MAXI];

    definir(&Simples);

    //Menu(&Simples);/*
    inserirTudo(&Simples, M, Cidades);
    //printf("saiu?\n");

    Ordena(&Simples);
    //imprimir(&Simples);
    //printf("entrou Guloso\n");
    //imprimir(&Simples);
    
    printf("Digite o inicio:\n");
    scanf("%c",&entrada);
    t = clock();
    Guloso(&Simples, entrada);
    t = clock() - t; 
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("O algoritmo guloso demorou %f segundos para executar \n", time_taken); 
    //printf("saiu do guloso\n");
    return 0;
}
