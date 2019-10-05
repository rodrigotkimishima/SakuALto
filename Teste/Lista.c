#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

typedef struct Element {
    Item info;
    struct Element *next;
    struct Element *previous; 
}Element;

typedef struct Base {
    Element *first;
    Element *last;
    int tamanho;
}Base;

Lista createLista(){
    Base *base = NULL;
    base = (Base *)malloc(sizeof(Base));
    if(base != NULL){
        base->first = NULL;
        base->last = NULL;
        base->tamanho = 0;
    }
    else{
        printf("Erro na alocação da memoria.\n");
    }
    return (Lista)base;
}

int tamanhoLista(Lista list){
    Base *base = (Base *)list;
    if(base->first == NULL){
        return 0;
    }
    return base->tamanho;
}

Posic insertLista(Lista list, Item info){
    Element *el1 = el1 = (Element *)malloc(sizeof(Element));
    Base *base = base = (Base *)list;
    if((tamanhoLista(list)) == 0){
        el1->info = info;
        el1->previous = NULL;
        el1->next = NULL;
        base->first = el1;
        base->last = el1;
        base->tamanho = base->tamanho +1;
    }
    else{
        el1->info = info;
        el1->previous = base->last;
        el1->next = NULL;
        base->last->next = el1;
        base->last = el1;
        base->tamanho = base->tamanho +1;
    }
    return el1;
}

void removeLista(Lista list, Posic info){
    Base *base = (Base *)list;
    Element *El1 = (Element *)info;
    if(tamanhoLista(list) != 0){
        if(El1->previous == NULL){
            base->first = El1->next;
            if(base->first != NULL){
                base->first->previous = NULL;
            }
        }
        else if(El1->next == NULL){
            base->last = El1->previous;
            if(base->last != NULL){
                base->last->next = NULL;
            }
        }
        else{
            El1->previous->next = El1->next;
            El1->next->previous = El1->previous;
        }
        base->tamanho--;
        if(El1 != NULL){
            free(El1);
        }
        return;
    }
}

Item getItem(Lista list, Posic p){
    Element *El1 = (Element *)p;
    if(tamanhoLista(list) != 0){
        if(El1->info != NULL){
            return El1->info;
        }
    }
    return NULL;
}

Posic insertBefore(Lista list, Posic p, Item info){
    Element *El = (Element *)p;
    Base *base = (Base *)list;
    Element *El2 = (Element *)malloc(sizeof(Element));
    if(tamanhoLista(list) != 0){
        if(El->previous == NULL){
            El2->info = info;
            El2->previous = NULL;
            El2->next = base->first;
            El->previous = El2;
            base->first = El2; 
            base->tamanho++;   
        }
        else{
            El2->info = info;
            El->previous->next = El2;
            El2->previous = El->previous;
            El2->next = El;
            El->previous = El2;
            base->tamanho++;
        }
    }
    else{
        El2 = insertLista(list, info);
    }
    return El2;
}

Posic insertAfter(Lista list, Posic p, Item info){
    Element *El = (Element *)p;
    Base *base = (Base *)list;
    Element *El2 = (Element *)malloc(sizeof(Element));
    if(tamanhoLista(list) != 0){
        if(El->next == NULL){
            El2->info = info;
            El2->next = NULL;
            El2->previous = base->last;
            El->next = El2;
            base->last = El2; 
            base->tamanho++;   
        }
        else{
            El2->info = info;
            El->next->previous = El2;
            El2->next = El->next;
            El2->previous = El;
            El->next = El2;
            base->tamanho++;
        }
    }
    else{
        El2 = insertLista(list, info);
    }
    return El2;
}

Posic getFirst(Lista list){
    Base *base = (Base *)list;
    return base->first;
}

Posic getLast(Lista list){
    Base *base = (Base *)list;
    return base->last;
}

Posic getNext(Lista list, Posic p){
    if(p != NULL){
        Element *El = (Element *)p;
        return El->next;
    }
    return NULL;
}

Posic getPrevious(Lista list, Posic p){
    Element *El = (Element *)p;
    return El->previous;
}

int eraseLista(Lista list){
    Base *base = (Base *)list;
    Element *aux, *aux2;
    int i, j;
    if (base != NULL)
    {
        if (base->first != NULL)
        {
            aux = base->first;
            j = tamanhoLista(list);
            for (i = 1; i <= j; i++)
            {
                aux2 = aux;
                aux = aux->next;
                free(aux2);
            }
            base->first = NULL;
            base->last = NULL;
            base->tamanho = 0;
            return 1;
        }
    }
    return 0;
}

void eraseBase(Lista list){
    Base *base = (Base *)list;
    if (base != NULL)
    {
        free(base);
    }
}
/*teste*/
int eraseListaL(Lista list, eraseItemL func)
{
    Base *base = (Base *)list;
    Element *aux, *aux2;
    int i, j;
    if (base != NULL)
    {
        if (base->first != NULL)
        {
            aux = base->first;
            j = tamanhoLista(list);
            for (i = 1; i <= j; i++)
            {
                aux2 = aux;
                aux = aux->next;
                if (func != NULL)
                    func(aux2->info);
                free(aux2);
            }
            base->first = NULL;
            base->last = NULL;
            base->tamanho = 0;
            return 1;
        }
    }
    return 0;
}

Item searchItemL(Lista list, Item item, compareToL func)
{
    Base *base = (Base *)list;
    Element *aux = NULL;
    Item info = NULL;
    int i = 0, j = 0;
    if (base != NULL)
    {
        if (base->first != NULL)
        {
            j = base->tamanho;
            aux = base->first;
            for (i = 1; i <= j; i++)
            {
                if (func(aux->info, item) == 1)
                {
                    info = aux->info;
                    break;
                }
                aux = aux->next;
            }
        }
    }
    return info;
}

int removeBeginL(Lista list, eraseItemL func)
{
    Base *base = (Base *)list;
    Element *aux = NULL;
    if (base != NULL)
    {
        if (base->first != NULL && base->tamanho == 1)
        {
            if (func != NULL)
                func(base->last->info);
            free(base->last);
            base->last = NULL;
            base->first = NULL;
            base->tamanho = base->tamanho - 1;
            return 1;
        }
        if (base->first != NULL)
        {
            aux = base->first->next;
            aux->previous = NULL;
            if (func != NULL)
                func(base->first->info);
            free(base->first);
            base->first = aux;
            base->tamanho = base->tamanho - 1;
            return 1;
        }
    }
    return 0;
}

int removeEndL(Lista list, eraseItemL func)
{
    Base *base = (Base *)list;
    Element *aux = NULL;
    if (base != NULL)
    {
        if (base->first != NULL && base->tamanho == 1)
        {
            if (func != NULL)
                func(base->last->info);
            free(base->last);
            base->last = NULL;
            base->first = NULL;
            base->tamanho = base->tamanho - 1;
            return 1;
        }

        if (base->first != NULL && base->tamanho > 1)
        {
            aux = base->last->previous;
            aux->next = NULL;
            if (func != NULL)
                func(base->last->info);
            free(base->last);
            base->last = aux;
            base->tamanho = base->tamanho - 1;
            return 1;
        }
    }
    return 0;
}

Item removeItemL2(Lista list, Item item, compareToL func)
{
    Base *base = (Base *)list;
    Element *aux = NULL;
    Item info = NULL;
    int i = 0, j = 0;
    if (base != NULL)
    {
        if (base->first != NULL)
        {
            aux = base->first;
            j = base->tamanho;
            for (i = 1; i <= j; i++)
            {
                if (func(aux->info, item) == 1)
                {
                    info = aux->info;
                    if (i == 1)
                    {
                        removeBeginL(list, NULL);
                    }
                    else if (i == j)
                    {
                        removeEndL(list, NULL);
                    }
                    else
                    {
                        aux->previous->next = aux->next;
                        aux->next->previous = aux->previous;
                        free(aux);
                        base->tamanho = base->tamanho - 1;
                    }
                    break;
                }
                aux = aux->next;
            }
        }
    }
    return info;
}

int insertBeginL(Lista list, Item item){
    Base *base = (Base *)list;
    Element *element = NULL;
    if (base != NULL){
        element = (Element *)malloc(sizeof(Element));
        if (element == NULL){
            return 0;
        }
        element->info = item;
        if (base->first != NULL){
            element->previous = NULL;
            element->next = base->first;
            base->first->previous = element;
            base->first = element;
        }
        else{
            base->first = element;
            base->last = element;
            element->next = NULL;
            element->previous = NULL;
        }
        base->tamanho = base->tamanho + 1;
        return 1;
    }
    return 0;
}

int insertEndL(Lista list, Item item)
{
    Base *base = (Base *)list;
    Element *element = NULL;
    if (base != NULL)
    {
        element = (Element *)malloc(sizeof(Element));
        if (element == NULL)
        {
            return 0;
        }
        element->info = item;
        if (base->first != NULL)
        {
            element->next = NULL;
            element->previous = base->last;
            base->last->next = element;
            base->last = element;
        }
        else
        {
            base->first = element;
            base->last = element;
            element->next = NULL;
            element->previous = NULL;
        }
        base->tamanho = base->tamanho + 1;
        return 1;
    }
    return 0;
}

Item getItemL(Lista list, int p)
{
    Base *base = (Base *)list;
    int i, j;
    Element *aux = NULL;
    Item item = NULL;
    if (base != NULL)
    {
        if (base->first != NULL)
        {
            aux = base->first;
            j = tamanhoLista(list);
            if (p <= 0 || p > j)
            {
                return NULL;
            }
            for (i = 1; i <= j; i++)
            {
                if (i == p)
                {
                    item = aux->info;
                    return item;
                }
                aux = aux->next;
            }
        }
    }
    return NULL;
}

Item getBeginItemL(Lista list){
    Base *base = (Base *)list;
    if (base != NULL)
    {
        if (base->first != NULL)
        {
            return (Item)base->first->info;
        }
    }
    return NULL;
}

int removeMiddleL(Lista list, int p, eraseItemL func){
    Base *base = (Base *)list;
    Element *aux = NULL;
    int i, j;
    if (p <= 0){
        return 0;
    }
    j = tamanhoLista(list);
    if (p == 1){
        removeBeginL(list, func);
        return 1;
    }
    else if (p >= j){
        removeEndL(list, func);
        return 1;
    }
    else{
        if (base != NULL){
            if (base->first != NULL){
                aux = base->first;
                base->tamanho = base->tamanho - 1;
                for (i = 1; i <= j; i++){
                    if (i == p){
                        if (func != NULL)
                            func(aux->info);
                        aux->previous->next = aux->next;
                        aux->next->previous = aux->previous;
                        free(aux);
                        break;
                    }
                    aux = aux->next;
                }
                return 1;
            }
        }
    }
    return 0;
}

Item getEndItemL(Lista list)
{
    Base *base = (Base *)list;
    if (base != NULL)
    {
        if (base->first != NULL)
        {
            return (Item)base->last->info;
        }
    }
    return NULL;
}