#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/lista_de_espera.h"

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
        lista->ultimo = novoMembro;
    }
    else
    {
        novoMembro->proximo = lista->primeiro;
        lista->primeiro->anterior = novoMembro;
        lista->primeiro = novoMembro;
    }

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
    while (membroAuxiliar != NULL)
    {
        printf("\n%d %s %s %s", membroAuxiliar->cidadao.idade, membroAuxiliar->cidadao.nome, membroAuxiliar->cidadao.cpf, membroAuxiliar->cidadao.email);
        membroAuxiliar = membroAuxiliar->proximo;
    }
}

void lerDados(TipoLista *lista, char *filepath)
{
    FILE *arquivo;
    int idade;
    char nome[100], cpf[12], email[100];
    Cidadao dadosCidadao;

    arquivo = fopen(filepath, "r");

    while (!feof(arquivo))
    {
        fscanf(arquivo, "%d %s %11s %99[^\n]\n", &idade, email, cpf, nome);
        printf("\n%d %s %s %s", idade, nome, cpf, email);

        dadosCidadao.idade = idade;
        strcpy(dadosCidadao.email, email);
        strcpy(dadosCidadao.cpf, cpf);
        strcpy(dadosCidadao.nome, nome);
        insereListaFinal(lista, dadosCidadao);
    }

    fclose(arquivo);
    exibeLista(lista);
}