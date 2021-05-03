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

void ordenaLista(TipoLista *lista, TipoFila *fila)
{

    Cidadao *vetorOrdenar = (Cidadao *)malloc(lista->quantidade * sizeof(Cidadao));
    TipoMembroLista *atual;
    int i;

    printf("\t\t-> ORDENANDO LISTA DE ESPERA PELO MÉTODO MERGE SORT, AGUARDE UM INSTANTE...\n\n");

    atual = lista->primeiro;
    for (i = 0; atual != NULL; i++)
    {
        vetorOrdenar[i] = atual->cidadao;
        atual = atual->proximo;
    }

    mergeSort(vetorOrdenar, 0, lista->quantidade - 1);

    atual = lista->primeiro;
    for (i = 0; atual != NULL; i++)
    {
        insereNaFila(fila, vetorOrdenar[i]);
        atual = atual->proximo;
    }

    printf("A LISTA FOI ORDENADO COM SUCESSO !!!\n\n");
    system("pause");
    system("cls");

    free(vetorOrdenar);
}