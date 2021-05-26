#include "fila.h"
#include "lista.h"
#include "../include/database.h"

#ifndef CONSULTA_H
#define CONSULTA_H

void consultarListaDeEsperaPorIdade(MYSQL *conexao, TipoLista *lista);
void consultarListaDeEsperaPorPrioridade(MYSQL *conexao, TipoLista *lista);
void consultarListaDeEsperaOrdenadaPorPrioridade(MYSQL *conexao, TipoLista *lista);
void consultarListaDeVacinadosComPrimeiraDosePorIdade(MYSQL *conexao, TipoLista *lista);
void consultarListaDeVacinadosPorIdade(MYSQL *conexao, TipoLista *lista);
void consultarListaDeVacinadosPorPrioridade(MYSQL *conexao, TipoLista *lista);

#endif