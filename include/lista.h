#include "cidadao.h"

#ifndef LISTA_DE_ESPERA_H
#define LISTA_DE_ESPERA_H

typedef struct MembroLista
{
    Cidadao cidadao;
    struct MembroLista *anterior;
    struct MembroLista *proximo;
} TipoMembroLista;

typedef struct Lista
{
    int quantidade;
    TipoMembroLista *primeiro;
    TipoMembroLista *ultimo;
} TipoLista;

TipoLista *criaLista();
void exibeLista(TipoLista *listaDeEspera);
void liberaLista(TipoLista *lista);
void resetarLista(TipoLista *lista);
int insereListaFinal(TipoLista *lista, Cidadao dadosCidadao);
int removeListaFinal(TipoLista *lista);

#endif