#include "fila_de_vacinacao.h"
#include "lista_de_espera.h"

#ifndef FUNCOES_AUXILIARES_H
#define FUNCOES_AUXILIARES_H

void procuraVacinados(TipoFila *fila, TipoLista *ListaDeVacinados);
void removeDaFilaPraLista(TipoFila *fila, TipoLista *listaDeVacinados);
void vacinarPrimeiraPessoa(TipoFila *fila, TipoFila *filaDestino, TipoLista *listaDeVacinados);

#endif