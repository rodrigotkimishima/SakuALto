#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "whiteboard.h"

//char table[11][20];

history *SYS;
int IDL;
int FLAG = 0;

history* wbadmin_2_svc(void* blank, struct svc_req *rqstp)
{
    history *aux;
    /*
    SYS = malloc(sizeof(history));
    SYS->next = NULL;
    SYS->quadros = malloc(sizeof(quadro));
    strcpy(SYS->quadros->id, "here");
    SYS->quadros->usuarios = NULL;
    */
    aux = SYS;
    //printf("atrib: %s\n", aux->quadros->id);
    return(aux);
}

/*
usuario* loop_usuarios(usuario *auxusu, FILE *arq)
{
    char *line;
    while(1){
        if (feof(arq)){
            auxusu = NULL;
            break;
        }
        auxusu = malloc(sizeof(usuario));
        fscanf(arq, "%s %d %s %s %s %d%d%d\n", line, &auxusu->id, line, auxusu->nick, line, &auxusu->cor[0],&auxusu->cor[1],&auxusu->cor[2]);

        auxusu->next = loop_usuarios(auxusu->next, arq);
        return auxusu;
    }
    return auxusu;
}

void listaArq()
{
    DIR *dir;
    struct dirent *lsdir;
    dir = opendir("./data/");
    char* listaArqs[11];
    char name[20];
    
    
    int i = 0;
    while(1){
        int flag=1;
        lsdir = readdir(dir);
        if (lsdir == NULL){
                strcpy(table[i], "\0");
                return;
        }
        while ( strcmp(lsdir->d_name, ".")==0 || strcmp(lsdir->d_name, "..")==0){
            lsdir = readdir(dir);
            if (lsdir == NULL){
                listaArqs[i] = NULL;
                return;
            }
        }
        
        strcpy(name , lsdir->d_name);
        for(int j=0; j<strlen(name); j++){
            if(name[j] == '.' && flag){
                flag = 0;
                name[j] = '\0';
            }
        }
        
        strcpy(table[i], name);
        i++;
    }
    closedir(dir);
}

history* loop_quadros(history *aux, int k)
{
    FILE *arq;
    struct dirent *lsdir;
    char nome[32], *line, name[20], *token;

    printf("arq: %s\n", table[k]);

    if (strcmp(table[k], "\0")==0){
        aux = NULL;
        return aux;
    }

    aux = malloc(sizeof(history));
    aux->quadros = malloc(sizeof(quadro));
    strcpy(aux->quadros->id , table[k]);
    printf("COPY: %s\n", aux->quadros->id);
    aux->quadros->usuarios = malloc(sizeof(usuario));

    strcpy(nome, "./data/");
    strcat(nome, aux->quadros->id);
    strcat(nome, ".txt");
    printf("abrindo %s\n", nome);
    arq = fopen(nome, "r");
    do{
        fscanf(arq, "%s", name);
        printf("%s\n", name);
    }while(strcmp(name, "USERS:") != 0);  

    if(!feof(arq)){
        aux->quadros->usuarios = loop_usuarios(aux->quadros->usuarios, arq);
        printf("return loop usuarios\n");
    }   
    fclose(arq);
    
    aux->next = loop_quadros(aux->next, k+1);
    return aux;

}
*/
void* inicializa_1_svc(void* blank, struct svc_req *rqstp)
{
    /*
    printf("chamando lista arquivos...\n");
    listaArq();
    printf("chamando loop quadros...\n");
    SYS = loop_quadros(SYS, 0);
    
    printf("fim do carregamento\n");
    */
    SYS = NULL;
}

usuario* lastUser(usuario *user, char* nick)
{
    if (user == NULL){
        usuario *user;
        user = malloc(sizeof(usuario));
        user->id = 0;
        user->cor[0] = 0;
        user->cor[1] = 0;
        user->cor[2] = 0;
        strcpy(user->nick, nick);
        user->next = NULL;
        IDL = user->id;
        return user;
    }

    while(user->next != NULL){
        user->next = lastUser(user->next, nick);
        return user;
    }

    user->next = malloc(sizeof(usuario));
    printf("last id: %d, user: %s\n", user->id, user->nick);
    user->next->id = (user->id) + 1;
    printf("new id: %d\n", user->next->id);
    for (int i=0; i<3; i++){
        user->next->cor[i] = rand () %255;
    }
    strcpy(user->next->nick, nick);
    user->next->next = NULL;
    IDL = user->next->id;
    return user;
}
/*
usuario* addUserQuadro(usuario *users, usuario *new)
{
    if (users == NULL){
        users = new;
        return users;
    }

    while (users->next != NULL){
        users->next = addUserQuadro(users->next, new);
        return users;
    }

    users->next = new;
    return users;
}
*/
history* findQuadro(history *ht, char *id)
{
    history *qd;
    if (ht == NULL){
        printf("history null\n");
        return NULL;
    }
    if(strcmp(ht->quadros->id , id)==0){
        return ht;
    }
    //printf("quadro: %s\n", ht->quadros->id );
    if(ht->next!=NULL){
        if (strcmp(ht->next->quadros->id , id)==0){
            //printf("retornando quadro..\n");
            return ht;
        }
    }
    while (ht->next != NULL){
        qd = findQuadro(ht->next, id);
        return qd;
    }
    return NULL;
}
/*
void keepNewUser(usuario *new, char *qd)
{
    char nome[32];
    FILE *arq;

    strcpy(nome, "./data/");
    strcat(nome, qd);
    strcat(nome, ".txt");

    arq = fopen(nome, "a");
    fprintf(arq, "id %d nick %s cor %d%d%d\n", new->id, new->nick, new->cor[0], new->cor[1],new->cor[2]);
    fclose(arq);
}
*/
msg* signin_quadro_1_svc(quadro *qd, struct svc_req *rqstp)
{
    msg* res;
    res = malloc(sizeof(msg));

    printf("Usuario %s entrando no quadro %s...\n", qd->usuarios->nick, qd->id);
    usuario *new;
    quadro *selected;
    history *ret;
    char line[50], aux[5];

    printf("procurando quadro no sistema..\n");
    ret = findQuadro(SYS, qd->id);
    if(ret!=NULL){
        if(strcmp(ret->quadros->id, qd->id)==0){
            selected = ret->quadros;
        }else{
            selected = ret->next->quadros;
        }
    }else{
        selected = NULL;
    }
    if(selected == NULL){
        printf("\nQuadro não encontrado\n");
        strcpy(res->content, "\nQuadro não encontrado\n");
        return(res);
    }
    printf("criando novo usuario...\n");
    selected->usuarios = lastUser(selected->usuarios, qd->usuarios->nick);
    //selected->usuarios = addUserQuadro(selected->usuarios, new);
    //printf("escrevendo novo usuario....\n");
    //keepNewUser(new, qd->id);
    strcpy(line, "\nusuario de ID=");
    sprintf(aux, "%d", IDL);
    strcat(line, aux);
    strcat(line," adicionado!\n\n");
    strcpy(res->content, line);
    return(res);
} 

history* addQuadroSYS(quadro *new, history *ht)
{
    if (ht == NULL){
        printf("quadro null\n");
        ht = malloc(sizeof(history));
        ht->next = NULL;
        ht->quadros = malloc(sizeof(quadro));
        strcpy(ht->quadros->id , new->id);
        ht->quadros->usuarios = NULL;
        return ht;
    }
    printf("quadro: %s\n", ht->quadros->id);
    printf("chamando next quadro\n");
    ht->next = addQuadroSYS(new, ht->next);
    return ht;
}

int* new_quadro_1_svc( quadro* qd, struct svc_req *rqstp)
{
    FILE *data, *data2;
    char nome[32];
    static int res;

    printf("criando o quadro %s\n", qd->id);

    //verica se o id do quadro ja existe
    //procurando na pasta data um arquivo de nome qd->id.txt
    /*
    strcpy(nome , "./data/");
    strcat(nome, qd->id);
    strcat(nome, ".txt");

    printf("%s\n", nome);

    data = fopen(nome, "r");
    */
    //verifica nome quadro
    //se não existe
    //if (data == NULL){
        //printf("nome do quadro valido\n");
        //cria quadro/arquivo e retorna 1
        /*
        data = fopen(nome, "w");
        fprintf(data, "ID = %s\n", qd->id);
        fprintf(data, "%s", "USERS:\n");
        fclose(data);
    */
        //add ao sistema interno de quadros

        SYS = addQuadroSYS(qd, SYS);

        //envio msg to client//////////////////
    //}else{
        //se existe retorna 0
      //  fclose(data);
        //printf("quadro já existe!\n");
    //}

    return(&res);
}

history* listar_quadros_1_svc(void* balnk, struct svc_req *rqstp)
{
    history *aux;
    
    aux = SYS;
    
    return(aux);
}

usuario* erase_user_struct(usuario *users, int ID)
{
    if(users == NULL){
        FLAG = 1;
        return NULL;
    }
    if(users->id == ID){
        return users->next;
    }
    if (users->next->id == ID){
        users->next = users->next->next;
        return users;
    }

    users->next = erase_user_struct(users->next, ID);
    return users;  
}
/*
void erase_user_arq(char* nameARQ, int ID)
{
    FILE *file;
    char word[10];
    long int pos;
    int num;

    file = fopen(nameARQ, "r+a");
    while(1){
        pos = ftell(file);
        fscanf(file, "%s", word);
        if(strcmp(word, "id")==0){
            fscanf(file, "%d", &num);
            if(num == ID){
                break;
            }
        }
    }
    fseek(file, pos, SEEK_SET);
    fprintf(file, "%s", "\0");
    fclose(file);    
}
*/
msg* erase_user_1_svc(quadro *qd, struct svc_req *rqstp)
{
    int rsp, mark = 0;
    char nome[32];
    msg* resp;
    //apaga user na struct -> retorna se quadro vazio
    quadro *foundQ;
    usuario* users;
    history* ret;

    resp = malloc(sizeof(msg));
    /*
    strcpy(nome , "./data/");
    strcat(nome, qd->id);
    strcat(nome, ".txt");
    */
    ret = findQuadro(SYS, qd->id);
    if(ret!=NULL){
        if(strcmp(ret->quadros->id, qd->id)==0){
            foundQ = ret->quadros;
            mark = 1;
        }else{
            foundQ = ret->next->quadros;
        }
    }else{
        foundQ = NULL;
    }
    if(foundQ == NULL){
        strcpy(resp->content, "\nQuadro não encontrado\n");
        return resp;
    }
    printf("quadro %s encontrado\n", foundQ->id);
    users = erase_user_struct(foundQ->usuarios, qd->usuarios->id);
    if(users == NULL && FLAG){
        FLAG = 0;
        strcpy(resp->content, "\nUsuario não encontrado\n");
        return(resp);
    }
    foundQ->usuarios = users;
    
    printf("usuario apagado\n");
    //se quadro vazio -> apaga quadro
    if (foundQ->usuarios == NULL){
        printf("quadro apagado\n");
        if(!mark){
            ret->next = ret->next->next;
        }else{
            SYS = ret->next;
        }
        strcpy(resp->content, "\nquadro vazio apagado\n");
        return(resp);
        //remove(nome);
    //senão -> apaga usuario do arquivo
    }/*else{
        erase_user_arq(nome, qd->usuarios->id);
    }*/
    strcpy(resp->content, "\nusuario apagado\n");
    return(resp);
}