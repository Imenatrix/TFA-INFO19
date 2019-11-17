#ifndef USUARIOCRUD_H
#define USUARIOCRUD_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../entities/usuario.h"

bool verificaAdmin(){
    FILE *usuarios = fopen("usuarios.bin", "rb");

    usuario coiso;
    memset(&coiso, 0, sizeof(usuario));

    while(fread(&coiso, sizeof(usuario), 1, usuarios)){
        if(coiso.tipo == 1){
            fclose(usuarios);
            return true;
        }
    }
    fclose(usuarios);
    return false;
}

usuario* efetuarLogin(char* login, char* senha){
    FILE *usuarios = fopen("usuarios.bin", "rb");

    usuario *coiso = malloc(sizeof(usuario));

    while(fread(coiso, sizeof(usuario), 1, usuarios)){
        if(!strcmp(coiso->login, login) && !strcmp(coiso->senha, senha)){
            fclose(usuarios);
            return coiso;
        }
    }
    fclose(usuarios);
    free(coiso);
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

    coiso = Usuario(tipo, nome, login, senha);
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
            coiso = Usuario(coiso.tipo, nome, login, senha);
            fseek(usuarios, -sizeof(usuario), SEEK_CUR);
            fwrite(&coiso, sizeof(usuario), 1, usuarios);
            fclose(usuarios);
            return true;
        }
    }
    fclose(usuarios);
    return false;
}

bool removerUsuario(char* login){
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
            fclose(usuarios);
            return true;
        }
    }
    fclose(usuarios);
    return false;
}

usuario* visualizarUsuarios(){
    FILE* usuarios = fopen("usuarios.bin", "rb");

    int index = 0;
    usuario* coiso = malloc(sizeof(usuario));

    while(fread(&coiso[index], sizeof(usuario), 1, usuarios)){
        index++;
        coiso = realloc(coiso, (index + 1) * sizeof(usuario));
    }

    for(int i = 0; i < index; i++){
        for(int j = index - i; j < index; j++){
            if(strcmp(coiso[i].nome, coiso[j].nome) < 0 || coiso[j].tipo){
                usuario aux;
                aux = coiso[i];
                coiso[i] = coiso[j];
                coiso[j] = aux;
            }
        }
    }

    //gambiarra?
    coiso[index].tipo = -1;
    fclose(usuarios);
    return coiso;
}

#endif
