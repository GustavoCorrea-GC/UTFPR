#ifndef _SM_H_
#define _SM_H_

#define STX '$'
#define ETX '\n'
#define BUFFER_SIZE 128
#define FLAG_HIGH 1
#define FLAG_LOW 0

typedef struct _SM_T SM_T;

typedef enum{
    ST_STX,ST_ADDR,ST_QTD,ST_DATA,ST_CHK,ST_END

}state_t;
typedef void(*Action_t)(SM_T, char);

typedef void(*handle_t)(char *);

typedef struct _SM_T{
    state_t state;
    short my_addr;
    short rx_addr;
    char flag;
    char buffer[BUFFER_SIZE];
    char check;
    char qtdDado;
    char counter;
    Action_t action[ST_END];
    handle_t handle;

}SM_T;





int InitSM(SM_T *sm, short addr, handle_t handle);

int ExecSM(SM_T *sm, char data);


#endif