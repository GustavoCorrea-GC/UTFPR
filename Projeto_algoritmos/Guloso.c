// Nome: Gustavo Luiz Andrade Correa
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include "Leitura.h"
#include "Grafo.h"



int main (){
float Cidades[Num_City][2];
readArchive(Cidades,"leitura.txt");
//printf("ué %f\n", Cidades[0][1]);
imprimirCidades(Cidades);
Grafo Simples;
int i,j;
int M[MAXI][MAXI];

definir(&Simples);

//Menu(&Simples);/*
inserirTudo(&Simples,M,Cidades);
printf("saiu?");

//Ordena(&Simples);
imprimir(&Simples);
printf("entrou Guloso\n");
//imprimir(&Simples);

Guloso(&Simples,'A');
return 0;
}
