#ifndef MENU_H
#define MENU_H

void menuUsuario(char* login){

    int o;

    if(login){
        printf("Seja bem-vindo: %s\n", login);
        printf("1) Iniciar o Cadastro\n");
        printf("2) Continuar\n");
        printf("3) Modificar Dados de Autenticação\n");
        printf("4) Configuração\n");
        printf("5) Ranking\n");
        printf("6) Efetuar “Logoff”\n");
        printf("7) Sair\n");

        scanf("%i", &o);

        switch(o){
            case 1:
                break;

            case 2:
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
                break;

            case 6:
                break;

            case 7:
                exit(1);
                break;

            default:
                break;
        }
    }
    else{
        exit(1);
    }
}

void menuAdmin(usuario coiso){

    int o;

    printf("Seja bem-vindo: %s\n", coiso.nome);
    printf("1) Cadastrar Usuário\n");
    printf("2) Visualizar Usuário\n");
    printf("3) Remover Usuário\n");
    printf("4) Efetuar “Logoff”\n");
    printf("5) Sair\n");

            scanf("%i", &o);

        switch(o){
            case 1:
                break;

            case 2:
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
                break;

            default:
                break;
        }
}

#endif
