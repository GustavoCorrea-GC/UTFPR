// Nome: Gustavo Luiz Andrade Correa
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include "Leitura.h"
#include "Grafo.h"

#define Num_City 29

/*int CalculaDist(float x1,float y1,float x2,float y2){
    double xd,yd;
    int dij;
    xd = x1 - x2;
    yd = y1 - y2;
    dij = nint( sqrt( xd*xd + yd*yd) );
    return dij;
}*/
int CalculaDist(float x1,float y1,float x2,float y2){
    double xd,yd;
    int dij;
    xd = x1 - x2;
    yd = y1 - y2;
    dij = nearbyint( sqrt( xd*xd + yd*yd) );
    return dij;
}


void inserirTudo(Grafo *G, int M[][MAXI],float d[][2]){
    int i,j;
    for (i=0;i<Num_City;i++){
        inserir_vertice(G, (int)'A'+i,M);
    }
    for (i=0;i<Num_City;i++){
        for(j=0;j<Num_City;j++){
            if(j!=i){
                inserir_aresta(G, (int)'A',(int)'B',CalculaDist(d[i][0],d[i][1],d[j][0],d[j][1]),M);
            }
        }
    }
}


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


Ordena(&Simples);
imprimir(&Simples);
return 0;
}
