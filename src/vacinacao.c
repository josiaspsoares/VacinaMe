#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/vacinacao.h"

void vacinar(TipoFila *fila, TipoFila *filaDestino, TipoLista *listaDeVacinados, MYSQL *conexao)
{
    if (fila->primeiro == NULL)
    {
        printf("Fila vazia!\n");
        return;
    }
    printf("\n<<< Vacinando o cidadão %s >>>\n\n", fila->primeiro->cidadao.nome);
    int opcao = 0;

    do
    {
        if (fila->primeiro->cidadao.statusVacinacao == 0)
        {
            /* SE É 0 SE TRATA DA PRIMEIRA DOSE */
            printf("Qual vacina o cidadão vai tomar?\n\n");
            printf("1) CORONAVAC.\n");
            printf("2) PFIZER.\n");
            printf("3) JANSEN.\n"); /*unica que é somente uma dose*/
            printf("0) Sair.\n\n");

            printf(" --> ");
            scanf("%d", &opcao);

            switch (opcao)
            {
            case 1:
                fila->primeiro->cidadao.codigoVacina = 1;
                fila->primeiro->cidadao.statusVacinacao = 1;
                atualizarCodigoVacina(conexao, fila->primeiro->cidadao.cpf, 1);
                atualizarStatusVacinacao(conexao, fila->primeiro->cidadao.cpf, 1);
                insereNaFila(filaDestino, fila->primeiro->cidadao);
                opcao = 0;
                removeDaFila(fila);
                break;
            case 2:
                fila->primeiro->cidadao.codigoVacina = 2;
                fila->primeiro->cidadao.statusVacinacao = 1;
                atualizarCodigoVacina(conexao, fila->primeiro->cidadao.cpf, 2);
                atualizarStatusVacinacao(conexao, fila->primeiro->cidadao.cpf, 1);
                insereNaFila(filaDestino, fila->primeiro->cidadao);
                opcao = 0;
                removeDaFila(fila);
                break;
            case 3:
                fila->primeiro->cidadao.codigoVacina = 3;
                fila->primeiro->cidadao.statusVacinacao = 2;
                atualizarCodigoVacina(conexao, fila->primeiro->cidadao.cpf, 3);
                atualizarStatusVacinacao(conexao, fila->primeiro->cidadao.cpf, 2);
                insereListaFinal(listaDeVacinados, fila->primeiro->cidadao);
                opcao = 0;
                removeDaFila(fila);
                break;
            default:
                break;
            }
        }
        else if (fila->primeiro->cidadao.statusVacinacao == 1)
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

            atualizarStatusVacinacao(conexao, fila->primeiro->cidadao.cpf, 2);
            insereListaFinal(listaDeVacinados, fila->primeiro->cidadao);
            removeDaFila(fila);
        }

    } while (opcao != 0);

    return;
}

void preencheFila(TipoFila *filaDeVacinacao, TipoFila *filaDeVacinacao2, char *filepath)
{
    FILE *fp;
    int idade, statusVacinacao, risco, codigoVacina;
    int i = 0;
    char nome[100], cpf[13], email[100];
    Cidadao dadosCidadao;
    fp = fopen(filepath, "r");

    while (!feof(fp))
    {
        fflush(stdin);
        fscanf(fp, "%d %d %d %d %s %11s %99[^\n]", &risco, &statusVacinacao, &codigoVacina, &idade, email, cpf, nome);
        if (statusVacinacao == 0)
        {
            strcpy(dadosCidadao.email, email);
            strcpy(dadosCidadao.cpf, cpf);
            strcpy(dadosCidadao.nome, nome);
            dadosCidadao.idade = idade;
            dadosCidadao.statusVacinacao = statusVacinacao;  /* 0 não tomou vacina, 1 tomou uma dose, 2 está imunizado */
            dadosCidadao.codigoVacina = codigoVacina;  /* 0 sem nenhum, 1 coronaVac, 2 Pfizer, 3 Jansen */
            dadosCidadao.grupoPrioritario = risco; /* 0 sem risco, 1 com risco */
            insereNaFila(filaDeVacinacao, dadosCidadao);
        }

        if (statusVacinacao == 1)
        {
            strcpy(dadosCidadao.email, email);
            strcpy(dadosCidadao.cpf, cpf);
            strcpy(dadosCidadao.nome, nome);
            dadosCidadao.idade = idade;
            dadosCidadao.statusVacinacao = statusVacinacao;  /* 0 não tomou vacina, 1 tomou uma dose, 2 está imunizado */
            dadosCidadao.codigoVacina = codigoVacina;  /* 0 sem nenhum, 1 coronaVac, 2 Pfizer, 3 Jansen */
            dadosCidadao.grupoPrioritario = risco; /* 0 sem risco, 1 com risco */
            insereNaFila(filaDeVacinacao2, dadosCidadao);
        }
        i++;
    }

    fclose(fp);
}