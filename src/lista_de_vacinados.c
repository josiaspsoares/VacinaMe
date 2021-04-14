#include "../include/fila_de_vacinacao.h"
#include "../include/lista_de_espera.h"
#include <stdlib.h>
#include <stdio.h>

void procuraVacinados(TipoFila *membrosDaFila, TipoLista *ListaDeVacinados)
{
    TipoMembroFila *proxFila;

    proxFila = membrosDaFila->primeiro;

    while (proxFila->deTras != NULL)
    {
        if (proxFila->cidadao.statusVacina == 1)
        {
            /*removeDaFilaPraLista(membrosDaFila,ListaDeVacinados);*/
        }
    }
}

void removeDaFila1(TipoFila *fila, TipoLista *ListaDeVacinados)
{
    if (fila->primeiro == NULL)
    {
        printf("Fila vazia!\n");
        return;
    }

    fila->primeiro = fila->primeiro->deTras;
    fila->primeiro->daFrente = NULL;

    if (fila->primeiro == NULL)
    {
        fila->ultimo = NULL;
    }

    fila->quantidade--;
    insereListaFinal(ListaDeVacinados, fila->ultimo->cidadao);
    return;
}