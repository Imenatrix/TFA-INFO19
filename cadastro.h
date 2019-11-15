#ifndef CADASTRO_H
#define CADASTRO_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int tipo;
    char nome[30];
    char login[12];
    char senha[12];
} usuario;

char* efetuarLogin(char* login, char* senha){
    FILE *usuarios;
    usuarios = fopen("usuarios.bin", "rb");

    usuario coiso;
    memset(&coiso, 0, sizeof(usuario));

    while(fread(&coiso, sizeof(usuario), 1, usuarios)){
        if(!strcmp(coiso.login, login) && !strcmp(coiso.senha, senha)){
            fclose(usuarios);
            char *nome = malloc(sizeof(char*));
            strcpy(nome, coiso.nome);
            return nome;
        }
    }

    fclose(usuarios);
    return NULL;
}

bool cadastrarUsuario(int tipo, char* nome, char* login, char* senha){
    FILE *usuarios;
    usuarios = fopen("usuarios.bin", "ab+");

    usuario coiso;
    memset(&coiso, 0, sizeof(usuario));

    while(fread(&coiso, sizeof(usuario), 1, usuarios)){
        if(!strcmp(coiso.login, login)){
            fclose(usuarios);
            return false;
        }
    }

    memset(&coiso, 0, sizeof(usuario));

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
    usuarios = fopen("usuarios.bin", "rb+");

    usuario coiso;
    memset(&coiso, 0, sizeof(usuario));

    while(fread(&coiso, sizeof(usuario), 1, usuarios)){
        if(!strcmp(coiso.login, login)){
            strcpy(coiso.nome, nome);
            strcpy(coiso.senha, senha);
            fseek(usuarios, -sizeof(usuario), SEEK_CUR);
            fwrite(&coiso, sizeof(usuario), 1, usuarios);
            fclose(usuarios);
            return true;
        }
    }
    fclose(usuarios);
    return false;
}

void removerUsuario(char* login){
    FILE *usuarios = fopen("usuarios.bin", "rb+");

    usuario coiso;
    memset(&coiso, 0, sizeof(usuario));

    fseek(usuarios, 0, SEEK_END);
    int tam = ftell(usuarios) - sizeof(usuario);
    fseek(usuarios, 0, SEEK_SET);

    while(fread(&coiso, sizeof(usuario), 1, usuarios)){
        if(!strcmp(coiso.login, login)){
            if(ftell(usuarios) - sizeof(usuario) == tam){
                ftruncate(fileno(usuarios), tam);
            }
            else{
                int pos = ftell(usuarios) - sizeof(usuario);

                fseek(usuarios, -sizeof(usuario), SEEK_END);
                fread(&coiso, sizeof(usuario), 1, usuarios);

                fseek(usuarios, pos, SEEK_SET);
                fwrite(&coiso, sizeof(usuario), 1, usuarios);
                ftruncate(fileno(usuarios), tam);
                break;
            }
        }
    }
    fclose(usuarios);
}

#endif
