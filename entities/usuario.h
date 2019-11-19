#ifndef USUARIO_H
#define USUARIO_H

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
#endif
