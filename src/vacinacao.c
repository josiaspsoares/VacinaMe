#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/vacinacao.h"

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
        {
            /* SE É 0 SE TRATA DA PRIMEIRA DOSE */
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
        {
            /* SE É 1 SE TRATA DA SEGUNDA DOSE */
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