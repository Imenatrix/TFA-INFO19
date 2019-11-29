#ifndef MENU_H
#define MENU_H

void menuUsuario(Usuario* usuario){

    Save save;

    memset(&save, 0, sizeof(save));
    strcpy(save.usuario, usuario->login);

    int o;

    bool menu = true;

    while(menu){
        system("clear");
        printf("Seja bem-vindo, %s!\n\n", usuario->nome);
        printf("1) Iniciar novo campeonato\n");
        printf("2) Continuar\n");
        printf("3) Modificar Dados de Autenticação\n");
        printf("4) Salvar campeonato\n");
        printf("5) Ranking\n");
        printf("6) Efetuar \"Logoff\"\n");
        printf("7) Sair\n");

        scanf("%i", &o);

        system("clear");
        switch(o){
            case 1:
                memset(&save, 0, sizeof(save));
                strcpy(save.usuario, usuario->login);
                menuRodadas(&save);
                break;

            case 2:
                //memset(&save, 0, sizeof(save));
                //strcpy(save.usuario, usuario->login);
                save = menuContinuar(save.usuario);
                system("clear");
                menuRodadas(&save);
                break;

            case 3:
                menuAlterarDados(usuario->login);
                break;

            case 4:
                menuSalvar(&save, false);
                break;

            case 5:
                verRanking(&save);
                break;

            case 6:
                menuSalvar(&save, true);
                menu = false;
                break;

            case 7:
                menuSalvar(&save, true);
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

void menuAdmin(Usuario* usuario){

    int o;

    char *login;
    bool menu = true;

    while(menu){

        system("clear");
        printf("Seja bem-vindo, %s\n\n", usuario->nome);
        printf("1) Cadastrar Usuário\n");
        printf("2) Visualizar Usuário\n");
        printf("3) Remover Usuário\n");
        printf("4) Efetuar \"Logoff\"\n");
        printf("5) Sair\n");

        scanf("%i", &o);

        system("clear");
        switch(o){
            case 1:
                menuCadastro(0);
                break;

            case 2:
                verUsuarios();
                break;

            case 3:
                login = menuRemover();

                if(login){
                    if(!strcmp(usuario->login, login)){
                        menu = false;
                    }
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

Usuario menuLogin(){

    char login[12];
    char senha[12];

    Usuario usuario;

    system("clear");
    printf("-LOGIN-\n\n");
    printf("Login: ");
    fgetstr(login, 12, stdin);
    printf("Senha: ");
    fgetstr(senha, 12, stdin);
    usuario = efetuarLogin(login, senha);
    if(usuario.tipo == -1){
        printf("<CREDENCIAS INVÁLIDAS>\n");
    }
    return usuario;
}
#endif
