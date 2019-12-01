#ifndef MENU_H
#define MENU_H

void menuUsuario(Usuario* usuario){

    Save save;
    Save* aux;

    bool newSave = false;

    memset(&save, 0, sizeof(save));
    strcpy(save.usuario, usuario->login);

    int o;

    bool menu = true;

    while(menu){
        system("cls");
        printf("Seja bem-vindo, %s!\n\n", usuario->nome);
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
                memset(&save, 0, sizeof(save));
                strcpy(save.usuario, usuario->login);
                newSave = true;
                menuRodadas(&save);
                break;

            case 2:
                aux = menuContinuar(save.usuario);

                if(aux){
                    memcpy(&save, aux, sizeof(Save));
                    free(aux);
                    system("cls");
                    newSave = true;
                    menuRodadas(&save);
                }

                break;

            case 3:
                menuAlterarDados(usuario);
                break;

            case 4:
                menuSalvar(&save, false);
                newSave = false;
                break;

            case 5:
                verRanking(&save);
                break;

            case 6:
                if(newSave){
                    menuSalvar(&save, true);
                }
                menu = false;
                break;

            case 7:
                if(newSave){
                    menuSalvar(&save, true);
                }
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

        system("cls");
        printf("Seja bem-vindo, %s\n\n", usuario->nome);
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

                if(login){
                    if(!strcmp(usuario->login, login)){
                        menu = false;
                        getch();
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

bool menuLogin(Usuario* usuario){

    char login[12];
    char senha[12];

    system("cls");
    printf("-LOGIN-\n\n");
    printf("Login: ");
    fgetstr(login, 12, stdin);
    printf("Senha: ");
    fgetstr(senha, 12, stdin);
    if(!efetuarLogin(usuario, login, senha)){
        printf("<CREDENCIAS INVÁLIDAS>\n");
        return false;
    }
    return true;
}
#endif
