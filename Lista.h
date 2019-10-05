#ifndef _LISTA_
#define _LISTA_
#include <stdio.h>

/* TAD Lista*/

typedef void *Item;
typedef void *Posic;
typedef void *Lista;
typedef void (*eraseItemL)(Item);
typedef void (*showLI)(Item);
typedef int (*compareToL)(Item, Item);

/* Cria a lista e retorna seu endereço */
Lista createLista();

/* Retorna o tamanho da lista*/
int tamanhoLista(Lista list);

/* A função insere ao final da lista o item info */
Posic insertLista(Lista list, Item info);

/* A função remove da lista o item com endereço info */
void removeLista(Lista list, Posic info);

/* A função procura na lista pelo item com endereço p, e retorna o item */
Item getItem(Lista list, Posic p);

/* A função insere um item na lista, antes do item com endereço p */
Posic insertBefore(Lista list, Posic p, Item info);

/* A função insere um item na lista, depois do item com endereço p */
Posic insertAfter(Lista list, Posic p, Item info);

/* A função retorna o indicador do primeiro elemento da lista */
Posic getFirst(Lista list);

/* A função retorna o indicador do ultimo elemento da lista */
Posic getLast(Lista list);

/* A função retorna o indicador do proximo elemento após o indicador p da lista */
Posic getNext(Lista list, Posic p);

/* A função retorna o indicador do elemento anterior ao indicador p da lista */
Posic getPrevious(Lista list, Posic p);

/* Função apaga lista e sua informação */
int eraseLista(Lista list);
 
 /* Função apaga base da lista */
void eraseBase(Lista list);



/* O procedimento apaga todos os nós da lista. A função utilizada para apagar os Itens de list deve ser implementada pelo usuário. 
Caso não se queira apagar os Itens func deve receber NULL. */
int eraseListaL(Lista list, eraseItemL func);

/*A função insere um item no final de uma lista.
   Retorna 1 se a inserção ocorreu corretamente e 0 caso contrário.*/
int insertEndL(Lista list, Item item);

/*A função remove um nó de list. A função de comparação de Itens deve ser implementada pelo usuário. 
	Retorna NULL caso o Item não exista em list e retorna o Item caso contrário.
   	func != NULL.*/
Item removeItemL2(Lista list, Item item, compareToL func);

/*
   A função remove um nó de list na última posição. A função de remoção (func) deve ser implementada pelo usuário. func = NULL caso não se queira eliminar o Item no nó removido.
   Retorna 1 caso a remoção foi realizada com sucesso e 0 caso contrário.
 */
int removeEndL(Lista list, eraseItemL func);
 
/*
   A função remove um nó de list na primeira posição. A função de remoção (func) deve ser implementada pelo usuário. func = NULL caso não se queira eliminar o Item no nó removido.
   Retorna 1 caso a remoção foi realizada com sucesso e 0 caso contrário.
 */
int removeBeginL(Lista list, eraseItemL func);

/*
   A função procura e retorna um Item contido em list. A função de comparação de Itens deve ser implementada pelo usuário. Retorna NULL caso Item não exista em list.
   func != NULL.
 */
Item searchItemL(Lista list, Item item, compareToL func);

Item getItemL(Lista list, int p);

Item getBeginItemL(Lista list);

int removeMiddleL(Lista list, int p, eraseItemL func);

int insertBeginL(Lista list, Item item);

Item getEndItemL(Lista list);

#endif