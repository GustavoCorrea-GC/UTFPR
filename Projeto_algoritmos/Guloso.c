// Nome: Gustavo Luiz Andrade Correa
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Leitura.h"
#include "Grafo.h"
#define Num_City 38 //original 29 ou 734

void inicialista(lista *l)
{
    int i = 0;
    while (i < Num_City)
    {
        insere_lista(l, ((int)'A') + i, 0, 0, 0, 0, 0);
        i++;
    }

}

void Guloso(Grafo *G, char inicio)
{
    int valor;
    int inicio0 = inicio;
    int distancia = 0;
    int flag = 0;
    no *q;
    no *s;
    q = G->inicio;
    lista l;
    lista caminho;
    no_lista *p;
    no_lista *r;
    define_lista(&l);
    define_lista(&caminho);
    inicialista(&l);
    p = l.inicio;
    no *k;
    printf("Cidades:%d\n", l.quant);
    remove_lista(&l, inicio);
    insere_lista(&caminho, inicio0, 0, 0, 0, 0, 0);
    while (l.quant != 0)
    {
        q = G->inicio;
        while (q->chave != inicio)
        {
            q = q->vertice;
        }
        valor = 100000000;
        while (q->aresta != NULL)
        {
            if ((q->peso != 0) && (q->peso < valor) && (Busca_lista(&l, q->chave) == 1))
            {
                s = q;
                valor = q->peso;
            }
            q = q->aresta;
        }
        remove_lista(&l, s->chave);
        distancia += s->peso;
        insere_lista(&caminho, s->chave, 0, 0, 0, 0, 0);
        inicio = s->chave;
        if ((l.quant == 0) && (flag == 0))
        {
            insere_lista(&l, inicio0, 0, 0, 0, 0, 0);
            flag = flag == 0 ? 1 : 0;
        }
    }
    r = caminho.inicio;
    printf("Distancia percorida:%d\nDistancia Ideal: 6656\n", distancia);
    insere_lista(&caminho, inicio0, 0, 0, 0, 0, 0);
    while (r->prox != NULL)
    {
        printf("->%c", (char)r->Arv);
        r = r->prox;
    }
    printf("\n");
}

int CalculaDist(float x1, float y1, float x2, float y2)
{
    double xd, yd;
    int dij;
    xd = x1 - x2;
    yd = y1 - y2;
    dij = rint(sqrt(xd * xd + yd * yd));
    return dij;
}

void inserirTudo(Grafo *G, int M[][MAXI], float d[][2])
{
    int i, j;
    for (i = 0; i < Num_City; i++)
    {
        inserir_vertice(G, (int)'A' + i, M);
    }
    printf("Vertices inseridos\n");
    for (i = 0; i < Num_City; i++)
    {
        for (j = 0; j < Num_City; j++)
        {
            if (j != i)
            {
                if (i < j)
                {
                    inserir_aresta(G, (int)'A' + i, (int)'A' + j, CalculaDist(d[i][0], d[i][1], d[j][0], d[j][1]), M);
                }
            }
        }
    }
    printf("Terminou inserção\n");
}



int main()
{
    clock_t t; 
    double time_taken; 
    char entrada;
    float Cidades[Num_City][2];
    readArchive(Cidades, "Leitura38.txt");
    //imprimirCidades(Cidades, Num_City);
    Grafo Simples;
    int i, j;
    int M[MAXI][MAXI];

    definir(&Simples);

    inserirTudo(&Simples, M, Cidades);

    Ordena(&Simples);
    //imprimir(&Simples);
    
    //printf("Digite o inicio:\n");
    //scanf("%c",&entrada);
    entrada='B';
    t = clock();
    Guloso(&Simples, entrada);
    t = clock() - t; 
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("O algoritmo guloso demorou %f segundos para executar \n", time_taken); 
    return 0;
}
