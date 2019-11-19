#ifndef MENU_H
#define MENU_H

void menuUsuario(usuario coiso){

    save _save;

    int o;

    bool menu = true;

    while(menu){
        system("cls");
        printf("Seja bem-vindo, %s!\n", coiso.nome);
        printf("1) Iniciar novo campeonato\n");
        printf("2) Continuar\n");
        printf("3) Modificar Dados de Autenticação\n");
        printf("4) Salvar campeonato\n");
        printf("5) Ranking\n");
        printf("6) Efetuar \"Logoff\"\n");
        printf("7) Sair\n");

        scanf("%i", &o);

        system("cls");
        switch(o){
            case 1:
                memset(&_save, 0, sizeof(_save));
                menuRodadas(&_save);
                break;

            case 2:
                _save = menuContinuar();
                getch();
                menuRodadas(&_save);
                break;

            case 3:
                menuAlterarDados(coiso.login);
                break;

            case 4:
                menuSalvar(_save);
                break;

            case 5:
                break;

            case 6:
                //menuSalvar(_save);
                menu = false;
                break;

            case 7:
                //menuSalvar(_save);
                exit(1);
                break;

            default:
                printf("<OPERAÇÃO INVÁLIDA>");
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
                verUsuarios();
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

usuario menuLogin(){

    char login[12];
    char senha[12];

    usuario coiso;

    system("cls");
    printf("LOGIN: ");
    fgetstr(login, 12, stdin);
    printf("SENHA: ");
    fgetstr(senha, 12, stdin);
    coiso = efetuarLogin(login, senha);
    if(coiso.tipo == -1){
        printf("<CREDENCIAS INVÁLIDAS>\n");
    }
    return coiso;
}
#endif
