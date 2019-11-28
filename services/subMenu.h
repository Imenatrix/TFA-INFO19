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
        printf("-CADASTRO DO ADMIN-\n\n");
    }
    else{
        printf("-CADASTRO DO USUARIO-\n\n");
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
        printf("<NENHUM USUARIO -%s- FOI ENCONTRADO>", login);
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
    int golsMandante;
    int golsVisitante;

    printf("<DIGITE /auto, /auto*>\n");

    for(; save->turnoIndex < 2; save->turnoIndex++){
        for(; save->rodadaIndex < 19; save->rodadaIndex++){
            int* chave = gerarRodada(save->rodadaIndex);
            for(; save->jogoIndex < 10; save->jogoIndex++){

                if(!automatico){
                    fgetstr(bufferComando, 7, stdin);
                    if(!strcmp(bufferComando, "/auto")){automatico = true;}
                    else if(!strcmp(bufferComando, "/auto*")){muitoAutomatico = true; automatico = true;}
                }

                if(automatico){
                    golsMandante = rand() % 6;
                }
                else{
                    golsMandante = atoi(bufferComando);
                }

                if(!automatico){
                    fgetstr(bufferComando, 6, stdin);
                    if(!strcmp(bufferComando, "/auto")){automatico = true;}
                    else if(!strcmp(bufferComando, "/auto*")){muitoAutomatico = true; automatico = true;}
                }

                if(automatico){
                    golsVisitante = rand() % 6;
                }
                else{
                    golsVisitante = atoi(bufferComando);
                }

                if(!muitoAutomatico){
                    automatico = false;
                }

                save->clubes[chave[save->jogoIndex]].jogos++;
                save->clubes[chave[save->jogoIndex + 10]].jogos++;

                if(golsMandante > golsVisitante){
                    save->clubes[chave[save->jogoIndex]].vitorias++;
                    save->clubes[chave[save->jogoIndex + 10]].derrotas++;

                    save->clubes[chave[save->jogoIndex]].pontos += 3;
                }
                else if(golsMandante < golsVisitante){
                    save->clubes[chave[save->jogoIndex]].derrotas++;
                    save->clubes[chave[save->jogoIndex + 10]].vitorias++;

                    save->clubes[chave[save->jogoIndex + 10]].pontos += 3;
                }
                else{
                    save->clubes[chave[save->jogoIndex]].empates++;
                    save->clubes[chave[save->jogoIndex + 10]].empates++;

                    save->clubes[chave[save->jogoIndex]].pontos++;
                    save->clubes[chave[save->jogoIndex + 10]].pontos++;
                }
                save->clubes[chave[save->jogoIndex]].gp += golsMandante;
                save->clubes[chave[save->jogoIndex + 10]].gc += golsMandante;
                save->clubes[chave[save->jogoIndex]].gc += golsVisitante;
                save->clubes[chave[save->jogoIndex + 10]].gp += golsVisitante;

                save->clubes[chave[save->jogoIndex]].sg += golsMandante - golsVisitante;
                save->clubes[chave[save->jogoIndex + 10]].sg += golsVisitante - golsMandante;

            }
            free(chave);
            save->jogoIndex = 0;
        }
        save->rodadaIndex = 0;
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

void Ranking(Save* save){

    Clube* copia = malloc(sizeof(save->clubes));
    memcpy(copia, &save->clubes, sizeof(save->clubes));

    for(int i = 0; i < sizeof(save->clubes) / sizeof(Clube); i++){
        copia[i].mgp = ((double)copia[i].gp) / copia[i].jogos;
        copia[i].mgc = ((double)copia[i].gc) / copia[i].jogos;
    }

    for(int i = 0; i < sizeof(save->clubes) / sizeof(Clube); i++){
        for(int j = i; j < sizeof(save->clubes) / sizeof(Clube); j++){
            if(copia[i].pontos < copia[j].pontos){
                Clube aux = copia[i];
                copia[i] = copia[j];
                copia[j] = aux;
            }
        }
    }


    for(int i = 0; i < sizeof(save->clubes) / sizeof(Clube); i++){
        printf("%s | %i | %i | %i | %i | %i | %i | %i | %i | %.2lf | %.2lf | %i\n",
            copia[i].nome,
            copia[i].pontos,
            copia[i].jogos,
            copia[i].vitorias,
            copia[i].empates,
            copia[i].derrotas,
            copia[i].gp,
            copia[i].gc,
            copia[i].sg,
            copia[i].mgp,
            copia[i].mgc,
            copia[i].lastPos - i
        );
    }
}

#endif
