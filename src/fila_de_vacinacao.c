#include<stdio.h>
#include<stdlib.h>
#include "../include/fila_de_vacinacao.h"

TipoFila *iniciaFila(){
	TipoFila *novaFila = (TipoFila *)malloc(sizeof(TipoFila));

	if(novaFila != NULL){
        novaFila->primeiro = NULL;
        novaFila->ultimo = NULL;
        novaFila->quantidade = 0;
        return novaFila;
    }
    
    printf("\nErro: Não foi possível alocar memória para a Fila!\n");
    return NULL;
}

void liberaFila(TipoFila *fila){
    if(fila != NULL){

        while(fila->primeiro != NULL){
            TipoMembroFila *membroAuxiliar;
            membroAuxiliar = fila->primeiro;
            fila->primeiro = fila->primeiro->deTras;
            free(membroAuxiliar);
        }

        free(fila);
    }
}

void insereNaFila(TipoFila *fila){
	TipoMembroFila *novoMembro = (TipoMembroFila *)malloc(sizeof(TipoMembroFila));
	if(novoMembro == NULL){
        return;
    }

	if(fila->primeiro == NULL){
		fila->primeiro = novoMembro;
		novoMembro->daFrente = NULL;
	}
	else{
		novoMembro->daFrente = fila->ultimo;
		fila->ultimo->deTras = novoMembro;
	}

	novoMembro->deTras = NULL;
	fila->ultimo = novoMembro;
	fila->quantidade++;
}

void removeDaFila(TipoFila *fila){
	if(fila->primeiro == NULL){
		printf("Fila vazia!\n");
		return;
	}

	TipoMembroFila *membroAuxiliar = fila->primeiro;
    fila->primeiro = fila->primeiro->deTras;
	fila->primeiro->daFrente = NULL;

    if(fila->primeiro == NULL){
        fila->ultimo = NULL;
    }

	fila->quantidade--;
    free(membroAuxiliar);
    return;
}