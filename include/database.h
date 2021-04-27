#include <windows.h>
#include <winsock2.h>
#include <C:\conectorC\include/mysql.h>

#ifndef DATABASE_H
#define DATABASE_H

MYSQL *__stdcall obterConexao();
void inserirNovoCidadao(MYSQL *conexao, char *nome, char *email, char *cpf, int idade);
void atualizarStatusVacinacao(MYSQL *conexao, char *cpf, int status);
void atualizarCodigoVacina(MYSQL *conexao, char *cpf, int codigo);
void apagarDadosCidadao(MYSQL *conexao, char *cpf);
void obterListaCidadaos(MYSQL *conexao);

#endif