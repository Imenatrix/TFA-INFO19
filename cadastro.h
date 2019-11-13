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
    usuarios = fopen("usuarios.bin", "r");

    usuario coiso;

    while(fread(&coiso, sizeof(coiso), 1, usuarios) < 1){
        fgets(fsenha, 12, usuarios);
        fscanf(usuarios, "%*[^\n]\n");
        fscanf(usuarios, "%*[^\n]\n");
        if(!strncmp(flogin, login, strlen(flogin) - 1) && !strncmp(fsenha, senha, strlen(fsenha) - 1)){
            return 1;
        }
    }

    fread

    fclose(usuarios);

    return 0;
}

bool cadastrarUsuario(int tipo, char* nome, char* login, char* senha){
    FILE *usuarios;
    usuarios = fopen("usuarios.bin", "a");

    usuario coiso;
    coiso.tipo = tipo;
    strcpy(coiso.nome, nome);
    strcpy(coiso.login, login);
    strcpy(coiso.senha, senha);

    fwrite(&coiso, sizeof(usuario), 1, usuarios);

    fclose(usuarios);

    return true;
}

bool alterarUsuario(char* nome, char* login, char* senha){
    FILE *usuarios;
    usuarios = fopen("usuarios.txt", "r+");

    char flogin[12];

    while(fgets(flogin, 12, usuarios) != NULL){

        if(!strncmp(flogin, login, strlen(flogin) - 1)){

            fputs(senha, usuarios);
            fputc('\n', usuarios);
            
        }
        
    }
}

#endif