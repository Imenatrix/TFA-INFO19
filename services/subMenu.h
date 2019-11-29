#ifndef SUBMENU_H
#define SUBMENU_H

void menuAlterarDados(char* login){
    Usuario usuario;

    strcpy(usuario.login, login);

    printf("-ALTERAR CREDENCIAIS-\n\n");
    printf("Novo Nome: ");
    fgetstr(usuario.nome, 30, stdin);
    printf("Nova Senha: ");
    fgetstr(usuario.senha, 12, stdin);
    if(alterarUsuario(&usuario)){
        printf("<DADOS ALTERADOS COM SUCESSO>\n");
    }
    else{
        printf("<OCORREU UM ERRO>\n");
    }
}

void verUsuarios(){

    Usuario *lista = listarUsuarios();

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

    Usuario usuario = newUsuario(tipo, "", "", "");

    if(tipo){
        printf("\n-CADASTRO DO ADMIN-\n\n");
    }
    else{
        printf("\n-CADASTRO DO USUARIO-\n\n");
    }
    printf("NOME: ");
    fgetstr(usuario.nome, 30, stdin);
    printf("LOGIN: ");
    fgetstr(usuario.login, 12, stdin);
    printf("SENHA: ");
    fgetstr(usuario.senha, 12, stdin);

    if(cadastrarUsuario(&usuario)){
        printf("<CADASTRO REALIZADO COM SUCESSO>");
    }
    else{
        printf("<JA EXISTE UM USUARIO COM ESSE LOGIN>");
    }
}

char* menuRemover(){

    char* login = malloc(12 * sizeof(char));

    printf("-REMOVER USUARIO-\n\n");
    printf("LOGIN: ");
    fgetstr(login, 12, stdin);
    if(removerUsuario(login)){
        printf("<USUARIO -%s- REMOVIDO COM SUCESSO>", login);
        return login;
    }
    else{
        printf("<NENHUM USUARIO -%s- FOI ENCONTRADO>\n", login);
        return NULL;
    }
}

void menuSalvar(Save *save, bool perguntar){

    if(perguntar){

        bool flag = true;

        while(flag){

            char op;

            printf("<DESEJA SALVAR O CAMPEONATO ATUAL? (s/n)>\n");
            scanf(" %c", &op);

            switch (op){

            case 's':
                flag = false;
                break;

            case 'n':
                return;
                break;

            default:
                printf("<OPÇÂO INVALIDA>");
                break;
            }

        }
    }

    char* saves = listarSaves(save->usuario);
    char* buffer;


    printf("-SALVAR-\n\n");
    if(saves){
        buffer = strtok(saves, "\n");
        int i = 1;

        printf("<EM QUAL SAVE DESEJA SALVAR?>\n");
        printf("<DIGITE /novo PARA CRIAR UM NOVO SAVE>\n");
        while(buffer){
            printf("%i) %s\n", i, buffer);
            buffer = strtok(NULL, "\n");
            i++;
        }

        char bufferComando[6];
        fgetstr(bufferComando, 6, stdin);

        if(strcmp(bufferComando, "/novo")){

            int op = atoi(bufferComando);
            if(op == 0){printf("<OPÇÂO INVALIDA>");return;}

            i = 1;
            saves = listarSaves(save->usuario);
            buffer = strtok(saves, "\n");
            while(i < op){
                buffer = strtok(NULL, "\n");
                i++;
            }
            strcpy(save->nome, buffer);
            Salvar(save);

            free(saves);
            printf("<SALVO COM SUCESSO!>");
            return;

        }
    }
    printf("NOME: ");
    fgetstr(save->nome, 30, stdin);
    Salvar(save);

    free(saves);
    printf("<SALVO COM SUCESSO!>");
}

void menuRodadas(Save* save){

    char bufferComando[30];

    printf("<DIGITE /sair PARA VOLTAR AO MENU INICIAL>\n");
    for(; save->clubeIndex < 20; save->clubeIndex++){

        Clube clube;
        memset(&clube, 0, sizeof(Clube));

        printf("\n-CADASTRO DE CLUBE %i-\n", save->clubeIndex + 1);

        printf("NOME: \n");
        fgetstr(bufferComando, 30, stdin);
        if(!strcmp(bufferComando, "/sair")){menuSalvar(save, true);return;}
        strcpy(clube.nome, bufferComando);

        /*printf("CIDADE: \n");

        fgetstr(buffer, 30, stdin);
        if(!strcmp(buffer, "/sair")){menuSalvar(save, true);return;}
        strcpy(clube.cidade, buffer);

        printf("ESTADIO: \n");
        fgetstr(buffer, 30, stdin);
        if(!strcmp(buffer, "/sair")){menuSalvar(save, true);return;}
        strcpy(clube.estadio, buffer);*/

        save->clubes[save->clubeIndex] = clube;
    }

    bool automatico = false;
    bool muitoAutomatico = false;

    printf("<DIGITE /auto, /auto*>\n");

    for(int i = save->turnoIndex; save->turnoIndex < 2; i++, save->turnoIndex++){
        for(int j = save->turnos[i].rodadaIndex; save->turnos[i].rodadaIndex < 19; j++, save->turnos[i].rodadaIndex++){
            int* chave = gerarRodada(j);
            printf("%i\n", j);
            for(int k = save->turnos[i].rodadas[j].jogoIndex; save->turnos[i].rodadas[k].jogoIndex < 10; k++, save->turnos[i].rodadas[j].jogoIndex++){

                save->turnos[i].rodadas[j].jogos[k].mandante = chave[k];
                save->turnos[i].rodadas[j].jogos[k].visitante = chave[k + 10];

                //printf("%i - %i\n", chave[k], chave[k + 10]);
                //printf("%i\n", k);

                if(!automatico){
                    fgetstr(bufferComando, 7, stdin);
                    if(!strcmp(bufferComando, "/auto")){automatico = true;}
                    else if(!strcmp(bufferComando, "/auto*")){muitoAutomatico = true; automatico = true;}
                }

                if(automatico){
                    save->turnos[i].rodadas[j].jogos[k].golsMandante = rand() % 6;
                }
                else{
                    save->turnos[i].rodadas[j].jogos[k].golsMandante = atoi(bufferComando);
                }

                if(!automatico){
                    fgetstr(bufferComando, 6, stdin);
                    if(!strcmp(bufferComando, "/auto")){automatico = true;}
                    else if(!strcmp(bufferComando, "/auto*")){muitoAutomatico = true; automatico = true;}
                }

                if(automatico){
                    save->turnos[i].rodadas[j].jogos[k].golsVisitante = rand() % 6;
                }
                else{
                    save->turnos[i].rodadas[j].jogos[k].golsVisitante = atoi(bufferComando);
                }

                if(!muitoAutomatico){
                    automatico = false;
                }

            }
            free(chave);
        }
    }
}

Save menuContinuar(char* usuario){
    char* saves = listarSaves(usuario);
    char* buffer;

    buffer = strtok(saves, "\n");
    int i = 1;

    printf("-SALVOS-\n\n");
    while(buffer){
        printf("%i) %s\n", i, buffer);
        buffer = strtok(NULL, "\n");
        i++;
    }

    int op;
    scanf("%i", &op);

    i = 1;
    saves = listarSaves(usuario);
    buffer = strtok(saves, "\n");
    while(i < op){
        buffer = strtok(NULL, "\n");
        i++;
    }

    Save save = resgatarSave(buffer);
    printf("<SAVE CARREGADO, APERTE (ENTER) PARA CONTINUAR>\n");

    free(saves);
    return save;
}

void verRanking(Save* save){

    char bufferComando[30];
    fgetstr(bufferComando, 30, stdin);
    printf("ok");

    if(!strcmp(bufferComando, "/geral")){

        ClubeRanking* clubes = malloc(save->clubeIndex * sizeof(ClubeRanking));
        memset(clubes, 0, save->clubeIndex * sizeof(ClubeRanking));

        for(int i = 0; i < save->clubeIndex; i++){
            clubes[i].clube = &save->clubes[i];
        }

        for(int i = 0; i < save->turnoIndex; i++){
            for(int j = 0; j < save->turnos[j].rodadaIndex; j++){
                for(int k = 0; k < save->turnos[i].rodadas[j].jogoIndex; k++){

                    //ClubeRanking* mandante = &clubes[ save->turnos[i].rodadas[j].jogos[k].mandante ];
                    //ClubeRanking* visitante = &clubes[ save->turnos[i].rodadas[j].jogos[k].visitante ];

                    printf("%i\n", save->turnos[i].rodadas[j].jogos[k].mandante);

                    /*clubes[ save->turnos[i].rodadas[j].jogos[k].mandante ].jogos++;
                    clubes[ save->turnos[i].rodadas[j].jogos[k].visitante ].jogos++;
                    
                    clubes[ save->turnos[i].rodadas[j].jogos[k].mandante ].gp += save->turnos[i].rodadas[j].jogos[k].golsMandante;
                    clubes[ save->turnos[i].rodadas[j].jogos[k].visitante ].gp += save->turnos[i].rodadas[j].jogos[k].golsVisitante;

                    clubes[ save->turnos[i].rodadas[j].jogos[k].mandante ].gc += clubes[ save->turnos[i].rodadas[j].jogos[k].visitante ].gp;
                    clubes[ save->turnos[i].rodadas[j].jogos[k].visitante ].gc += clubes[ save->turnos[i].rodadas[j].jogos[k].mandante ].gp;

                    if(save->turnos[i].rodadas[j].jogos[k].golsMandante > save->turnos[i].rodadas[j].jogos[k].golsVisitante){
                        clubes[ save->turnos[i].rodadas[j].jogos[k].mandante ].vitorias++;
                        clubes[ save->turnos[i].rodadas[j].jogos[k].mandante ].pontos += 3;
                        clubes[ save->turnos[i].rodadas[j].jogos[k].visitante ].derrotas++;
                    }
                    else if(save->turnos[i].rodadas[j].jogos[k].golsMandante < save->turnos[i].rodadas[j].jogos[k].golsVisitante){
                        clubes[ save->turnos[i].rodadas[j].jogos[k].visitante ].vitorias++;
                        clubes[ save->turnos[i].rodadas[j].jogos[k].visitante ].pontos += 3;
                        clubes[ save->turnos[i].rodadas[j].jogos[k].mandante ].derrotas++;
                    }
                    else{
                        clubes[ save->turnos[i].rodadas[j].jogos[k].mandante ].empates++;
                        clubes[ save->turnos[i].rodadas[j].jogos[k].mandante ].pontos++;
                        clubes[ save->turnos[i].rodadas[j].jogos[k].visitante ].empates++;
                        clubes[ save->turnos[i].rodadas[j].jogos[k].visitante ].pontos++;
                    }*/
                }
            }
        }

        free(clubes);

    }
    
}

#endif
