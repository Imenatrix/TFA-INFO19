#ifndef USUARIO_H
#define USUARIO_H

typedef struct {
    int tipo;
    char nome[30];
    char login[12];
    char senha[12];
} Usuario;

Usuario newUsuario(int tipo, char* nome, char* login, char* senha){
    Usuario usuario;
    memset(&usuario, 0, sizeof(Usuario));

    usuario.tipo = tipo;
    strcpy(usuario.nome, nome);
    strcpy(usuario.login, login);
    strcpy(usuario.senha, senha);

    return usuario;
}
#endif
