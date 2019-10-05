#include <stdio.h>
#include <string.h>
#include "whiteboard.h"

void sairQuadro(CLIENT *clnt)
{
   quadro *qd;
   msg* resp;

   qd = malloc(sizeof(quadro));
   qd->usuarios = malloc(sizeof(usuario));

   printf("\ninforme o id do quadro que seu usuario se encontra: ");
   scanf("%s", qd->id);
   printf("\ninforme o seu id no quadro: ");
   scanf("%d", &(qd->usuarios->id));
   printf("\nid %d recebido\n", qd->usuarios->id);

   resp = erase_user_1(qd, clnt);
   printf("%s", resp->content);
}

/* cadastra um usuario num quadro existente*/
void entrarQuadro(quadro *qd, CLIENT *clnt)
{
   usuario *user;
   msg *resp;
   user = malloc(sizeof(usuario));

   printf("\ninforme o nick que deseja usar nesse quadro: ");
   scanf("%s", user->nick);

   qd->usuarios = user;

   resp = signin_quadro_1(qd, clnt);
   printf("%s",resp->content);
}

/* cria um novo quadro */
void criarQuadro(CLIENT *clnt, char *IP)
{
   printf("Criando quadro no server %s\n", IP);

   char *nome, server[15];
   quadro *sugest;
   int* flag;

   nome = malloc(20*sizeof(char));
   sugest = malloc(sizeof(quadro));

   //while(1){
      printf("\ninforme o id do quadro que deseja criar (não usar '.' ou espaços): ");
      scanf("%s", nome);

      strcpy(sugest->id , nome);  

      new_quadro_1(sugest, clnt);
      printf("\nquadro criado\n");
     // break;
   //}

   //criar usuario e add ao quadro criado
   entrarQuadro(sugest, clnt);
}

void entrarQuadroExist(CLIENT *clnt)
{
   quadro *base;
   msg* resp;

   //resp = malloc(sizeof(msg));
   base = malloc(sizeof(quadro));
   printf("informe o id do quadro que deseja entrar: ");
   scanf("%s", base->id);

   base->usuarios = malloc(sizeof(usuario));
   printf("\ninforme o nick que deseja usar nesse quadro: ");
   scanf("%s", base->usuarios->nick);

   resp = signin_quadro_1(base, clnt);
   printf("%s",resp->content);
}

int listarQuadros(CLIENT *clnt)
{
   history *list;
   list = listar_quadros_1(NULL, clnt);
   if (list == NULL){
        printf("não há quadros no sistema\n");
        return 0;
    }
    printf("\nLISTA DE QUADROS ATIVOS\n");
   do{
        if (list->quadros == NULL){
            printf("ERROR: quadros não encontrados\n");
            exit(1);
        }
        printf("- %s\n", list->quadros->id);
        list = list->next;
    }while(list != NULL);
    printf("\n");
}

int main( int argc, char *argv[])
{

   CLIENT *clnt;
   int code, tecla;
   char *IP;

   IP = malloc(15*sizeof(char));

   printf("\nInforme o endereço IP do servidor: ");
   scanf("%s", IP);
   setbuf(stdin, NULL);

   /* cria uma struct CLIENT que referencia uma interface RPC */
   clnt = clnt_create (IP, WHITEBOARD_PROG, WHITEBOARD_VERSION, "udp");
   /* verifica se a referência foi criada */
   if (clnt == (CLIENT *) NULL)
   {
      printf("client null\n");
      clnt_pcreateerror (IP);
      exit(1);
   }

   //printf("chamando inicializa...\n");
   //inicializa_1(NULL,clnt);
   //printf("saiu inicializa\n");

   while(1){
      printf("Informe o codigo da ação que deseja realizar:\n");
      printf("1. Criar um quadro\n");
      printf("2. Entrar em um quadro existente\n");
      printf("3. listar quadros ativos\n");
      printf("4. sair de quadro\n");
      printf("codigo: ");
      scanf("%d", &code);
      setbuf(stdin, NULL);

      if(code == 1){
         criarQuadro(clnt, IP);
      }else if (code == 2) {
         entrarQuadroExist(clnt);
      }else if (code == 3) {
         listarQuadros(clnt);
      }else if(code == 4){
         sairQuadro(clnt);
      }else{
         printf("código invalido!\n");
      }
   }

   return (0);
} 