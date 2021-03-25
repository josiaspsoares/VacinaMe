#include "cidadao.h"

#ifndef LISTA_DE_ESPERA_H
#define LISTA_DE_ESPERA_H

typedef struct MembroLista{
    Cidadao cidadao;
    struct MembroLista *anterior;
    struct MembroLista *proximo;
}TipoMembroLista;

typedef struct Lista{
    int quantidade;
    TipoMembroLista *primeiro;
    TipoMembroLista *ultimo;
}TipoLista;

TipoLista* criaLista();
void liberaLista(TipoLista *lista);
int insereListaFinal(TipoLista *lista);
int removeListaFinal(TipoLista *lista);

#endif 