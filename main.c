#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include "include/fila_de_vacinacao.h"
#include "include/lista_de_espera.h"
#include "include/database.h"

void procuraVacinados(TipoFila *fila, TipoLista *ListaDeVacinados);
void removeDaFilaPraLista(TipoFila *fila, TipoLista *listaDeVacinados);
void vacinarPrimeiraPessoa(TipoFila *fila, TipoFila *filaDestino, TipoLista *listaDeVacinados);
void menu(TipoLista *listaDeEspera, TipoFila *filaDeVacinacao, TipoFila *filaDeVacinacaoDose2, TipoLista *listaDeVacinados);

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    SetConsoleOutputCP(65001);

    TipoLista *listaDeEspera = criaLista();
    TipoFila *filaDeVacinacao = iniciaFila();
    TipoFila *filaDeVacinacaoDose2 = iniciaFila();
    TipoLista *listaDeVacinados = criaLista();

    if (listaDeEspera == NULL || filaDeVacinacao == NULL)
    {
        printf("\nErro: Não foi possível alocar memória!\n");
        exit(1);
    }

    MYSQL *conexao = obterConexao();
    //inserirNovoCidadao(conexao, "Josias Soares", "aluno.josias.soares@doctum.edu.br", "51423612510", 19);
    //atualizarStatusVacinacao(conexao, "51423612510", 1);
    obterListaCidadaos(conexao);

    lerDados(listaDeEspera, "data/dados_cidadaos.txt");
    ordenaLista(listaDeEspera);

    insereNaFila(filaDeVacinacao, listaDeEspera->primeiro->cidadao);

    menu(listaDeEspera, filaDeVacinacao, filaDeVacinacaoDose2, listaDeVacinados);
    /*exibeLista(listaDeEspera); */

    liberaLista(listaDeEspera);
    liberaFila(filaDeVacinacao);
    return 0;
}

void menu(TipoLista *listaDeEspera, TipoFila *filaDeVacinacao, TipoFila *filaDeVacinacaoDose2, TipoLista *listaDeVacinados)
{
    int op = 0;

    do
    {
        printf("MENU\n\n");
        printf("1) Ver ordenação por idade.\n");
        printf("2) Ver fila de vacinação.\n");
        printf("3) Ver fila de vacinação dose 2.\n");
        printf("4) Ver lista de vacinados.\n");
        printf("5) Vacinar.\n");
        printf("6) Vacinar dose 2.\n");
        printf("0) Sair.\n\n");

        scanf("%d", &op);

        switch (op)
        {
        case 1:
            exibeLista(listaDeEspera);
            break;
        case 2:
            exibeFila(filaDeVacinacao);
            break;
        case 3:
            exibeFila(filaDeVacinacaoDose2);
            break;
        case 4:
            exibeLista(listaDeVacinados);
            break;
        case 5:
            vacinarPrimeiraPessoa(filaDeVacinacao, filaDeVacinacaoDose2, listaDeVacinados);
            break;
        case 6:
            vacinarPrimeiraPessoa(filaDeVacinacaoDose2, NULL, listaDeVacinados);
            break;
        default:
            printf("Opção inválida.\n\n");
        }

        printf("\n\n");
        system("pause");
        system("cls");
    } while (op != 0);
}