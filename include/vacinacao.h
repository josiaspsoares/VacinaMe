#include "fila.h"
#include "lista.h"
#include "../include/database.h"

#ifndef VACINACAO_H
#define VACINACAO_H

void vacinar(TipoFila *fila, TipoFila *filaDestino, TipoLista *listaDeVacinados, MYSQL *conexao);

#endif

