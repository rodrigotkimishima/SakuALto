#define PROGRAM_NUMBER 1111111
#define VERSION_NUMBER 1

   struct msg
   {
      char content[50];
   };

   struct usuario
   {
      char nick[20];
      int id;
      int cor[3];
      usuario *next;
   };

   struct quadro
   {
     char id[20];
     usuario *usuarios;
   };

   struct history
   {
      history* next;
      quadro *quadros;
   };

program WHITEBOARD_PROG
{
       version WHITEBOARD_VERSION
        {
           int NEW_QUADRO(quadro) = 1;
           msg SIGNIN_QUADRO(quadro) = 2;
           void INICIALIZA() = 3;
           history LISTAR_QUADROS() = 4;
           msg ERASE_USER(quadro) = 5;
        }
      = VERSION_NUMBER; 
      version WBADMIN_VERSION
      {
         history WBADMIN() = 1;
      }
      = 2;
}
= PROGRAM_NUMBER;

 
