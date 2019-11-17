#ifndef SUBMENU_H
#define SUBMENU_H

#include "usuarioCRUD.h"
#include "tfatools.h"

void menuAlterarDados(char* login){
    char nome[30];
    char senha[12];

    printf("NOVO NOME: ");
    fgetstr(nome, 30, stdin);
    printf("NOVA SENHA: ");
    fgetstr(senha, 12, stdin);
    if(alterarUsuario(nome, login, senha)){
        printf("<DADOS ALTERADOS COM SUCESSO>\n");
    }
    else{
        printf("<OCORREU UM ERRO>\n");
    }
}

void menuVisualizarUsuarios(){

    usuario *lista = visualizarUsuarios();

    for(int i = 0;lista[i].tipo != -1; i++){
        if(lista[i].tipo == 1){printf("<ADMIN>\n");}
        printf("NOME:\t%s\n", lista[i].nome);
        printf("LOGIN:\t%s\n", lista[i].login);
        printf("SENHA:\t%s\n", lista[i].senha);
        if(lista[i].tipo == 1){printf("</ADMIN>\n");}
        printf("\n");
    }
    free(lista);
}

void menuCadastro(int tipo){

    char nome[30];
    char login[12];
    char senha[12];

    if(tipo){
        printf("-CADASTRO DO ADMIN-\n");
    }
    else{
        printf("-CADASTRO DO USUARIO-\n");
    }
    printf("NOME: ");
    fgetstr(nome, 30, stdin);
    printf("LOGIN: ");
    fgetstr(login, 12, stdin);
    printf("SENHA: ");
    fgetstr(senha, 12, stdin);

    if(cadastrarUsuario(tipo, nome, login, senha)){
        printf("<CADASTRO REALIZADO COM SUCESSO>");
    }
    else{
        printf("<JA EXISTE UM USUARIO COM ESSE LOGIN>");
    }
}

char* menuRemover(){

    char* login = malloc(12 * sizeof(char));

    printf("-REMOVER USUARIO-\n");
    printf("LOGIN: ");
    fgetstr(login, 12, stdin);
    if(removerUsuario(login)){
        printf("<USUARIO -%s- REMOVIDO COM SUCESSO>", login);
        return login;
    }
    else{
        printf("<NENHUM USUARIO -%s- FOI ENCONTRADO>", login);
        return NULL;
    }
}

#endif // SUBMENU_H
