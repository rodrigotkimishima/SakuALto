#include <stdio.h>
#include "whiteboard.h"

void main(int argc, char *argv[])
{
    CLIENT *clnt;
    history* data;

    printf("%s %s\n", argv[2], argv[3]);
    clnt = clnt_create (argv[2], WHITEBOARD_PROG, atoi(argv[3]), "udp");
   /* verifica se a referência foi criada */
   if (clnt == (CLIENT *) NULL)
   {
      printf("client null\n");
      clnt_pcreateerror (argv[0]);
      exit(1);
   }

    data = wbadmin_2(NULL, clnt);
    if (data == NULL){
        printf("sistema vazio\n");
        exit(1);
    }
    do{
        if (data->quadros == NULL){
            printf("ERROR: quadros não encontrados\n");
            exit(1);
        }
        printf("QUADRO: %s\n", data->quadros->id);
        printf("USUARIOS:\n");
        do{
            if(data->quadros->usuarios == NULL){
                printf("quadro sem usuarios\n");
                exit(1);
            }
            printf("- id: %d nick: %s\n", data->quadros->usuarios->id, data->quadros->usuarios->nick);
            data->quadros->usuarios = data->quadros->usuarios->next;
        }while( data->quadros->usuarios != NULL );
        data = data->next;
    }while(data != NULL);
}