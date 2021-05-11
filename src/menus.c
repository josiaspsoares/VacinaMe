#include <stdlib.h>
#include <stdio.h>
#include "../include/menus.h"
#include "../include/ordenacao.h"
#include "../include/vacinacao.h"
#include "../include/consulta.h"

void menuVacinacao(TipoLista *listaDeEspera, TipoFila *filaDeVacinacao, TipoFila *filaDeVacinacaoDose2, TipoLista *listaDeVacinados, MYSQL *conexao)
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
            // TODO: Implementar vacinação de cidadaos de grupos prioritários - 1ª DOSE
            break;
        case 4:
            // TODO: Implementar vacinação de cidadaos de grupos prioritários - 2ª DOSE
            break;
        default:
            continue;
        }

        printf("\n\n");
        system("pause");
    } while (opcao != 0);
}

void menuExibicao(TipoLista *listaDeEspera, TipoFila *filaDeVacinacao, TipoFila *filaDeVacinacaoDose2, TipoLista *listaDeVacinados, MYSQL *conexao)
{
    int opcao = 0;

    do
    {
        system("cls");
        printf("\t<<< VacinaMe - Exibição de Dados >>>\n\n");
        printf("1) Lista de Espera\n");
        printf("2) Fila de Vacinação - 1ª DOSE\n");
        printf("3) Fila de Vacinação - 2ª DOSE\n");
        printf("4) Fila de Vacinação - 1ª DOSE - GRUPOS PRIORITÁRIOS\n");
        printf("5) Fila de Vacinação - 2ª DOSE - GRUPOS PRIORITÁRIOS\n");
        printf("6) Lista de Imunizados\n");
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
            exibeFila(filaDeVacinacao);
            break;
        case 3:
            exibeFila(filaDeVacinacaoDose2);
            break;
        case 4:
            // TODO: Implementar exibição de cidadaos de grupos prioritários vacinados - 1ª DOSE
            break;
        case 5:
            // TODO: Implementar exibição de cidadaos de grupos prioritários vacinados - 2ª DOSE
            break;
        case 6:
            consultarListaDeVacinadosPorIdade(conexao, listaDeVacinados);
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

void menuGerenciamento(TipoLista *listaDeEspera, TipoFila *filaDeVacinacao, TipoFila *filaDeVacinacaoDose2, TipoLista *listaDeVacinados, MYSQL *conexao)
{
    int opcao = 0;

    do
    {
        system("cls");
        printf("\t<<< VacinaMe - Gerenciamento >>>\n\n");
        printf("1) Carregar Base de Dados\n");
        printf("2) Gerar Fila de Vacinação - IDADE\n");
        printf("3) Gerar Fila de Vacinação - GRUPOS PRIORITÁRIOS\n");
        printf("4) Restaurar Sistema\n");
        printf("0) Sair.\n\n");

        printf("---> OPÇÃO: ");
        scanf("%d", &opcao);
        system("cls");

        switch (opcao)
        {
        case 1:
            mockDados(conexao, "../data/dados_cidadaos.txt");
            break;
        case 2:
            consultarListaDeEsperaPorIdade(conexao, listaDeEspera);
            system("cls");
            ordenaLista(listaDeEspera);
            converteListaParaFila(listaDeEspera, filaDeVacinacao);
            consultarListaDeVacinadosComPrimeiraDosePorIdade(conexao, listaDeEspera);
            system("cls");
            ordenaLista(listaDeEspera);
            converteListaParaFila(listaDeEspera, filaDeVacinacaoDose2);
            break;
        case 3:
            // TODO: Implementar ordenação tendo como critério os grupos prioritários
            break;
        case 4:
            apagarTodosRegistros(conexao);
            break;
        default:
            continue;
        }

    } while (opcao != 0);
}

void menu(TipoLista *listaDeEspera, TipoFila *filaDeVacinacao, TipoFila *filaDeVacinacaoDose2, TipoLista *listaDeVacinados, MYSQL *conexao)
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
            menuExibicao(listaDeEspera, filaDeVacinacao, filaDeVacinacaoDose2, listaDeVacinados, conexao);
            break;
        case 2:
            menuVacinacao(listaDeEspera, filaDeVacinacao, filaDeVacinacaoDose2, listaDeVacinados, conexao);
            break;
        case 3:
            menuGerenciamento(listaDeEspera, filaDeVacinacao, filaDeVacinacaoDose2, listaDeVacinados, conexao);
            break;
        default:
            continue;
        }

    } while (opcao != 0);
}