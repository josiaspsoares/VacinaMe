#ifndef CIDADAO_H
#define CIDADAO_H

typedef struct Cidadao {
    char nome[100];
    char email[100];
    char cpf[12];
    int idade;
    char pertenceGrupoDeRisco;
    char recebeuVacina;
}Cidadao;

#endif 