#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <C:\conectorC\include/mysql.h>
#include "../include/database.h"

void erro(MYSQL *conexao)
{
    fprintf(stderr, "\n%s\n", mysql_error(conexao));
    mysql_close(conexao);
    exit(1);
}

MYSQL *__stdcall obterConexao()
{
    char *servidor = "88.211.101.190";
    char *usuario = "ivwundbr_vaciname";
    char *senha = "rcAylIfCW8";
    char *nomeBanco = "ivwundbr_vaciname";

    MYSQL *conexao = mysql_init(NULL);

    if (!mysql_real_connect(conexao, servidor, usuario, senha, nomeBanco, 0, NULL, 0))
    {
        erro(conexao);
    }
    else
    {
        printf("\nConexao realizada com sucesso!\n");
        return conexao;
    }

    return NULL;
}

void inserirNovoCidadao(MYSQL *conexao, char *nome, char *email, char *cpf, int idade)
{
    char query[250];
    sprintf(query, "INSERT INTO dados_cidadaos(nome, email, cpf, idade) VALUES('%s', '%s', '%s', '%d');", nome, email, cpf, idade);

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
    else
    {
        printf("\nDados inseridos com sucesso!\n");
    }
}

void obterListaCidadaos(MYSQL *conexao)
{
    MYSQL_RES *resultado;
    MYSQL_ROW row;

    if (mysql_query(conexao, "SELECT * FROM dados_cidadaos"))
    {
        erro(conexao);
    }

    resultado = mysql_store_result(conexao);
    if (resultado == NULL)
    {
        erro(conexao);
    }

    while ((row = mysql_fetch_row(resultado)) != NULL)
    {
        printf("\nNome: %s\n", row[0]);
        printf("E-mail: %s\n", row[1]);
        printf("CPF: %s\n", row[2]);
    }

    mysql_free_result(resultado);
}

void atualizarStatusVacinacao(MYSQL *conexao, char *cpf, int status)
{
    char query[100];
    sprintf(query, "UPDATE dados_cidadaos SET status_vacinacao = %d WHERE cpf = %s;", status, cpf);

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
    else
    {
        printf("\nDados atualizados com sucesso!\n");
    }
}

void atualizarCodigoVacina(MYSQL *conexao, char *cpf, int codigo)
{
    char query[100];
    sprintf(query, "UPDATE dados_cidadaos SET codigo_vacina = %d WHERE cpf = %s;", codigo, cpf);

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
    else
    {
        printf("\nDados atualizados com sucesso!\n");
    }
}

void apagarDadosCidadao(MYSQL *conexao, char *cpf)
{
    char query[100];
    sprintf(query, "DELETE FROM dados_cidadaos WHERE numero_conta = %s;", cpf);

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
    else
    {
        printf("\nDados apagados com sucesso!\n");
    }
}