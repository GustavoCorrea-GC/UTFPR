#include "Biblioteca.h"
#include <stdio.h>
static void fnSTX(SM_T *sm,char data);
static void fnChk(SM_T *sm,char data);
static void fnEnd(SM_T *sm,char data);
static void fnQtd(SM_T *sm,char data);
static void fnData(SM_T *sm,char data);
static void fnAddrV(SM_T *sm,char addr);
void execSM(SM_T *sm,char data);




int InitSM(SM_T *sm,short addr, handle_t handle){
    sm->state=ST_STX;
    sm->my_addr=addr;
    sm->handle=handle;
    sm->flag=FLAG_LOW;
    sm->action[ST_STX]=fnSTX;
    sm->action[ST_ADDR]=fnAddrV;
    sm->action[ST_QTD]=fnQtd;
    sm->action[ST_DATA]=fnData;
    sm->action[ST_CHK]=fnChk;
    sm->action[ST_END]=fnEnd;

}
static void fnSTX(SM_T *sm,char data){
    sm->check=0;
    sm->flag=FLAG_LOW;
    if(data==STX){
        sm->state=ST_ADDR;
    }
}
static void handle1(char *string){
    printf("Pacote é");
}

static void fnAddrV(SM_T *sm, char addr){
    sm->check+=addr;
    if(sm->flag==FLAG_LOW){
        sm->flag=FLAG_HIGH;
        sm->rx_addr=(short)addr;
    }

    if(sm->flag==FLAG_HIGH){
        sm->rx_addr=(short)(addr<<8);
        if(sm->rx_addr==sm->my_addr){
            sm->state=ST_QTD;
        }
        else{
            sm->state=ST_STX;
        }
    }
}

static void fnQtd (SM_T *sm,char data){

    if(data<BUFFER_SIZE){
        sm->state=ST_DATA;
        sm->qtdDado=data;
        sm->counter=0;
        sm->check+=data;
    }
    else{
       sm->state=ST_STX;
    }

}
static void fnData (SM_T *sm,char data){
    if (sm->qtdDado!=sm->counter){
        sm->buffer[sm->counter]=data;
        sm->counter++;
        sm->check+=data;
    }
    if(sm->qtdDado==sm->counter){
        sm->buffer[sm->counter]='\0'; 
        sm->state=ST_CHK;
    }
}
static void fnChk(SM_T *sm,char data){
    if(sm->check==data){
        sm->state=ST_END;
    }
    else{
        sm->state=ST_STX;//erro checksum 
    }
}

static void fnEnd(SM_T *sm,char data){
    if(data==ETX){
        sm->state=ST_STX;
    }
}

void execSM(SM_T *sm,char data){
    sm->action[sm->state]( *sm, data);
}
SM_T sm1,sm2;
int main (void){
    int k;
    k=3;
    printf("k=%d",k);
    k++;
    printf("k=%d",k);
    InitSM(&sm1,1000,handle1);

    while(1){
        execSM(&sm1, STX);


    }



}