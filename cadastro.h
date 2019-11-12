#ifndef CADASTRO_H
#define CADASTRO_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//<structinutil>
typedef struct {
    int tipo;
    char nome[30];
    char login[12];
    char senha[12];
} usuario;
//</structinutil>

int efetuarLogin(char* login, char* senha){
    FILE *usuarios;
    usuarios = fopen("usuarios.txt", "r");

    char flogin[12], fsenha[12];
    char flag;

    while(fscanf(usuarios, "%*[^\n]\n") != EOF){
        fscanf(usuarios, "%*[^\n]\n");
        fgets(flogin, 12, usuarios);
        fgets(fsenha, 12, usuarios);
        if(!strncmp(flogin, login, strlen(flogin) - 1) && !strncmp(fsenha, senha, strlen(fsenha) - 1)){
            return 1;
        }

    }

    fclose(usuarios);

    return 0;
}

bool cadastrarUsuario(int tipo, char* nome, char* login, char* senha){
    FILE *usuarios;
    usuarios = fopen("usuarios.txt", "a");

    fprintf(usuarios, "%i\n", tipo);
    fputs(nome, usuarios);
    fputs(login, usuarios);
    fputc('\n', usuarios);
    fputc('\n', usuarios);
    fputs(senha, usuarios);
    fputc('\n', usuarios);

    fclose(usuarios);

    return true;
}

bool alterarUsuario(char* nome, char* login, char* senha){
    FILE *usuarios;
    usuarios = fopen("usuarios.txt", "r+");

    while(fscanf(usuarios, "%*[^\n]\n") != EOF){
        
    }
}

#endif