#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/lista_de_espera.h"
#define MAX_NOMES 500

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
    while (membroAuxiliar != NULL)
    {
        printf("\n%d %s %s %s", membroAuxiliar->cidadao.idade, membroAuxiliar->cidadao.nome, membroAuxiliar->cidadao.cpf, membroAuxiliar->cidadao.email);
        membroAuxiliar = membroAuxiliar->proximo;
    }
}

void lerDados(TipoLista *lista, char *filepath)
{
    FILE *fp;
    int idade, statusVacina, risco, codigoVacina;
    int i = 0;
    char nome[100], cpf[13], email[100];
    Cidadao dadosCidadao;
    fp = fopen(filepath, "r");

    while (!feof(fp))
    {
        fflush(stdin);
        fscanf(fp, "%d %d %d %d %s %11s %99[^\n]", &risco, &statusVacina, &codigoVacina, &idade, email, cpf, nome);
        strcpy(dadosCidadao.email, email);
        strcpy(dadosCidadao.cpf, cpf);
        strcpy(dadosCidadao.nome, nome);
        dadosCidadao.idade = idade;
        dadosCidadao.statusVacina = statusVacina;  /* 0 não tomou vacina, 1 tomou uma dose, 2 está imunizado */
        dadosCidadao.codigoVacina = codigoVacina;  /* 0 sem nenhum, 1 coronaVac, 2 Pfizer, 3 Jansen */
        dadosCidadao.pertenceGrupoDeRisco = risco; /* 0 sem risco, 1 com risco */
        insereListaFinal(lista, dadosCidadao);
        i++;
    }

    fclose(fp);
}

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
                if (vetor[i].idade < vetor[j].idade)
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

    Cidadao *vetorOrdenar = (Cidadao *)malloc(lista->quantidade * sizeof(Cidadao));
    TipoMembroLista *atual;
    int i;

    printf("\t\t-> ORDENANDO O ARQUIVO PELO MÉTODO MERGE SORT, AGUARDE UM INSTANTE...\n\n");

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
        atual->cidadao = vetorOrdenar[i];
        atual = atual->proximo;
    }

    printf("O ARQUIVO FOI ORDENADO COM SUCESSO !!!\n\n");
    system("pause");
    system("cls");

    free(vetorOrdenar);
}