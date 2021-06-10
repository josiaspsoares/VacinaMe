#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/fila.h"

TipoFila *iniciaFila()
{
    TipoFila *novaFila = (TipoFila *)malloc(sizeof(TipoFila));

    if (novaFila != NULL)
    {
        novaFila->primeiro = NULL;
        novaFila->ultimo = NULL;
        novaFila->quantidade = 0;
        return novaFila;
    }

    printf("\nErro: Não foi possível alocar memória para a Fila!\n");
    return NULL;
}

void liberaFila(TipoFila *fila)
{
    if (fila != NULL)
    {

        while (fila->primeiro != NULL)
        {
            TipoMembroFila *membroAuxiliar;
            membroAuxiliar = fila->primeiro;
            fila->primeiro = fila->primeiro->deTras;
            free(membroAuxiliar);
        }

        free(fila);
    }
}

void resetarFila(TipoFila *fila)
{
    liberaFila(fila);
    fila = iniciaFila();
}

void insereNaFila(TipoFila *fila, Cidadao dadosCidadao)
{
    TipoMembroFila *novoMembro = (TipoMembroFila *)malloc(sizeof(TipoMembroFila));
    if (novoMembro == NULL)
    {
        return;
    }

    novoMembro->cidadao = dadosCidadao;
    if (fila->primeiro == NULL)
    {
        fila->primeiro = novoMembro;
        novoMembro->daFrente = NULL;
    }
    else
    {
        novoMembro->daFrente = fila->ultimo;
        fila->ultimo->deTras = novoMembro;
    }

    novoMembro->deTras = NULL;
    fila->ultimo = novoMembro;
    fila->quantidade++;
}

void removeDaFila(TipoFila *fila)
{

    if (fila->primeiro == NULL)
    {
        printf("Fila vazia!\n");
        return;
    }

    TipoMembroFila *membroAuxiliar = fila->primeiro;
    fila->primeiro = fila->primeiro->deTras;

    if (fila->primeiro == NULL)
    {
        fila->ultimo = NULL;
    }
    else
    {
        fila->primeiro->daFrente = NULL;
    }

    fila->quantidade--;
    free(membroAuxiliar);
    return;
}

void exibeFila(TipoFila *Fila)
{
    if (Fila->quantidade == 0)
    {
        printf("\n\t!!! Não há nenhum cidadão nesta Fila !!!\n");
        return;
    }

    TipoMembroFila *membroAuxiliar = Fila->primeiro;
    char nomeVacina[14];

    printf(" IDADE\t  NOME\t\t\t\t\t\t CPF\t       EMAIL\t\t\t      VACINA\n");
    while (membroAuxiliar != NULL)
    {
        switch (membroAuxiliar->cidadao.codigoVacina)
        {
        case 1:
            strcpy(nomeVacina, "Coronavac");
            break;
        case 2:
            strcpy(nomeVacina, "Covishield");
            break;
        case 3:
            strcpy(nomeVacina, "Pfizer");
            break;
        case 4:
            strcpy(nomeVacina, "Janssen");
            break;
        default:
            strcpy(nomeVacina, "Não Vacinado");
            break;
        }

        printf("\n %-4d     %-45s  %-12s  %-30s %-14s", membroAuxiliar->cidadao.idade, membroAuxiliar->cidadao.nome, membroAuxiliar->cidadao.cpf, membroAuxiliar->cidadao.email, nomeVacina);
        membroAuxiliar = membroAuxiliar->deTras;
    }
}