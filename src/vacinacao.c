#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/vacinacao.h"

void vacinar(TipoFila *fila, TipoFila *filaDestino, TipoLista *listaDeVacinados, MYSQL *conexao)
{
    if (fila->primeiro == NULL)
    {
        printf("\n\t!!! Não há nenhum cidadão na Fila de Vacinação !!!\n");
        return;
    }

    char grupoPrioritario[13];
    switch (fila->primeiro->cidadao.grupoPrioritario)
    {
    case 1:
        strcpy(grupoPrioritario, "Comorbidades");
        break;

    default:
        strcpy(grupoPrioritario, "Não Consta");
        break;
    }

    printf("\t<<< VacinaMe - Vacinação >>>\n\n");
    printf(" > Cidadão: %s\n", fila->primeiro->cidadao.nome);
    printf(" > CPF: %s\n", fila->primeiro->cidadao.cpf);
    printf(" > Email: %s\n", fila->primeiro->cidadao.email);
    printf(" > Grupo: %s\n", grupoPrioritario);
    printf(" > Idade: %d\n\n", fila->primeiro->cidadao.idade);

    int opcao = 0;

    do
    {
        if (fila->primeiro->cidadao.statusVacinacao == 0)
        {
            /* SE É 0 SE TRATA DA PRIMEIRA DOSE */
            printf(" -> Qual vacina o cidadão vai tomar?\n\n");
            printf("1) CORONAVAC (BUTANTAN/SINOVAC).\n");
            printf("2) COVISHIELD (OXFORD/ASTRAZENECA).\n");
            printf("3) PFIZER VACCINE (PFIZER/BIONTECH).\n");
            printf("4) JANSSEN VACCINE (JANSSEN).\n"); /*unica que é somente uma dose*/
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
                printf("\n !!! O Cidadão Precisará Receber Segunda Dose !!!\n");
                printf("\n     !!! Vacinação Realizada com Sucesso !!!\n");
                opcao = 0;
                removeDaFila(fila);
                break;
            case 2:
                fila->primeiro->cidadao.codigoVacina = 2;
                fila->primeiro->cidadao.statusVacinacao = 1;
                atualizarCodigoVacina(conexao, fila->primeiro->cidadao.cpf, 2);
                atualizarStatusVacinacao(conexao, fila->primeiro->cidadao.cpf, 1);
                insereNaFila(filaDestino, fila->primeiro->cidadao);
                printf("\n !!! O Cidadão Precisará Receber Segunda Dose !!!\n");
                printf("\n     !!! Vacinação Realizada com Sucesso !!!\n");
                opcao = 0;
                removeDaFila(fila);
                break;
            case 3:
                fila->primeiro->cidadao.codigoVacina = 3;
                fila->primeiro->cidadao.statusVacinacao = 1;
                atualizarCodigoVacina(conexao, fila->primeiro->cidadao.cpf, 3);
                atualizarStatusVacinacao(conexao, fila->primeiro->cidadao.cpf, 1);
                insereNaFila(filaDestino, fila->primeiro->cidadao);
                printf("\n !!! O Cidadão Precisará Receber Segunda Dose !!!\n");
                printf("\n     !!! Vacinação Realizada com Sucesso !!!\n");
                opcao = 0;
                removeDaFila(fila);
                break;
            case 4:
                fila->primeiro->cidadao.codigoVacina = 4;
                fila->primeiro->cidadao.statusVacinacao = 2;
                atualizarCodigoVacina(conexao, fila->primeiro->cidadao.cpf, 4);
                atualizarStatusVacinacao(conexao, fila->primeiro->cidadao.cpf, 2);
                insereListaFinal(listaDeVacinados, fila->primeiro->cidadao);
                printf("\n     !!! Vacinação Realizada com Sucesso !!!\n");
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
            printf(" !!! O Cidadão deve receber a Segunda Dose da ");
            if (fila->primeiro->cidadao.codigoVacina == 1)
            {
                printf("CORONAVAC !!!\n\n");
            }
            if (fila->primeiro->cidadao.codigoVacina == 2)
            {
                printf("COVISHIELD !!!\n\n");
            }
            if (fila->primeiro->cidadao.codigoVacina == 3)
            {
                printf("PFIZER VACCINE !!!\n\n");
            }

            printf(" -> Você confirma a aplicação?\n\n");
            printf("  1) SIM\n");
            printf("  0) NÃO\n\n");

            printf(" --> ");
            scanf("%d", &opcao);

            switch (opcao)
            {
            case 1:
                atualizarStatusVacinacao(conexao, fila->primeiro->cidadao.cpf, 2);
                printf("\n     !!! Vacinação Realizada com Sucesso !!!\n");
                insereListaFinal(listaDeVacinados, fila->primeiro->cidadao);
                removeDaFila(fila);
                opcao = 0;
                break;
            default:
                break;
            }
        }

    } while (opcao != 0);

    return;
}
