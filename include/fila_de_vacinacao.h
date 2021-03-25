#include "cidadao.h"

#ifndef FILA_DE_VACINACAO_H
#define FILA_DE_VACINACAO_H

typedef struct MembroFila
{
	Cidadao cidadao;
	struct MembroFila *daFrente;
	struct MembroFila *deTras;
} TipoMembroFila;

typedef struct Fila
{
	int quantidade;
	TipoMembroFila *primeiro;
	TipoMembroFila *ultimo;
} TipoFila;

TipoFila *iniciaFila();
void liberaFila(TipoFila *fila);
void insereNaFila(TipoFila *fila);
void removeDaFila(TipoFila *fila);

#endif