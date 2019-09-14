#include <locale.h>
#include <stdio.h>
#include <stdlib.h>


#define MAXI 30
//structs de listas
typedef struct tag_lista
{
    int Arv;
    int cor;
    int d;
    int pai;
    int tempo_final;
    int endereco;
    struct tag_lista *prox;
    struct tag_lista *ant;

} no_lista;
typedef struct
{
    no_lista *inicio;
    int quant;
} lista;
//fim de structs de listas
//structs de grafos
typedef struct tag
{
    int chave;
    struct tag *aresta;
    struct tag *vertice;
    int Grau;
    int peso;
} no;
typedef struct
{
    no *inicio;
    int qt_ve;
    int qt_ar;
} Grafo;
//fim de structs de grafos
// structs de fila
typedef struct Notag
{
    int chave;
    int chamada;
    struct Notag *link;
} No_Fila;
typedef struct
{
    No_Fila *inicio;
    No_Fila *fim;
    int quant;
} fila;
//fim de structs de fila
//funções de filas
void definir_fila(fila *L)
{
    L->inicio = NULL;
    L->fim = NULL;
    L->quant = 0;
}
int inserirFila(fila *L, int valor)
{
    if (L->quant == 0)
    {
        No_Fila *p;
        p = (No_Fila *)malloc(sizeof(No_Fila));
        p->chave = valor;
        p->link = NULL;
        p->chamada = 1;
        L->inicio = p;
        L->fim = p;
        L->quant++;
        return 0;
    }
    else
    {
        No_Fila *aux = malloc(sizeof(No_Fila));
        aux->chave = valor;
        aux->chamada = L->quant + 1;
        aux->link = NULL;
        L->fim->link = aux;
        L->fim = aux;
        L->quant++;
        return 0;
    }
    return -1;
}
int removerFila(fila *L)
{
    if (L->quant == 0)
        return -1;
    if (L->quant == 1)
    {
        //printf("if\n");
        No_Fila *p = L->inicio;
        L->inicio = NULL;
        L->fim == NULL;
        int x = p->chave;
        free(p);
        L->quant--;
        return x;
    }
    else
    {
        //printf("else\n");
        No_Fila *p = L->inicio;
        L->inicio = p->link;
        int x = p->chave;
        //printf("else pchave%d l->quant%d\n",p->chave,L->quant);
        free(p);

        L->quant--;
        //printf("aqui?");
        return x;
        // printf("retorno?");
    }
}
int Busca_Fila(fila *L, int x)
{
    No_Fila *p;
    p = L->inicio;
    while (p != NULL)
    {
        if (x == p->chave)
            return 1;
        p = p->link;
    }
    return 0;
}
//fim de funções de filas
//funções de listas
void define_lista(lista *L)
{
    L->inicio = NULL;
    L->quant = 0;
}
void insere_lista(lista *L, int arv, int D, int Cor, int Pai, int Tempo, int Ende)
{
    if (L->quant == 0)
    {
        no_lista *p;
        p = malloc(sizeof(no_lista));
        p->endereco = Ende;
        p->cor = Cor;
        p->d = D;
        p->Arv = arv;
        p->tempo_final = Tempo;
        p->pai = Pai;
        p->prox = NULL;
        p->ant = NULL;
        L->inicio = p;
        L->quant++;
    }
    else
    {
        no_lista *q;
        q = L->inicio;
        no_lista *p;
        p = malloc(sizeof(no_lista));
        p->endereco = Ende;
        p->cor = Cor;
        p->Arv = arv;
        p->d = D;
        p->tempo_final = Tempo;
        p->pai = Pai;
        p->prox = NULL;
        while (q->prox != NULL)
        {
            q = q->prox;
        }
        q->prox = p;
        q = L->inicio;
        while (q->prox != p)
            q = q->prox;
        p->ant = q;
        L->quant++;
    }
}
void remove_lista(lista *l, int arv)
{
    no_lista *p;
    no_lista *q;
    no_lista *r;
    p = l->inicio;
    int verifica = arv;
    int verifica2;
    //printf("excluindo=%c \n",(char)arv);
    while (p->Arv != arv)
    {
        verifica2 = p->Arv;
        //printf("p->arv=%c %d\n",(char)verifica2,verifica2);
        p = p->prox;
    }
    if ((p->ant == NULL) && (p->prox == NULL))
    {
        l->inicio = NULL;
        free(p);
    }
    else
    {
        if (p->ant == NULL)
        {
            l->inicio = p->prox;
            q = p->prox;
            q->ant = NULL;
            free(p);
        }
        else
        {
            q = p->prox; /* code */
            r = p->ant;
            if (p->prox == NULL)
            {
                r->prox = NULL;
                free(p);
            }
            else
            {
                q->ant = r;
                r->prox = q;
                free(p);
            }
        }
    }
    l->quant--;
}
int Busca_lista(lista *l, int k)
{
    no_lista *p;
    p = l->inicio;
    while (p->prox != NULL)
    {
        if (p->Arv == k)
            return 1;
        p = p->prox;
    }
    if (p->Arv == k)
        return 1;
    return 0;
}
//fim de funções de lista
void definir(Grafo *G)
{
    G->inicio = NULL;
    G->qt_ar = 0;
    G->qt_ve = 0;
}
/*void Matriz(Grafo *G, int M[][MAXI]){
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
    //printf("\n\t");
}*/
void inserir_vertice(Grafo *G, int x, int M[][MAXI])
{
    if (G->qt_ve == 0)
    {
        no *p;
        p = malloc(sizeof(no));
        p->chave = x;
        p->vertice = NULL;
        p->aresta = NULL;
        G->inicio = p;
        G->qt_ve++;
        //printf("\tInserida a primeira vértice. Chamada %c\n", (char)x);
        p->Grau = 0;
        //Matriz(G,M);
        return;
    }
    else
    {
        no *aux;
        aux = G->inicio;
        if (x == aux->chave)
        {
            printf("\n\tNúmero da vértice inválido, já contém vértice nomeada com o número %d.\n", x);
            return;
        }
        while (aux->vertice != NULL)
        {
            aux = aux->vertice;
            if (x == aux->chave)
            {
                printf("\n\tNúmero da vértice inválido, já contém vértice nomeada com o número %d.\n", x);
                return;
            }
        }
        no *p;
        no *f;
        p = malloc(sizeof(no));
        f = G->inicio;
        p->chave = x;
        p->vertice = NULL;
        p->aresta = NULL;
        while (f->vertice != NULL)
            f = f->vertice;
        f->vertice = p;
        G->qt_ve++;
        //printf ("\tInserida uma nova vértice. chamada %c\n",(char)x);
        p->Grau = 0;
        //Matriz(G,M);
        return;
    }
}
void inserir_aresta(Grafo *G, int x, int y, int pe, int M[][MAXI])
{
    int flag_arX = 0;
    int flag_arY = 0;
    int cont = 0;
    no *aux2;
    aux2 = G->inicio;
    while (aux2->vertice != NULL)
    {
        if (aux2->chave == x)
            flag_arX = 1;
        if (aux2->chave == y)
            flag_arY = 1;
        aux2 = aux2->vertice;
        if (aux2->chave == x)
            flag_arX = 1;
        if (aux2->chave == y)
            flag_arY = 1;
        cont++;
    }
    if ((flag_arX == 0) || (flag_arY == 0))
    {
        printf("\n\tVértice inexistente\n");
        flag_arX = 0;
        flag_arY = 0;
        return;
    }
    if (G->qt_ve < 2)
    {
        //printf("\n\tNúmero de vértice insuficiente para ser colocado arestas.\n");
        return;
    }
    if (pe < 0)
    {
        //printf("\n\tArestas não podem ter peso negativo.");
        return;
    }
    else
    {
        no *j;
        no *k;
        j = G->inicio;
        while (j->chave != x)
        {
            j = j->vertice;
        }
        k = j->aresta;
        while (k != NULL)
        {
            if (k->chave == y)
            {
                //printf("\n\taresta já existente");
                return;
            }
            k = k->aresta;
        }
        if (x == y)
        {
            //printf("\n\tProibido fazer laços");
            return;
        }
        else
        {
            no *aux;
            no *p;
            p = malloc(sizeof(no));
            aux = malloc(sizeof(no));
            aux = G->inicio;
            p->chave = y;
            p->peso = pe;
            p->vertice = NULL;
            p->aresta = NULL;
            while (aux->chave != x)
                aux = aux->vertice;
            aux->Grau = aux->Grau + 1;
            while (aux->aresta != NULL)
                aux = aux->aresta;
            aux->aresta = p;
            no *q;
            q = malloc(sizeof(no));
            aux = G->inicio;
            q->chave = x;
            q->peso = pe;
            q->vertice = NULL;
            q->aresta = NULL;
            while (aux->chave != y)
                aux = aux->vertice;
            aux->Grau = aux->Grau + 1;
            while (aux->aresta != NULL)
                aux = aux->aresta;
            aux->aresta = q;
        }
        //printf("\tAresta %c %c inserida\n",(char)x ,(char)y);
        //Matriz(G, M);
    }
}
void imprimir(Grafo *G)
{
    if (G->qt_ve == 0)
    {
        printf("\n\tGrafo vazio.\n");
    }
    else
    {
        printf("\tGrafo\n");
        printf("\tVértices|Arestas\n");
        no *aux;
        aux = G->inicio;
        no *aux2;
        while (aux != NULL)
        {
            printf("\t");
            aux2 = aux;
            while (aux2 != NULL)
            {
                if (aux2 == aux)
                    printf("|(%c)|\t->", (char)aux2->chave);
                else
                    printf("|(%c)|P=%d|->", (char)aux2->chave, aux2->peso);
                aux2 = aux2->aresta;
            }
            printf("NULL\n");
            aux = aux->vertice;
        }
    }
}
int verifica_vertice(Grafo *G, int x)
{
    no *p;
    p = G->inicio;
    // printf("\ninicio=%d\n", G->inicio->chave);
    // p=malloc(sizeof (no));
    while (p != NULL)
    {
        //   printf("\nok ini%d -%d\n", x, p->chave);
        if (p->chave == x)
        {
            //      printf("\nretornou 1 %d -%d\n", x, p->chave);
            return 1;
        }
        p = p->vertice;
    }
    // printf("\n retorno 0\n");
    return 0;
}
int verifica_aresta(Grafo *G, int x, int y)
{
    if ((verifica_vertice(G, x) == 0) || (verifica_vertice(G, y) == 0))
    {
        return 0;
    }
    if (x == y)
    {
    }
    else
    {
        int aux;
        no *p;
        p = G->inicio;
        while (p->chave != x)
            p = p->vertice;
        while (p->aresta != NULL)
        {
            if (p->chave == y)
            {
                aux = 1;
            }
            p = p->aresta;
        }
        if (p->chave == y)
            aux = 1;
        if (aux == 1)
        {
            return 1;
        } //ta ok aqui vai pra remover é la a treta
        else
            return 0;
    }
}
void remover_aresta(Grafo *G, int x, int y, int M[][MAXI])
{
    if (verifica_aresta(G, x, y) == 0)
    {
        //printf("\n\tUma das arestas não existem!");
        return;
    }
    else
    {
        if (x == y)
        {
            no *p, *aux;
            p = G->inicio;
            while (p->chave != x)
                p = p->vertice;
            aux = p;
            p = p->aresta;
            while (p->chave != x)
            {
                aux = aux->aresta;
                p = p->aresta;
                if (p == NULL)
                {
                    //printf("\n\tLaço não encontrado, falha na remoção\n");
                    return;
                }
            }
            aux->aresta = p->aresta;
            free(p);
        }
        else
        {
            no *p, *aux;
            p = G->inicio;
            while (p->chave != x)
                p = p->vertice;
            p->Grau--;
            aux = p;
            p = p->aresta;
            while (p->chave != y)
            {
                aux = aux->aresta;
                p = p->aresta;
            }
            aux->aresta = p->aresta;
            free(p);

            p = G->inicio;
            while (p->chave != y)
                p = p->vertice;
            p->Grau--;
            aux = p;
            p = p->aresta;
            while (p->chave != x)
            {
                aux = aux->aresta;
                p = p->aresta;
            }
            aux->aresta = p->aresta;
            free(p);
        }
        //printf("\n\tAresta removida com sucesso!\n");
    }
    //Matriz(G, M);
}
void remover_vertice(Grafo *G, int x, int M[][MAXI])
{
    if (verifica_vertice(G, x) == 0)
    {
        //printf("\n\tO vertice não existe!\n");
        return;
    }
    if (G->inicio->chave == x)
    {
        no *p, *q;
        int y;
        p = G->inicio;
        while (p->chave != x)
            p = p->vertice;
        p = p->aresta;
        while (p != NULL)
        {
            y = p->chave;
            p = p->aresta;
            remover_aresta(G, x, y, M);
        }
        p = G->inicio;
        q = p->vertice;
        G->inicio = q;
        free(p);
        //printf("\n\tRemoção de vertice %d concluida.", x);
        G->qt_ve--;
    }
    else
    {
        no *p, *q, *s, *aux, *aux2, *aux3;
        int y;
        p = G->inicio;
        //removendo arestas com x
        while (p->chave != x)
            p = p->vertice;
        p = p->aresta;
        while (p != NULL)
        {
            y = p->chave;
            p = p->aresta;
            remover_aresta(G, x, y, M);
        }
        //removendo vertice
        p = G->inicio;
        q = p->vertice;
        s = q->vertice;
        while (q->chave != x)
        {
            p = p->vertice;
            q = q->vertice;
            s = s->vertice;
        }
        p->vertice = s;
        free(q);

        //printf("\n\tRemoção de vertice %d concluida.", x);
        G->qt_ve--;
    }
    //Matriz(G, M);
}

int Grau(Grafo *G, int x)
{
    if (verifica_vertice(G, x) == 0)
    {
        //printf("\n\tvertice inexistente");
        return -1;
    }
    no *p;
    p = G->inicio;
    while (p->chave != x)
        p = p->vertice;
    return p->Grau;
}

void Ordena(Grafo *G)
{
    if (G->qt_ve == 2)
    {
        no *p, *q, *r, *aux, *aux2;
        r = G->inicio;
        p = r->vertice;
        q = p->vertice;
        if (r->chave > p->chave)
        {
            aux = p->vertice;
            G->inicio = p;
            p->vertice = r;
            r->vertice = aux;
        }
    }
    if (G->qt_ve > 2)
    {
        int cont;
        no *p, *q, *r, *aux, *aux2;
        r = G->inicio;
        p = r->vertice;
        q = p->vertice;
        cont = 3;
        while (cont != G->qt_ve + 1)
        {
            while (q != NULL)
            {

                if (p->chave > q->chave)
                {
                    aux = q->vertice;
                    r->vertice = q;
                    p->vertice = aux;
                    q->vertice = p;

                    cont = 2;
                    r = G->inicio;
                    p = r->vertice;
                    q = p->vertice;
                }
                else
                {
                    if (r->chave > p->chave)
                    {
                        aux = p->vertice;
                        G->inicio = p;
                        p->vertice = r;
                        r->vertice = aux;
                        cont = 2;
                        r = G->inicio;
                        p = r->vertice;
                        q = p->vertice;
                    }
                    else
                    {
                        r = r->vertice;
                        p = p->vertice;
                        q = q->vertice;
                    }
                }
            }
            cont++;
        }
    }
    // printf("ordenou vertices corretamente\n");
    //ordenando os vertices

    int cont;
    no *p, *q, *r, *aux, *s;
    s = G->inicio;
    //  p=r->vertice;
    //q=p->vertice;
    cont = 0;
    //printf("ok?");
    while (s != NULL)
    {
        //printf("inicio while de s\n");
        no *aux2;

        cont = 3;
        //printf("chave %d ,grau %d\n",s->chave ,Grau(G, s->chave));
        if (Grau(G, s->chave) == 2)
        {
            r = s->aresta;
            p = r->aresta;
            q = p->aresta;
            // printf("ponteiros apontados\n");
            // printf("entro if grau==2\n");
            no *p, *q, *r, *aux, *aux2;
            r = s->aresta;
            p = r->aresta;
            q = p->aresta;
            if (r->peso > p->peso)
            {
                aux = p->aresta;
                s->aresta = p;
                p->aresta = r;
                r->aresta = aux;
            }
            // printf("saindo grau==2\n");
        }
        if (Grau(G, s->chave) > 2)
        {
            r = s->aresta;
            p = r->aresta;
            q = p->aresta;
            //  printf("ponteiros apontados\n");
            while (cont != Grau(G, s->chave) + 1)
            {

                while (q != NULL)
                {
                    // printf("entrou while q!=null\n");
                    if (p->peso > q->peso)
                    {
                        //  printf("if p->peso>q->peso com P%d r Q%d\n",p->chave,q->chave);
                        aux = q->aresta;
                        r->aresta = q;
                        p->aresta = aux;
                        q->aresta = p;
                        cont = 2;
                        r = s->aresta;
                        p = r->aresta;
                        q = p->aresta;
                    }
                    else
                    {
                        //    printf("entrou else para r>p\n");
                        if (r->peso > p->peso)
                        {
                            // printf("entrou if r>p com R%d e P%d\n", r->chave,p->chave);
                            //aux=p->aresta;
                            s->aresta = p;
                            p->aresta = r;
                            r->aresta = q /*aux*/;
                            cont = 2;
                            r = s->aresta;
                            p = r->aresta;
                            q = p->aresta;
                        }
                        else
                        {
                            // printf("entrou else final\n");
                            r = r->aresta;
                            p = p->aresta;

                            q = q->aresta;
                        }
                    }
                }

                // printf("saiu while q!=null\n");
                cont++;
            }
        }
        s = s->vertice;
        // printf("fim while de s\n");
    }
    // printf("asdasdasd-");
}
int Busca_Largura(Grafo *G, int S, int flag)
{
    no *p;
    p = G->inicio;
    if (verifica_vertice(G, S) == 0)
    {
        //printf("\n\tvertice inexistente");
        return 0;
    }
    int u, dis;
    no_lista *r, *k;
    fila F;
    lista L;
    p = G->inicio;
    definir_fila(&F);
    define_lista(&L);
    while (p != NULL)
    {
        //lista arv distancia cor pai endereço
        insere_lista(&L, 0, -1, 0, -1, 0, p->chave);
        p = p->vertice;
    } /*ver oque esta na lista
        //apagar
        p=G->inicio;
        printf("\n");
        while (p!=NULL){
            printf("%d-%d=%d",p->chave,);
            p=p->vertice;
        }
        //apagar*/
    r = L.inicio;
    while (r->endereco != S)
        r = r->prox;
    r->cor = 1;
    r->d = 0;
    r->pai = 0;

    inserirFila(&F, S);
    while (F.quant != 0)
    {
        u = removerFila(&F);
        p = G->inicio;
        while (p->chave != u)
            p = p->vertice;
        //p=p->aresta;

        while (p != NULL)
        {
            r = L.inicio;
            while (r->endereco != p->chave)
                r = r->prox;
            // printf("\n%d==%d\n", r->endereco,p->chave);
            if (r->cor == 0)
            {
                //printf("ok?");
                r->cor = 1;
                //distancia de u+peso arrumar
                k = L.inicio; // para pegar o cor[u]
                while (k->endereco != u)
                    k = k->prox;
                //usar endereço de u pra saber sua distancia
                (r->d) = (k->d) + (p->peso);
                //printf("\nvertice %d %d é %d+%d= distancia",p->chave,r->endereco,r->d, p->peso);
                r->pai = u;
                inserirFila(&F, p->chave);
            }
            p = p->aresta;
        }
        // printf("\nPulou\n");
        r = L.inicio;
        while (r->endereco != u)
            r = r->prox;
        r->cor = 2;
    }
    if (flag == 0)
    {
        r = L.inicio;
        while (r != NULL)
        {
            //printf("\n\tDistância do vértice %d ao %d é %d \t O pai do vértice %d é %d",S, r->endereco,r->d, r->endereco, r->pai);
            r = r->prox;
        }
    }
    if (flag == 1)
    {
        r = L.inicio;
        while (r != NULL)
        {
            if (r->d == -1)
                return 1;
            r = r->prox;
        }
    }
}

int Conexo(Grafo *G)
{
    no *p;
    p = G->inicio;
    if (Busca_Largura(G, p->chave, 1) == 0)
    {
        //printf("\n\tO grafo é conexo.");
        return 0;
    }
    else
    {
        //printf("\n\tO grafo não é conexo.");
        return 1;
    }
}

void Busca_Profundidade_Visita(Grafo *G, lista *L, int u, int *tempo)
{
    no_lista *l;
    no *p, *q;
    l = L->inicio;
    while (l->endereco != u)
        l = l->prox;
    l->cor = 1;
    *tempo = *tempo + 1;
    l->d = *tempo;
    //para cada agr
    p = G->inicio;
    while (p->chave != u)
        p = p->vertice;
    q = p->aresta;
    while (q != NULL)
    {
        l = L->inicio;
        while (l->endereco != q->chave)
            l = l->prox;
        if (l->cor == 0)
        {
            l->pai = u;
            Busca_Profundidade_Visita(G, L, l->endereco, tempo);
        }

        q = q->aresta;
    }

    //fim cara cada
    l = L->inicio;
    while (l->endereco != u)
        l = l->prox;
    l->cor = 2;
    //qq é esse F?
    *tempo = *tempo + 1;
    l->tempo_final = *tempo;
}
int Busca_Profundidade(Grafo *G)
{
    int u, tempo;
    no *p;
    no_lista *r, *k;
    lista L;
    p = G->inicio;
    define_lista(&L);
    while (p != NULL)
    {
        //tempo arv cor pai tempo_final endereço
        insere_lista(&L, 0, -1, 0, -1, 0, p->chave);
        p = p->vertice;
    }
    tempo = 0;
    p = G->inicio;
    r = L.inicio;
    while (r != NULL)
    {
        if (r->cor == 0)
        {
            Busca_Profundidade_Visita(G, &L, r->endereco, &tempo);
        }
        r = r->prox;
    }

    r = L.inicio;
    while (r != NULL)
    {
        //printf("\n\tO vértice %d tem inicio no tempo %d e tempo de término %d.\t O pai do vétice %d é %d.", r->endereco,r->d,r->tempo_final,r->endereco, r->pai);
        r = r->prox;
    }
}

int Extrair_Minimo(fila *F, lista *L)
{
    int key, ende;
    No_Fila *f, *h, *i;
    no_lista *l, *v;
    /*f=F->inicio;
    while(f!=NULL){
        printf("%d-",f->chave);
        f=f->link;
    }*/

    f = F->inicio;
    l = L->inicio;
    v = L->inicio;
    while (v->endereco != f->chave)
        v = v->prox;
    key = v->d;
    ende = v->endereco;
    while (f != NULL)
    {
        l = L->inicio;
        while (l->endereco != f->chave) //alinhando lista e fila
            l = l->prox;
        if (key > l->d)
        {
            key = l->d;
            ende = l->endereco;
        }
        f = f->link;
    }
    //printf("\naqui esta o ende menor %d",ende);
    i = F->inicio;
    while (i->chave != ende)
        i = i->link;

    if (ende == F->inicio->chave)
    {
        //printf("\n\n inicio f->chave%d menor %d\n",F->inicio->chave,menor);

        //printf("primeiro menor%d F-<inicio->chave%d\n",menor,F->inicio->chave);
        return removerFila(F);
    }
    if (i->chamada == L->quant)
    {

        f = F->inicio;
        h = f->link;
        while (h->chave != ende)
        {
            f = f->link;
            h = h->link;
        }
        f->link = h->link;
        free(h);
        F->quant--;
        F->fim = f;
        //printf("\n\nfim f->chave%d\n",f->chave);
        return ende;
    }

    else
    {
        //printf("else menor%d F-<inicio->chave%d\n",menor,F->inicio->chave);
        f = F->inicio;
        h = f->link;
        while (h->chave != ende)
        {
            f = f->link;
            h = h->link;
        }
        //printf("else fchave%d hchave%d\n",f->chave,h->chave);
        f->link = h->link;
        free(h);
        F->quant--;
        //printf("\n\nmeio f->chave%d\n",f->chave);
        return ende;
    }
}
int inicia_Dijkstra(Grafo *G, fila *F, lista *L, int S)
{
    no *p, *Q;
    no_lista *r, *k;
    p = G->inicio;
    insere_lista(L, 0, 0, 0, -1, 0, S);

    while (p != NULL)
    { //preenche a lista
        //lista arv distancia cor pai tempo endereço &L,0,1000000,0,-1,0,p->chave
        if (p->chave != S)
        {
            insere_lista(L, 0, 500, 0, -1, 0, p->chave);
        }
        p = p->vertice;
    }
    /*
    r=L->inicio;
    //printf("ur");
    //printf("indo while r->endereço =%d", r->endereco);
    while(r->endereco!=S){
            //printf("ououio");//faz o D[S]=0
        r=r->prox;
    }
    r->d=0;*/
}
void relax(lista *L, int u, int v, int p)
{
    no_lista *g, *h;
    g = L->inicio;
    h = L->inicio;
    while (g->endereco != u)
        g = g->prox;
    while (h->endereco != v)
        h = h->prox;
    if (h->d > (g->d + p))
    {
        h->d = g->d + p;
        h->pai = u;
    }
}
void Arvore_Dijkstra(Grafo *G, int u)
{
    if (verifica_vertice(G, u) == 0)
    {
        //printf("\n\tvertice inexistente");
        return;
    }
    if (Conexo(G) == 1)
    {
        return;
    }
    no *p, *q;
    int a, i;
    no_lista *r, *k;
    No_Fila *y;
    fila F;
    lista L;
    definir_fila(&F);
    define_lista(&L);
    p = G->inicio;
    inicia_Dijkstra(G, &F, &L, u); //ok até aqui ele so preencheu a lista.
    for (i = 0; i < G->qt_ve; i++)
    {
        inserirFila(&F, u); //insere fila de prioridades
        p = G->inicio;
        while (p != NULL)
        {
            inserirFila(&F, p->chave);
            p = p->vertice;
        } //termina de inserir fila

        while (F.quant != 0)
        {
            a = removerFila(&F);
            q = G->inicio;
            while (q->chave != a) //so faz o q se alinhar a lista
                q = q->vertice;
            q = q->aresta;
            while (q != NULL)
            {
                relax(&L, a, q->chave, q->peso); //chama o relax para todos os vertices de 'a'
                q = q->aresta;
            }
        }
    }
    r = L.inicio;
    while (r != NULL)
    {
        //printf("\n\tA distância minima do vértice %d ao %d é %d. \t O pai de %d é %d.",u, r->endereco,r->d,r->endereco, r->pai);
        r = r->prox;
    }
}
void Prim(Grafo *G, int u)
{
    if (verifica_vertice(G, u) == 0)
    {
        //printf("\n\tvertice inexistente");
        return;
    }
    if (Conexo(G) == 1)
    {
        return;
    }
    no *p, *q;
    no_lista *r, *g;
    int a, i;
    No_Fila *y;
    fila F;
    lista L;
    definir_fila(&F);
    define_lista(&L);
    //inicia a lista para o prim
    p = G->inicio;
    insere_lista(&L, 0, 0, 0, -1, 0, u); //faz o no raiz receber 0
    while (p != NULL)
    { //preenche a lista
        //lista arv 'd' cor pai tempo endereço &L,0,1000000,0,-1,0,p->chave
        if (p->chave != u)
        {
            insere_lista(&L, 0, 500, 0, -1, 0, p->chave);
        }
        p = p->vertice;
    }
    //termina de iniciar a lista para o Prim
    inserirFila(&F, u); //insere fila de prioridades
    p = G->inicio;
    while (p != NULL)
    {
        if (p->chave != u)
        {
            inserirFila(&F, p->chave);
        }
        p = p->vertice;
    } //termina de inserir fila
    while (F.quant != 0)
    {
        a = Extrair_Minimo(&F, &L);
        q = G->inicio;
        while (q->chave != a)
        { //so faz o q se alinhar a lista
            q = q->vertice;
        }
        q = q->aresta;
        while (q != NULL)
        {
            g = L.inicio;
            while (g->endereco != q->chave)
            { //faz a lista se alinar com o q
                g = g->prox;
            }
            if ((Busca_Fila(&F, q->chave) == 1) && (q->peso < g->d))
            { //se v pertence a Q e w(u, v) < key[v]
                g->pai = a;
                g->d = q->peso;
            }
            q = q->aresta;
        }
    }
    r = L.inicio;
    while (r != NULL)
    {
        //printf("\n\tO vértice %d tem pai %d", r->endereco, r->pai);
        r = r->prox;
    }
}

