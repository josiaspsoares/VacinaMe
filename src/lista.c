#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/lista.h"

TipoLista *criaLista()
{
    TipoLista *novaLista = (TipoLista *)malloc(sizeof(TipoLista));

    if (novaLista != NULL)
    {
        novaLista->primeiro = NULL;
        novaLista->ultimo = NULL;
        novaLista->quantidade = 0;
    }

    return novaLista;
}

void liberaLista(TipoLista *lista)
{
    if (lista != NULL)
    {

        while (lista->primeiro != NULL)
        {
            TipoMembroLista *membroAuxiliar;
            membroAuxiliar = lista->primeiro;
            lista->primeiro = lista->primeiro->proximo;
            free(membroAuxiliar);
        }

        free(lista);
    }
}

void resetarLista(TipoLista *lista)
{
    liberaLista(lista);
    lista = criaLista();
}

int listaVazia(TipoLista *lista)
{
    if (lista == NULL)
        return 1;
    if (lista->primeiro == NULL)
        return 1;
    return 0;
}

int insereListaInicio(TipoLista *lista, Cidadao dadosCidadao)
{
    if (lista == NULL)
        return 0;

    TipoMembroLista *novoMembro = (TipoMembroLista *)malloc(sizeof(TipoMembroLista));
    if (novoMembro == NULL)
        return 0;

    novoMembro->cidadao = dadosCidadao;

    if (listaVazia(lista))
    {
        lista->primeiro = novoMembro;
        lista->primeiro->anterior = NULL;
        lista->ultimo = novoMembro;
    }
    else
    {
        novoMembro->proximo = lista->primeiro;
        lista->primeiro->anterior = novoMembro;
        lista->primeiro = novoMembro;
    }
    lista->ultimo->proximo = NULL;
    lista->quantidade++;
    return 1;
}

int insereListaFinal(TipoLista *lista, Cidadao dadosCidadao)
{
    if (lista == NULL)
        return 0;

    TipoMembroLista *novoMembro = (TipoMembroLista *)malloc(sizeof(TipoMembroLista));
    if (novoMembro == NULL)
        return 0;

    novoMembro->cidadao = dadosCidadao;

    if (listaVazia(lista))
    {
        free(novoMembro);
        return insereListaInicio(lista, dadosCidadao);
    }
    else
    {
        lista->ultimo->proximo = novoMembro;
        novoMembro->anterior = lista->ultimo;
        lista->ultimo = novoMembro;
        lista->ultimo->proximo = NULL;
        lista->quantidade++;
        return 1;
    }
}

int removeListaInicio(TipoLista *lista)
{
    if (lista == NULL)
        return 0;
    if ((lista->primeiro) == NULL)
        return 0;

    TipoMembroLista *membroAuxiliar = lista->primeiro;
    lista->primeiro = membroAuxiliar->proximo;

    if (membroAuxiliar->proximo != NULL)
    {
        membroAuxiliar->proximo->anterior = NULL;
    }

    lista->quantidade--;
    free(membroAuxiliar);
    return 1;
}

int removeListaFinal(TipoLista *lista)
{
    if (lista == NULL)
        return 0;
    if ((lista->primeiro) == NULL)
        return 0;

    TipoMembroLista *membroAuxiliar = lista->ultimo;

    if (membroAuxiliar == lista->primeiro)
    {
        free(membroAuxiliar);
        return removeListaInicio(lista);
    }
    else
    {
        lista->ultimo->anterior->proximo = NULL;
        lista->ultimo = lista->ultimo->anterior;
        lista->quantidade--;
        free(membroAuxiliar);
        return 1;
    }
}

void exibeLista(TipoLista *lista)
{
    TipoMembroLista *membroAuxiliar = lista->primeiro;
    printf(" IDADE \tNOME\t\t\t\t\t\t CPF\t\tEMAIL\n");
    while (membroAuxiliar != NULL)
    {
        printf("\n %-4d     %-45s  %-12s  %-45s", membroAuxiliar->cidadao.idade, membroAuxiliar->cidadao.nome, membroAuxiliar->cidadao.cpf, membroAuxiliar->cidadao.email);
        membroAuxiliar = membroAuxiliar->proximo;
    }
}

