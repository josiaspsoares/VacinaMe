#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/fila_de_vacinacao.h"
#include "../include/lista_de_espera.h"

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

void vacinarPrimeiraPessoa(TipoFila *fila, TipoFila *filaDestino, TipoLista *listaDeVacinados)
{
    if (fila->primeiro == NULL)
    {
        printf("Fila vazia!\n");
        return;
    }
    printf("Vacinando o cidadão %s. \n\n", fila->primeiro->cidadao.nome);
    int op = 0;

    do
    {
        if (fila->primeiro->cidadao.statusVacina == 0)
        { /* SE É 0 SE TRATA DA PRIMEIRA DOSE */
            printf("Qual vacina o cidadão vai tomar?\n\n");
            printf("1) CORONAVAC.\n");
            printf("2) PFIZER.\n");
            printf("3) JANSEN.\n"); /*unica que é somente uma dose*/
            printf("0) Sair.\n\n");

            scanf("%d", &op);

            switch (op)
            {
            case 1:
                fila->primeiro->cidadao.codigoVacina = 1;
                fila->primeiro->cidadao.statusVacina = 1;
                insereNaFila(filaDestino, fila->primeiro->cidadao);
                op = 0;
                removeDaFila(fila);
                break;
            case 2:
                fila->primeiro->cidadao.codigoVacina = 2;
                fila->primeiro->cidadao.statusVacina = 1;
                insereNaFila(filaDestino, fila->primeiro->cidadao);
                op = 0;
                removeDaFila(fila);
                break;
            case 3:
                fila->primeiro->cidadao.codigoVacina = 3;
                fila->primeiro->cidadao.statusVacina = 2;
                insereListaFinal(listaDeVacinados, fila->primeiro->cidadao);
                op = 0;
                removeDaFila(fila);
                break;
            default:
                printf("Opção inválida.\n\n");
                break;
            }
        }
        else if (fila->primeiro->cidadao.statusVacina == 1)
        { /* SE É 1 SE TRATA DA SEGUNDA DOSE */
            if (fila->primeiro->cidadao.codigoVacina == 1)
            {
                printf("\nSegunda dose da CoronaVac.\n\n");
            }
            if (fila->primeiro->cidadao.codigoVacina == 2)
            {
                printf("\nSegunda dose da Pfizer.\n\n");
            }
            insereListaFinal(listaDeVacinados, fila->primeiro->cidadao);
            removeDaFila(fila);
        }

        system("pause");
        system("cls");

    } while (op != 0);

    return;
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
        printf("Fila vazia.\n");
    }
    TipoMembroFila *membroAuxiliar = Fila->primeiro;
    while (membroAuxiliar != NULL)
    {
        printf("\n%d %s %s %s", membroAuxiliar->cidadao.idade, membroAuxiliar->cidadao.nome, membroAuxiliar->cidadao.cpf, membroAuxiliar->cidadao.email);
        membroAuxiliar = membroAuxiliar->deTras;
    }
}

void preencheFila(TipoFila *filaDeVacinacao, TipoFila *filaDeVacinacao2, char *filepath)
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
        if (statusVacina == 0)
        {
            strcpy(dadosCidadao.email, email);
            strcpy(dadosCidadao.cpf, cpf);
            strcpy(dadosCidadao.nome, nome);
            dadosCidadao.idade = idade;
            dadosCidadao.statusVacina = statusVacina;  /* 0 não tomou vacina, 1 tomou uma dose, 2 está imunizado */
            dadosCidadao.codigoVacina = codigoVacina;  /* 0 sem nenhum, 1 coronaVac, 2 Pfizer, 3 Jansen */
            dadosCidadao.pertenceGrupoDeRisco = risco; /* 0 sem risco, 1 com risco */
            insereNaFila(filaDeVacinacao, dadosCidadao);
        }

        if (statusVacina == 1)
        {
            strcpy(dadosCidadao.email, email);
            strcpy(dadosCidadao.cpf, cpf);
            strcpy(dadosCidadao.nome, nome);
            dadosCidadao.idade = idade;
            dadosCidadao.statusVacina = statusVacina;  /* 0 não tomou vacina, 1 tomou uma dose, 2 está imunizado */
            dadosCidadao.codigoVacina = codigoVacina;  /* 0 sem nenhum, 1 coronaVac, 2 Pfizer, 3 Jansen */
            dadosCidadao.pertenceGrupoDeRisco = risco; /* 0 sem risco, 1 com risco */
            insereNaFila(filaDeVacinacao2, dadosCidadao);
        }
        i++;
    }

    fclose(fp);
}

void exibeFilaDeVacinacao(TipoFila *fila)
{
    TipoMembroFila *aux;

    aux = fila->primeiro;

    while (aux->deTras != NULL)
    {
        printf("\n%d %s %s %s", aux->cidadao.idade, aux->cidadao.nome, aux->cidadao.cpf, aux->cidadao.email);
        aux = aux->deTras;
    }
}