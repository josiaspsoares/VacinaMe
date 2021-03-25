#ifndef CIDADAO_H
#define CIDADAO_H

typedef struct Cidadao {
    char nome[100];
    char email[100];
    long int cpf;
    int idade;
    char isGrupoDeRisco;
}Cidadao;

#endif 