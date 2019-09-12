// Nome: Gustavo Luiz Andrade Correa
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Leitura.h"
#include "Grafo.h"

int CalculaDist(float a,float b){

}

void inserirTudo(Grafo *G, int M[][MAXI],int d[][MAXI]){
    inserir_vertice(G, (int)'A',M);
    inserir_vertice(G, (int)'B',M);
    inserir_aresta(G, (int)'a',(int)'B',CalculaDist(d[0][0]),M);
}


int main (){
float Cidades[29][2];
readArchive(Cidades,"leitura.txt");
//printf("ué %f\n", Cidades[0][1]);
imprimirCidades(Cidades);
Grafo Simples;
int i,j;
int M[MAXI][MAXI];

definir(&Simples);

//Menu(&Simples);/*
inserirTudo(&Simples,M);


Ordena(&Simples);
imprimir(&Simples);

return 0;
}
