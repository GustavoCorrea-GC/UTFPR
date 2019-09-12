

/*float CalcDistancia( char *vetor ){
    xd = x[i] - x[j];
    yd = y[i] - y[j];
    dij = nint( sqrt( xd*xd + yd*yd) );
}*/
void imprimirCidades(float vetor[][2]){
    int k;
    for (k=0;k<29;k++){
        printf("%f %f\n", vetor[k][0],vetor[k][1]);
        k++;
    }

}

void readArchive(float cities[][2], char nome[]){
  FILE *arq_palavras;
  arq_palavras = fopen(nome, "rt"); // abre o arquivo txt

  char ch;
  char v[10];
  int i=0;
  int counter=0;
  int j=0;
  int k=0;
    while((ch = fgetc(arq_palavras)) != EOF) // verificaçao enquanto não é o final do arquivo
    {
        //printf("Counter%d k %d ch %c\n", counter,k,ch);
        if(ch != 10 && ch != 32){
            //printf("Counter%d k %d\n ", counter,k);
            if (counter>8){
                cities[i][k]=atof(v);
                //printf("0 1 =%f i=%d, k%d\n", cities[0][1],i,k);
                //printf("i k =%f \n", cities[i][k]);
                counter=0;
                if (k==1){
                    i++;
                }
                //printf("k= %d \n",k);
                k=k==0?1:0;
            }
            else{
                v[counter]=ch;
                counter++;
            }
        }

    
    }
    //printf("ué %f\n", cities[0][1]);
fclose(arq_palavras);
}