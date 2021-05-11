#include <stdlib.h>
#include <stdio.h>
#include "../include/consulta.h"
#include "../include/lista.h"

int consultarIdadeMinima() {
    int idadeMinima;

    printf(" -> Informe a Idade Mínima para consulta: ");
    scanf("%d", &idadeMinima);

    return idadeMinima;
}

void consultarListaDeEsperaPorIdade(MYSQL *conexao, TipoLista *lista)
{

    printf("\t<<< VacinaMe - Consulta de Lista de Espera >>>\n\n");
    resetarLista(lista);
    obterListaCidadaosPorIdadeEStatusDaVacinacao(conexao, lista, consultarIdadeMinima(), 0);
}

void consultarListaDeVacinadosComPrimeiraDosePorIdade(MYSQL *conexao, TipoLista *lista)
{

    printf("\t<<< VacinaMe - Consulta de Vacinados com Primeira Dose >>>\n\n");
    resetarLista(lista);
    obterListaCidadaosPorIdadeEStatusDaVacinacao(conexao, lista, consultarIdadeMinima(), 1);
}

void consultarListaDeVacinadosPorIdade(MYSQL *conexao, TipoLista *lista)
{

    printf("\t<<< VacinaMe - Consulta de Vacinados >>>\n\n");
    resetarLista(lista);
    obterListaCidadaosPorIdadeEStatusDaVacinacao(conexao, lista, consultarIdadeMinima(), 2);
}