#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/ordenacao.h"

void mergeSort(Cidadao *vetor, int inicio, int final)
{
    if (inicio == final)
        return;

    int metade = (inicio + final) / 2;
    mergeSort(vetor, inicio, metade);
    mergeSort(vetor, metade + 1, final);

    int i, j, posicaoAuxiliar = 0;
    int tamanhoAuxiliar = (final - inicio) + 1;
    Cidadao *vetorAuxiliar = (Cidadao *)malloc(tamanhoAuxiliar * sizeof(Cidadao));

    for (i = inicio, j = metade + 1; posicaoAuxiliar < tamanhoAuxiliar; posicaoAuxiliar++)
    {
        if (i > metade)
        {
            vetorAuxiliar[posicaoAuxiliar] = vetor[j];
            j++;
        }
        else
        {
            if (j > final)
            {
                vetorAuxiliar[posicaoAuxiliar] = vetor[i];
                i++;
            }
            else
            {
                if (vetor[i].idade > vetor[j].idade)
                {
                    vetorAuxiliar[posicaoAuxiliar] = vetor[i];
                    i++;
                }
                else
                {
                    vetorAuxiliar[posicaoAuxiliar] = vetor[j];
                    j++;
                }
            }
        }
    }

    for (i = inicio, posicaoAuxiliar = 0; posicaoAuxiliar < tamanhoAuxiliar; posicaoAuxiliar++)
    {
        vetor[i] = vetorAuxiliar[posicaoAuxiliar];
        i++;
    }

    free(vetorAuxiliar);
}

void ordenaLista(TipoLista *lista)
{
    int tamanho = lista->quantidade;

    if (tamanho == 0)
    {
        printf("\t!!! LISTA VAZIA! NÃO HÁ DADOS PARA ORDENAR !!!\n\n");
        system("pause");
        system("cls");
        return;
    }

    Cidadao *vetorOrdenar = (Cidadao *)malloc(lista->quantidade * sizeof(Cidadao));
    TipoMembroLista *atual = lista->primeiro;
    int i;

    for (i = 0; atual != NULL; i++)
    {
        vetorOrdenar[i] = atual->cidadao;
        atual = atual->proximo;
    }

    printf("\t\t-> ORDENANDO LISTA PELO MÉTODO MERGE SORT, AGUARDE UM INSTANTE...\n\n");
    mergeSort(vetorOrdenar, 0, lista->quantidade - 1);
    resetarLista(lista);

    for (i = 0; i < tamanho; i++)
    {
        insereListaFinal(lista, vetorOrdenar[i]);
    }

    printf("A LISTA FOI ORDENADO COM SUCESSO !!!\n\n");
    system("pause");
    system("cls");

    free(vetorOrdenar);
}

void converteListaParaFila(TipoLista *lista, TipoFila *fila)
{
    TipoMembroLista *atual = lista->primeiro;
    resetarFila(fila);

    while (atual != NULL)
    {
        insereNaFila(fila, atual->cidadao);
        atual = atual->proximo;
    }
}