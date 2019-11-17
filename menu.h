#ifndef MENU_H
#define MENU_H
#include <stdbool.h>
#include "tfatools.h"
#include "subMenu.h"
#include "usuarioCRUD.h"

void menuUsuario(usuario coiso){

    int o;

    bool menu = true;

    while(menu){
        system("cls");
        printf("Seja bem-vindo, %s!\n", coiso.nome);
        printf("1) Iniciar o Cadastro\n");
        printf("2) Continuar\n");
        printf("3) Modificar Dados de Autenticação\n");
        printf("4) Configuração\n");
        printf("5) Ranking\n");
        printf("6) Efetuar \"Logoff\"\n");
        printf("7) Sair\n");

        scanf("%i", &o);

        system("cls");
        switch(o){
            case 1:
                break;

            case 2:
                break;

            case 3:
                menuAlterarDados(coiso.login);
                break;

            case 4:
                break;

            case 5:
                break;

            case 6:
                menu = false;
                break;

            case 7:
                exit(1);
                break;

            default:
                printf("<OPERAÇÂO INVÀLIDA>");
                break;
        }
        if(menu){
            getch();
        }
    }
}

void menuAdmin(usuario coiso){

    int o;

    char *login;
    bool menu = true;

    while(menu){

        system("cls");
        printf("Seja bem-vindo: %s\n", coiso.nome);
        printf("1) Cadastrar Usuário\n");
        printf("2) Visualizar Usuário\n");
        printf("3) Remover Usuário\n");
        printf("4) Efetuar \"Logoff\"\n");
        printf("5) Sair\n");

        scanf("%i", &o);

        system("cls");
        switch(o){
            case 1:
                menuCadastro(0);
                break;

            case 2:
                menuVisualizarUsuarios();
                break;

            case 3:
                login = menuRemover();
                if(!strcmp(coiso.login, login)){
                   menu = false;
                }
                free(login);
                break;

            case 4:
                menu = false;
                break;

            case 5:
                exit(1);
                break;

            default:
                printf("<OPÇÃO INVÁLIDA>");
                break;
        }
        if(menu){
            getch();
        }
    }
}

usuario* menuLogin(){

    int i;
    char login[12];
    char senha[12];

    usuario* coiso;

    system("cls");
    printf("LOGIN: ");
    fgetstr(login, 12, stdin);
    printf("SENHA: ");
    fgetstr(senha, 12, stdin);
    coiso = efetuarLogin(login, senha);
    if(coiso){
        return coiso;
    }
    printf("<CREDENCIAS INVALIDAS>\n");
    return NULL;
}
#endif
