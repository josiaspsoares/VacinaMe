#include "fila.h"
#include "lista.h"
#include "../include/database.h"

#ifndef MENUS_H
#define MENUS_H

void menu(TipoLista *listaDeEspera, TipoFila *filaDeVacinacao, TipoFila *filaDeVacinacaoDose2, TipoLista *listaDeVacinados, MYSQL *conexao);

#endif