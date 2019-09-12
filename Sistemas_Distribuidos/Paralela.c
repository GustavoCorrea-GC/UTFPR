#include <stdio.h>
#include<omp.h>
#define Counter 1000000000

int main(){

    long i;
    double pi = 0;

    #pragma omp parallel for reduction(+: pi)
    {
        for (i=0;i<Counter;i++){
            pi +=1.0/(i*4.0+1.0);
            pi -= 1.0/(i*4.0 + 3.0);
        }
    }
    pi=pi*4.0;
    printf("sou pi: %lf\n",pi);
}