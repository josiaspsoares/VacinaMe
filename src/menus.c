#include <stdlib.h>
#include <stdio.h>
#include "../include/menus.h"
#include "../include/ordenacao.h"
#include "../include/vacinacao.h"
#include "../include/consulta.h"

void menuVacinacao(TipoLista *listaDeEspera, TipoFila *filaPrioridade, TipoFila *filaPrioridadeDose2, TipoFila *filaDeVacinacao, TipoFila *filaDeVacinacaoDose2, TipoLista *listaDeVacinados, MYSQL *conexao)
{
    int opcao = 0;

    do
    {
        system("cls");
        printf("\t<<< VacinaMe - Vacinação >>>\n\n");
        printf("1) Vacinar - 1ª DOSE - IDADE\n");
        printf("2) Vacinar - 2ª DOSE - IDADE\n");
        printf("3) Vacinar - 1ª DOSE - GRUPOS PRIORITÁRIOS\n");
        printf("4) Vacinar - 2ª DOSE - GRUPOS PRIORITÁRIOS\n");
        printf("0) Sair.\n\n");

        printf("---> OPÇÃO: ");
        scanf("%d", &opcao);
        system("cls");

        switch (opcao)
        {
        case 1:
            vacinar(filaDeVacinacao, filaDeVacinacaoDose2, listaDeVacinados, conexao);
            break;
        case 2:
            vacinar(filaDeVacinacaoDose2, NULL, listaDeVacinados, conexao);
            break;
        case 3:
            vacinar(filaPrioridade, filaDeVacinacaoDose2, listaDeVacinados, conexao);
            break;
        case 4:
            vacinar(filaPrioridadeDose2, NULL, listaDeVacinados, conexao);
            break;
        default:
            continue;
        }

        printf("\n\n");
        system("pause");
    } while (opcao != 0);
}

void menuExibicao(TipoLista *listaDeEspera, TipoFila *filaPrioridade, TipoFila *filaPrioridadeDose2, TipoFila *filaDeVacinacao, TipoFila *filaDeVacinacaoDose2, TipoLista *listaDeVacinados, MYSQL *conexao)
{
    int opcao = 0;

    do
    {
        system("cls");
        printf("\t<<< VacinaMe - Exibição de Dados >>>\n\n");
        printf("1) Lista de Espera - IDADE\n");
        printf("2) Lista de Espera - GRUPOS PRIORITÁRIOS\n");
        printf("3) Fila de Vacinação - 1ª DOSE - IDADE\n");
        printf("4) Fila de Vacinação - 2ª DOSE - IDADE\n");
        printf("5) Fila de Vacinação - 1ª DOSE - GRUPOS PRIORITÁRIOS\n");
        printf("6) Fila de Vacinação - 2ª DOSE - GRUPOS PRIORITÁRIOS\n");
        printf("7) Lista de Imunizados - IDADE\n");
        printf("8) Lista de Imunizados - GRUPOS PRIORITÁRIOS\n");
        printf("0) Sair.\n\n");

        printf("---> OPÇÃO: ");
        scanf("%d", &opcao);
        system("cls");

        switch (opcao)
        {
        case 1:
            consultarListaDeEsperaPorIdade(conexao, listaDeEspera);
            system("cls");
            exibeLista(listaDeEspera);
            break;
        case 2:
            consultarListaDeEsperaPorPrioridade(conexao, listaDeEspera);
            system("cls");
            exibeLista(listaDeEspera);
            break;
        case 3:
            exibeFila(filaDeVacinacao);
            break;
        case 4:
            exibeFila(filaDeVacinacaoDose2);
            break;
        case 5:
            exibeFila(filaPrioridade);
            break;
        case 6:
            exibeFila(filaPrioridadeDose2);
            break;
        case 7:
            consultarListaDeVacinadosPorIdade(conexao, listaDeVacinados);
            system("cls");
            exibeLista(listaDeVacinados);
            break;
        case 8:
            consultarListaDeVacinadosPorPrioridade(conexao, listaDeVacinados);
            system("cls");
            exibeLista(listaDeVacinados);
            break;
        default:
            continue;
        }

        printf("\n\n");
        system("pause");
    } while (opcao != 0);
}

void menuGerenciamento(TipoLista *listaDeEspera, TipoFila *filaPrioridade, TipoFila *filaPrioridadeDose2, TipoLista *listaPrioridade, TipoFila *filaDeVacinacao, TipoFila *filaDeVacinacaoDose2, TipoLista *listaDeVacinados, MYSQL *conexao)
{
    int opcao = 0;

    do
    {
        system("cls");
        printf("\t<<< VacinaMe - Gerenciamento >>>\n\n");
        printf("1) Gerar Fila de Vacinação - 1ª DOSE - IDADE\n");
        printf("2) Gerar Fila de Vacinação - 2ª DOSE - IDADE\n");
        printf("3) Gerar Fila de Vacinação - 1ª DOSE - GRUPOS PRIORITÁRIOS\n");
        printf("4) Gerar Fila de Vacinação - 2ª DOSE - GRUPOS PRIORITÁRIOS\n");
        printf("0) Sair.\n\n");

        printf("---> OPÇÃO: ");
        scanf("%d", &opcao);
        system("cls");

        switch (opcao)
        {
        case 1:
            consultarListaDeEsperaPorIdade(conexao, listaDeEspera);
            system("cls");
            ordenaLista(listaDeEspera);
            converteListaParaFila(listaDeEspera, filaDeVacinacao);
            break;
        case 2:
            consultarListaDeVacinadosComPrimeiraDosePorIdade(conexao, listaDeEspera);
            system("cls");
            ordenaLista(listaDeEspera);
            converteListaParaFila(listaDeEspera, filaDeVacinacaoDose2);
            break;
        case 3:
            consultarListaDeEsperaPorIdade(conexao, listaDeEspera);
            system("cls");
            criarListaPrioridade(listaDeEspera, listaPrioridade);
            ordenaLista(listaPrioridade);
            converteListaParaFila(listaPrioridade, filaPrioridade);
            break;
        case 4:
            consultarListaDeVacinadosComPrimeiraDosePorIdade(conexao, listaDeEspera);
            system("cls");
            criarListaPrioridade(listaDeEspera, listaPrioridade);
            ordenaLista(listaPrioridade);
            converteListaParaFila(listaPrioridade, filaPrioridadeDose2);
            break;
        default:
            continue;
        }

    } while (opcao != 0);
}

void menu(TipoLista *listaDeEspera, TipoFila *filaPrioridade, TipoFila *filaPrioridadeDose2, TipoLista *listaPrioridade, TipoFila *filaDeVacinacao, TipoFila *filaDeVacinacaoDose2, TipoLista *listaDeVacinados, MYSQL *conexao)
{
    int opcao = 0;

    do
    {
        system("cls");
        printf("\t<<< VacinaMe - Gerenciador de Vacinação >>>\n\n");
        printf("1) Consulta de Dados\n");
        printf("2) Vacinação\n");
        printf("3) Gerenciamento\n");
        printf("0) Sair.\n\n");

        printf("---> OPÇÃO: ");
        scanf("%d", &opcao);
        system("cls");

        switch (opcao)
        {
        case 1:
            menuExibicao(listaDeEspera, filaPrioridade, filaPrioridadeDose2, filaDeVacinacao, filaDeVacinacaoDose2, listaDeVacinados, conexao);
            break;
        case 2:
            menuVacinacao(listaDeEspera, filaPrioridade, filaPrioridadeDose2, filaDeVacinacao, filaDeVacinacaoDose2, listaDeVacinados, conexao);
            break;
        case 3:
            menuGerenciamento(listaDeEspera, filaPrioridade, filaPrioridadeDose2, listaPrioridade, filaDeVacinacao, filaDeVacinacaoDose2, listaDeVacinados, conexao);
            break;
        default:
            continue;
        }

    } while (opcao != 0);
}