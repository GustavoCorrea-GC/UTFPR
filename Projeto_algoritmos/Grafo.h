#include <locale.h>
#include <stdio.h>
#include <stdlib.h>


#define MAXI 30
//structs de listas
typedef struct tag_lista{
    int Arv;
    int cor;
    int d;
    int pai;
    int tempo_final;
    int endereco;
    struct tag_lista *prox;
}no_lista;
typedef struct{
    no_lista *inicio;
    int quant;
}lista;
//fim de structs de listas
//structs de grafos
typedef struct tag{
    int chave;
    struct tag *aresta;
    struct tag *vertice;
    int Grau;
    int peso;
}no;
typedef struct{
    no *inicio;
    int qt_ve;
    int qt_ar;
}Grafo;
//fim de structs de grafos
// structs de fila
typedef struct Notag{
    int chave;
    int chamada;
    struct Notag *link;
}No_Fila;
typedef struct{
    No_Fila *inicio;
    No_Fila *fim;
    int quant;
}fila;
//fim de structs de fila
//funções de filas
void definir_fila (fila *L){
    L->inicio=NULL;
    L->fim=NULL;
    L->quant=0;
}
int inserirFila(fila *L, int valor){
    if(L->quant==0)
    {
        No_Fila *p;
        p = (No_Fila*)malloc(sizeof(No_Fila));
        p->chave = valor;
        p->link = NULL;
        p->chamada=1;
        L->inicio = p;
        L->fim = p;
        L->quant++;
        return 0;
    }
    else
    {
        No_Fila *aux=malloc(sizeof(No_Fila));
        aux->chave=valor;
        aux->chamada=L->quant+1;
        aux->link=NULL;
        L->fim->link=aux;
        L->fim=aux;
        L->quant++;
        return 0;
    }
    return -1;
}
int removerFila(fila *L){
    if(L->quant==0)
        return -1;
    if(L->quant==1){
        //printf("if\n");
        No_Fila *p=L->inicio;
        L->inicio=NULL;
        L->fim==NULL;
        int x = p->chave;
        free(p);
        L->quant--;
        return x;
    }
    else{
        //printf("else\n");
        No_Fila *p = L->inicio;
        L->inicio=p->link;
        int x =p->chave;
        //printf("else pchave%d l->quant%d\n",p->chave,L->quant);
        free(p);

        L->quant--;
        //printf("aqui?");
        return x;
       // printf("retorno?");
    }
}
int Busca_Fila(fila *L,int x){
    No_Fila *p;
    p=L->inicio;
    while(p!=NULL){
        if(x==p->chave)
            return 1;
        p=p->link;
    }
    return 0;
}
//fim de funções de filas
//funções de listas
void define_lista(lista *L){
    L->inicio = NULL;
    L->quant = 0;
}
void insere_lista(lista *L,int arv, int D, int Cor, int Pai,int Tempo, int Ende){
    if (L->quant==0){
        no_lista *p;
        p =malloc(sizeof(no_lista));
        p->endereco = Ende;
        p->cor = Cor;
        p->d = D;
        p->Arv=arv;
        p->tempo_final=Tempo;
        p->pai = Pai;
        p->prox = NULL;
        L->inicio = p;
        L->quant++;
    }
    else{
        no_lista *q;
        q=L->inicio;
        no_lista *p;
        p=malloc(sizeof(no_lista));
        p->endereco = Ende;
        p->cor = Cor;
        p->d = D;
        p->tempo_final=Tempo;
        p->pai = Pai;
        p->prox = NULL;
        while (q->prox!=NULL)
            q=q->prox;
        q->prox=p;
    }

}
//fim de funções de lista
void definir(Grafo *G) {
    G->inicio = NULL;
    G->qt_ar = 0;
    G->qt_ve = 0;
}
void Matriz(Grafo *G, int M[][MAXI]){
    int i=0,j=0, cont=1;
    no *p, *q;
    p=G->inicio;
    //zerando a matriz
    for(i=0;i<MAXI;i++){
        for(j=0;j<MAXI;j++){
            M[i][j]=0;
        }
    }
    //colocando o grafo na matriz
    while (p!=NULL){
        q=p->aresta;
        while (q!=NULL){
            M[p->chave-1][q->chave-1]=q->peso;//-1 pq a lista começa em 1 não em 0 igual matriz
            q=q->aresta;
        }
        p=p->vertice;
    }
    printf("\n\t");
}
void inserir_vertice(Grafo *G,int x, int M[][MAXI]){
    if (G->qt_ve==0){
        no *p;
        p=malloc(sizeof(no));
        p->chave=x;
        p->vertice=NULL;
        p->aresta=NULL;
        G->inicio=p;
        G->qt_ve++;
        printf("\tInserida a primeira vértice. Chamada %c\n", (char)x);
        p->Grau=0;
        Matriz(G,M);
        return;
    }
    else{
        no *aux;
        aux =G->inicio;
        if (x==aux->chave){
            printf ("\n\tNúmero da vértice inválido, já contém vértice nomeada com o número %d.\n", x);
                return;
            }
        while (aux->vertice!=NULL){
            aux= aux->vertice;
            if (x==aux->chave){
            printf ("\n\tNúmero da vértice inválido, já contém vértice nomeada com o número %d.\n", x);
                return;
            }
        }
        no *p;
        no *f;
        p=malloc(sizeof(no));
        f=G->inicio;
        p->chave=x;
        p->vertice=NULL;
        p->aresta=NULL;
        while (f->vertice!=NULL)
            f=f->vertice;
        f->vertice=p;
        G->qt_ve++;
        printf ("\tInserida uma nova vértice. chamada %c\n",(char)x);
        p->Grau=0;
        Matriz(G,M);
        return;
    }
}
void inserir_aresta (Grafo *G, int x, int y, int pe, int M[][MAXI]){
    int flag_arX=0;
    int flag_arY=0;
    int cont=0;
    no *aux2;
    aux2=G->inicio;
    while (aux2->vertice!=NULL){
        if (aux2->chave==x)
            flag_arX=1;
        if (aux2->chave==y)
            flag_arY=1;
        aux2=aux2->vertice;
        if (aux2->chave==x)
            flag_arX=1;
        if (aux2->chave==y)
            flag_arY=1;
        cont++;
    }
    if ((flag_arX==0)||(flag_arY==0)){
        printf ("\n\tVértice inexistente\n");
        flag_arX=0;
        flag_arY=0;
        return;
    }
    if (G->qt_ve<2){
        printf("\n\tNúmero de vértice insuficiente para ser colocado arestas.\n");
        return;
    }
    if(pe<0){
        printf("\n\tArestas não podem ter peso negativo.");
        return;
    }
    else{
        no *j;
        no *k;
        j=G->inicio;
        while (j->chave!=x){
            j=j->vertice;
        }
            k=j->aresta;
            while(k!=NULL){
                if(k->chave==y){
                    printf("\n\taresta já existente");
                    return;
                }
                k=k->aresta;
            }
        if(x==y){
        printf("\n\tProibido fazer laços");
        return;
        }
        else{
            no *aux;
            no *p;
            p=malloc(sizeof(no));
            aux=malloc(sizeof(no));
            aux=G->inicio;
            p->chave=y;
            p->peso=pe;
            p->vertice=NULL;
            p->aresta=NULL;
            while (aux->chave!=x)
                aux=aux->vertice;
            aux->Grau=aux->Grau+1;
            while (aux->aresta!=NULL)
                aux=aux->aresta;
            aux->aresta=p;
            no *q;
            q=malloc(sizeof(no));
            aux=G->inicio;
            q->chave=x;
            q->peso=pe;
            q->vertice=NULL;
            q->aresta=NULL;
            while (aux->chave!=y)
                aux=aux->vertice;
            aux->Grau=aux->Grau+1;
            while (aux->aresta!=NULL)
                aux=aux->aresta;
            aux->aresta=q;
        }
            printf("\tAresta %c %c inserida\n",(char)x ,(char)y);
            Matriz(G, M);
    }
}
void imprimir(Grafo *G){
    if(G->qt_ve==0){
            printf("\n\tGrafo vazio.\n");
    }
    else{
        printf("\tGrafo\n");
        printf ("\tVértices|Arestas\n");
        no *aux;
        aux=G->inicio;
        no *aux2;
        while(aux!=NULL){
            printf("\t");
            aux2=aux;
            while(aux2!=NULL){
                if(aux2==aux)
                    printf("|(%c)|\t->", (char)aux2->chave);
                else
                printf("|(%c)|P=%d|->", (char)aux2->chave, aux2->peso);
                aux2=aux2->aresta;
            }
            printf ("NULL\n");
            aux=aux->vertice;
        }
    }
}
int verifica_vertice(Grafo *G, int x){
    no *p;
    p=G->inicio;
   // printf("\ninicio=%d\n", G->inicio->chave);
   // p=malloc(sizeof (no));
    while (p!=NULL){
         //   printf("\nok ini%d -%d\n", x, p->chave);
        if (p->chave==x){
                                     //      printf("\nretornou 1 %d -%d\n", x, p->chave);
            return 1;

        }
        p=p->vertice;
    }
   // printf("\n retorno 0\n");
    return 0;
}
int verifica_aresta(Grafo *G, int x, int y){
    if ((verifica_vertice(G, x)==0)||(verifica_vertice(G, y)==0)){
        return 0;
    }
    if(x==y){



    }
    else{
        int aux;
        no *p;
        p=G->inicio;
        while (p->chave!=x)
            p=p->vertice;
        while (p->aresta!=NULL){
            if(p->chave==y){
                aux=1;}
            p=p->aresta;
        }
        if(p->chave==y)
            aux=1;
        if (aux==1){
            return 1;}//ta ok aqui vai pra remover é la a treta
        else
            return 0;
    }
}
void remover_aresta(Grafo *G, int x, int y,int M[][MAXI]){
    if (verifica_aresta(G, x, y)==0){
            printf("\n\tUma das arestas não existem!");
        return;
    }
    else{
        if(x==y){
            no *p, *aux;
            p=G->inicio;
            while (p->chave!=x)
                p=p->vertice;
            aux=p;
            p=p->aresta;
            while (p->chave!=x){
                aux=aux->aresta;
                p=p->aresta;
                if (p==NULL){
                    printf("\n\tLaço não encontrado, falha na remoção\n");
                    return;
                    }
            }
            aux->aresta=p->aresta;
            free(p);
        }
        else{
            no *p, *aux;
            p=G->inicio;
            while (p->chave!=x)
                p=p->vertice;
            p->Grau--;
            aux=p;
            p=p->aresta;
            while (p->chave!=y){
                aux=aux->aresta;
                p=p->aresta;
            }
            aux->aresta=p->aresta;
            free(p);


            p=G->inicio;
            while(p->chave!=y)
                p=p->vertice;
            p->Grau--;
            aux=p;
            p=p->aresta;
            while(p->chave!=x){
                aux=aux->aresta;
                p=p->aresta;
            }
            aux->aresta=p->aresta;
            free(p);
        }
        printf("\n\tAresta removida com sucesso!\n");
    }
    Matriz(G, M);
}
void remover_vertice(Grafo *G, int x,int M[][MAXI]){
    if (verifica_vertice(G, x)==0){
            printf("\n\tO vertice não existe!\n");
        return;
    }
    if (G->inicio->chave==x){
        no *p,*q;
        int y;
        p=G->inicio;
        while (p->chave!=x)
        p=p->vertice;
        p=p->aresta;
            while (p!=NULL){
                y=p->chave;
                p=p->aresta;
            remover_aresta(G, x, y, M);
        }
        p=G->inicio;
        q=p->vertice;
        G->inicio=q;
       free(p);
        printf("\n\tRemoção de vertice %d concluida.", x);
        G->qt_ve--;
    }
    else{
       no *p,*q,*s, *aux, *aux2,*aux3;
       int y;
       p=G->inicio;
       //removendo arestas com x
        while (p->chave!=x)
        p=p->vertice;
        p=p->aresta;
            while (p!=NULL){
                y=p->chave;
                p=p->aresta;
            remover_aresta(G, x, y, M);
        }
        //removendo vertice
       p=G->inicio;
       q=p->vertice;
       s=q->vertice;
       while(q->chave!=x){
        p=p->vertice;
        q=q->vertice;
        s=s->vertice;
       }
       p->vertice=s;
       free(q);

        printf("\n\tRemoção de vertice %d concluida.", x);
        G->qt_ve--;
    }
    Matriz(G, M);
}

int Grau(Grafo *G, int x){
    if(verifica_vertice(G,x)==0){
        printf("\n\tvertice inexistente");
        return -1;
    }
    no *p;
    p=G->inicio;
    while (p->chave!=x)
        p=p->vertice;
    return p->Grau;
}


void Ordena(Grafo *G){
    if(G->qt_ve==2){
        no *p,*q,*r, *aux,*aux2;
        r=G->inicio;
        p=r->vertice;
        q=p->vertice;
        if(r->chave>p->chave){
            aux=p->vertice;
            G->inicio=p;
            p->vertice=r;
            r->vertice=aux;
            }

    }
    if (G->qt_ve >2){
        int cont;
        no *p,*q,*r, *aux,*aux2;
        r=G->inicio;
        p=r->vertice;
        q=p->vertice;
        cont =3;
        while(cont !=G->qt_ve+1){
            while (q!=NULL){

                if (p->chave>q->chave){
                    aux=q->vertice;
                    r->vertice=q;
                    p->vertice=aux;
                    q->vertice=p;

                    cont =2;
                    r=G->inicio;
                    p=r->vertice;
                    q=p->vertice;

                }
                else{
                    if(r->chave>p->chave){
                        aux=p->vertice;
                        G->inicio=p;
                        p->vertice=r;
                        r->vertice=aux;
                        cont =2;
                        r=G->inicio;
                        p=r->vertice;
                        q=p->vertice;
                    }
                    else{
                        r=r->vertice;
                        p=p->vertice;
                        q=q->vertice;
                    }

                }

            }
        cont++;
        }
    }
   // printf("ordenou vertices corretamente\n");
    //ordenando os vertices


        int cont;
        no *p,*q,*r, *aux,*s;
        s=G->inicio;
      //  p=r->vertice;
        //q=p->vertice;
        cont =0;
        //printf("ok?");
        while(s!=NULL){
            //printf("inicio while de s\n");
            no *aux2;


            cont =3;
            //printf("chave %d ,grau %d\n",s->chave ,Grau(G, s->chave));
            if(Grau(G,s->chave)==2){
                    r=s->aresta;
                    p=r->aresta;
                    q=p->aresta;
                   // printf("ponteiros apontados\n");
                   // printf("entro if grau==2\n");
                no *p,*q,*r, *aux,*aux2;
                r=s->aresta;
                p=r->aresta;
                q=p->aresta;
                if(r->peso>p->peso){
                    aux=p->aresta;
                    s->aresta=p;
                    p->aresta=r;
                    r->aresta=aux;
                }
               // printf("saindo grau==2\n");
            }
            if(Grau(G,s->chave)>2){
                    r=s->aresta;
                    p=r->aresta;
                    q=p->aresta;
                  //  printf("ponteiros apontados\n");
                while(cont !=Grau(G, s->chave)+1){

                    while (q!=NULL){
                           // printf("entrou while q!=null\n");
                        if (p->peso>q->peso){
                          //  printf("if p->peso>q->peso com P%d r Q%d\n",p->chave,q->chave);
                            aux=q->aresta;
                            r->aresta=q;
                            p->aresta=aux;
                            q->aresta=p;
                            cont =2;
                            r=s->aresta;
                            p=r->aresta;
                            q=p->aresta;

                        }
                        else{
                            //    printf("entrou else para r>p\n");
                            if(r->peso>p->peso){
                               // printf("entrou if r>p com R%d e P%d\n", r->chave,p->chave);
                                //aux=p->aresta;
                                s->aresta=p;
                                p->aresta=r;
                                r->aresta=q/*aux*/;
                                cont =2;
                                r=s->aresta;
                                p=r->aresta;
                                q=p->aresta;
                            }
                            else{
                               // printf("entrou else final\n");
                                r=r->aresta;
                                p=p->aresta;

                                q=q->aresta;

                            }

                        }

                    }

                   // printf("saiu while q!=null\n");
                    cont++;
                }
        }
        s=s->vertice;
       // printf("fim while de s\n");
        }
       // printf("asdasdasd-");

}