#ifndef USUARIO_H
#define USUARIO_H

#include <string.h>

typedef struct {
    int tipo;
    char nome[30];
    char login[12];
    char senha[12];
} usuario;

usuario Usuario(int tipo, char* nome, char* login, char* senha){
    usuario coiso;
    memset(&coiso, 0, sizeof(usuario));

    coiso.tipo = tipo;
    strcpy(coiso.nome, nome);
    strcpy(coiso.login, login);
    strcpy(coiso.senha, senha);

    return coiso;
}

/*char* usuarioToString(usuario coiso){
    int index = 0;
    char* str = malloc(sizeof(char));

    const char nome[] = "\nNOME: ";
    const char login[] = "\nLOGIN: ";
    const char senha[] = "\nSENHA: ";

    for(int i = 0; i < strlen(coiso.nome); i++){

    }
}*/


#endif
