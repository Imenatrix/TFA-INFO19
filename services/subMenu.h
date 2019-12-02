#ifndef SUBMENU_H
#define SUBMENU_H

void menuAlterarDados(Usuario* usuario){

    printf("-ALTERAR CREDENCIAIS-\n\n");
    printf("Novo Nome: ");
    fgetstr(usuario->nome, 30, stdin);
    printf("Nova Senha: ");
    fgetstr(usuario->senha, 12, stdin);
    if(alterarUsuario(usuario)){
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
            if(op >= i || op == 0){
                printf("<SELEÇÃO INVÁLIDA>\n");
                return;
            }

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
            printf("<SALVO COM SUCESSO!>\n");
            return;

        }
    }
    printf("\nNOME: ");
    fgetstr(save->nome, 30, stdin);
    Salvar(save);

    free(saves);
    printf("<SALVO COM SUCESSO!>\n");
}

void menuRodadas(Save* save){

    char bufferComando[30];

    if(save->clubeCap == 0){
        save->clubeCap = 20;
    }

    printf("<DIGITE /sair PARA VOLTAR AO MENU INICIAL>\n");
    for(; save->clubeIndex < save->clubeCap; save->clubeIndex++){

        Clube clube;
        memset(&clube, 0, sizeof(Clube));

        printf("\n-CADASTRO DE CLUBE %i-\n", save->clubeIndex + 1);

        printf("\nNOME:\t\t");
        fgetstr(bufferComando, 30, stdin);
        if(!strcmp(bufferComando, "/sair")){return;}
        else if(!strcmp(bufferComando, "/pronto")){save->clubeCap = save->clubeIndex; break;}
        strcpy(clube.nome, bufferComando);

        /*printf("CIDADE:\t\t");
        fgetstr(bufferComando, 30, stdin);
        if(!strcmp(bufferComando, "/sair")){return;}
        strcpy(clube.cidade, bufferComando);

        printf("ESTADIO:\t");
        fgetstr(bufferComando, 30, stdin);
        if(!strcmp(bufferComando, "/sair")){return;}
        strcpy(clube.estadio, bufferComando);*/

        printf("\n");

        save->clubes[save->clubeIndex] = clube;
    }

    bool automatico = false;
    bool muitoAutomatico = false;

    system("cls");
    printf("<DIGITE OS RESULTADOS DOS JOGOS>\n");
    printf("<DIGITE /sair PARA VOLTAR AO MENU INICIAL>\n");
    printf("<DIGITE /auto PARA PREENCHER A RODADA AUTOMATICAMENTE>\n");
    printf("<DIGITE /auto* PARA PREENCHER TODAS AS RODADAS AUTOMATICAMENTE>\n");

    for(int i = save->turnoIndex; save->turnoIndex < 2; i++, save->turnoIndex++){
        for(int j = save->turnos[i].rodadaIndex; save->turnos[i].rodadaIndex < save->clubeIndex - 1; j++, save->turnos[i].rodadaIndex++){

            int* chave = gerarRodada(j, save->clubeIndex);
            if(!muitoAutomatico){printf("\nTURNO %i - RODADA %i\n", i + 1, j + 1);}

            for(int k = save->turnos[i].rodadas[j].jogoIndex; save->turnos[i].rodadas[j].jogoIndex < save->clubeIndex / 2; k++, save->turnos[i].rodadas[j].jogoIndex++){

                if(i == 0){
                    save->turnos[i].rodadas[j].jogos[k].mandante = chave[k];
                    save->turnos[i].rodadas[j].jogos[k].visitante = chave[k + save->clubeIndex / 2];
                }
                else{
                    save->turnos[i].rodadas[j].jogos[k].mandante = chave[k + save->clubeIndex / 2];
                    save->turnos[i].rodadas[j].jogos[k].visitante = chave[k];
                }


                if(!automatico){
                    printf("%s X %s\n", save->clubes[save->turnos[i].rodadas[j].jogos[k].mandante].nome, save->clubes[save->turnos[i].rodadas[j].jogos[k].visitante].nome);
                    printf("%s: ", save->clubes[save->turnos[i].rodadas[j].jogos[k].mandante].nome);
                    fgetstr(bufferComando, 7, stdin);
                    if(!strcmp(bufferComando, "/sair")){return;}
                    else if(!strcmp(bufferComando, "/auto")){automatico = true;}
                    else if(!strcmp(bufferComando, "/auto*")){muitoAutomatico = true; automatico = true;}
                }

                if(automatico){
                    save->turnos[i].rodadas[j].jogos[k].golsMandante = rand() % 6;
                }
                else{
                    save->turnos[i].rodadas[j].jogos[k].golsMandante = atoi(bufferComando);
                }


                if(!automatico){
                    printf("%s: ", save->clubes[save->turnos[i].rodadas[j].jogos[k].visitante].nome);
                    fgetstr(bufferComando, 7, stdin);
                    if(!strcmp(bufferComando, "/sair")){return;}
                    else if(!strcmp(bufferComando, "/auto")){automatico = true;}
                    else if(!strcmp(bufferComando, "/auto*")){muitoAutomatico = true; automatico = true;}
                    printf("\n");
                }

                if(automatico){
                    save->turnos[i].rodadas[j].jogos[k].golsVisitante = rand() % 6;
                }
                else{
                    save->turnos[i].rodadas[j].jogos[k].golsVisitante = atoi(bufferComando);
                }


            }
            if(!muitoAutomatico){
                automatico = false;
            }
            free(chave);
        }
    }
    system("cls");
    printf("<CAMPEONATO FINALIZADO! VA ATE O MENU DE RANKING PARA VER O RESULTADO>");
}

Save* menuContinuar(char* usuario){
    char* saves = listarSaves(usuario);
    if(saves){
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

        if(op >= i || op == 0){
            printf("<SELEÇÃO INVÁLIDA>\n");
            return NULL;
        }

        i = 1;
        saves = listarSaves(usuario);
        buffer = strtok(saves, "\n");
        while(i < op){
            buffer = strtok(NULL, "\n");
            i++;
        }

        Save* save = resgatarSave(buffer);
        printf("<SAVE CARREGADO, APERTE (ENTER) PARA CONTINUAR>\n");
        return save;
    }
    printf("<NENHUM SAVE ENCONTRADO>\n");
    return NULL;
}

void verRanking(Save* save){

    char bufferComando[30];

    printf("<DIGITE UM NUMERO N PARA VER OS JOGOS DA RODADA N>\n");
    printf("<DIGITE /geral PARA VER O RANKING GERAL>\n");
    printf("<DIGITE DOIS NUMEROS N E M PARA VER O RANKING ENTRE AS RODADAS N E M>\n");
    fgetstr(bufferComando, 30, stdin);


    if(!strcmp(bufferComando, "/geral") || strchr(bufferComando, ' ')){

        int turnoC, turnoF, rodadaC, rodadaF;

        if(!strcmp(bufferComando, "/geral")){

            turnoC = 0;
            rodadaC = 0;
            turnoF = save->turnoIndex;
            rodadaF = save->turnos[turnoF - 1].rodadaIndex;

        }
        else{

            int buffer = atoi(strtok(bufferComando, " "));

            turnoC = ceil(buffer / ((double)save->clubeIndex - 1)) - 1;
            rodadaC = buffer - ((save->turnos[turnoC].rodadaIndex) * (turnoC)) - 1;

            buffer = atoi(strtok(NULL, " "));

            turnoF = ceil(buffer / ((double)save->clubeIndex - 1));
            rodadaF = buffer - ((save->turnos[turnoF - 1].rodadaIndex) * (turnoF - 1));

            if(!(turnoC > save->turnoIndex - 1)){
                if(rodadaC > save->turnos[turnoC].rodadaIndex - 1){
                    printf("<ESSA RODADA NÃO EXISTE>\n");
                    return;
                }
            }
            else{
                printf("<ESSA RODADA NÃO EXISTE>\n");
                return;
            }

            if(!(turnoF > save->turnoIndex)){
                if(rodadaF > save->turnos[turnoF].rodadaIndex){
                    printf("<ESSA RODADA NÃO EXISTE>\n");
                    return;
                }
            }
            else{
                printf("<ESSA RODADA NÃO EXISTE>\n");
                return;
            }

            if(turnoC > turnoF || rodadaC > rodadaF){
                printf("<ERRO: O VALOR INICIAL É MAIOR QUE O FINAL>");
                return;
            }

        }

        ClubeRanking* clubes = malloc(save->clubeIndex * sizeof(ClubeRanking));
        memset(clubes, 0, save->clubeIndex * sizeof(ClubeRanking));

        for(int i = 0; i < save->clubeIndex; i++){
            clubes[i].clube = &save->clubes[i];
        }

        for(int i = turnoC; i != turnoF; i++){
            for(int j = rodadaC; (i != turnoF - 1 && j < save->turnos[i].rodadaIndex) || (i == turnoF - 1 && j < rodadaF); j++){
                for(int k = 0; k < save->turnos[i].rodadas[j].jogoIndex; k++){

                    ClubeRanking* mandante = &clubes[ save->turnos[i].rodadas[j].jogos[k].mandante ];
                    ClubeRanking* visitante = &clubes[ save->turnos[i].rodadas[j].jogos[k].visitante ];

                    mandante->jogos++;
                    visitante->jogos++;

                    mandante->gp += save->turnos[i].rodadas[j].jogos[k].golsMandante;
                    visitante->gp += save->turnos[i].rodadas[j].jogos[k].golsVisitante;

                    mandante->gc += save->turnos[i].rodadas[j].jogos[k].golsVisitante;
                    visitante->gc += save->turnos[i].rodadas[j].jogos[k].golsMandante;

                    if(save->turnos[i].rodadas[j].jogos[k].golsMandante > save->turnos[i].rodadas[j].jogos[k].golsVisitante){
                        mandante->vitorias++;
                        mandante->pontos += 3;
                        visitante->derrotas++;
                    }
                    else if(save->turnos[i].rodadas[j].jogos[k].golsMandante < save->turnos[i].rodadas[j].jogos[k].golsVisitante){
                        visitante->vitorias++;
                        visitante->pontos += 3;
                        mandante->derrotas++;
                    }
                    else{
                        mandante->empates++;
                        mandante->pontos++;
                        visitante->empates++;
                        visitante->pontos++;
                    }
                }
            }
        }

        int sizes[11];

        sizes[0] = 4;
        sizes[1] = 3;
        sizes[2] = 3;
        sizes[3] = 1;
        sizes[4] = 1;
        sizes[5] = 1;
        sizes[6] = 2;
        sizes[7] = 2;
        sizes[8] = 2;
        sizes[9] = 3;
        sizes[10] = 3;

        for(int i = 0; i < save->clubeIndex; i++){

            int temp[11];
            int pos;

            for(int j = i; j < save->clubeIndex; j++){
                if(clubes[i].pontos < clubes[j].pontos){
                    ClubeRanking aux = clubes[i];
                    clubes[i] = clubes[j];
                    clubes[j] = aux;
                }
            }

            char buffer[10];

            temp[0] = strlen(clubes[i].clube->nome);

            itoa(clubes[i].pontos, buffer, 10);
            temp[1] = strlen(buffer);

            itoa(clubes[i].jogos, buffer, 10);
            temp[2] = strlen(buffer);

            itoa(clubes[i].vitorias, buffer, 10);
            temp[3] = strlen(buffer);

            itoa(clubes[i].empates, buffer, 10);
            temp[4] = strlen(buffer);

            itoa(clubes[i].derrotas, buffer, 10);
            temp[5] = strlen(buffer);

            itoa(clubes[i].gp, buffer, 10);
            temp[6] = strlen(buffer);

            itoa(clubes[i].gc, buffer, 10);
            temp[7] = strlen(buffer);

            itoa(clubes[i].gc - clubes[i].gp, buffer, 10);
            temp[8] = strlen(buffer);

            ftoa(((double)clubes[i].gc) / clubes[i].jogos, buffer, 2);
            temp[9] = strlen(buffer);

            ftoa(((double)clubes[i].gp) / clubes[i].jogos, buffer, 2);
            temp[10] = strlen(buffer);

            for(int j = 0; j < 11; j++){
                if(sizes[j] < temp[j]){
                    sizes[j] = temp[j];
                }
            }
        }

        system("cls");
        printf("%2s | %*s | %*s | %*s | %*s | %*s | %*s | %*s | %*s | %*s | %*s | %*s |\n",
            "Pos",
            sizes[0],
            "Time",
            sizes[1],
            "Pts",
            sizes[2],
            "Jgs",
            sizes[3],
            "V",
            sizes[4],
            "E",
            sizes[5],
            "D",
            sizes[6],
            "GP",
            sizes[7],
            "GC",
            sizes[8],
            "SG",
            sizes[9],
            "mGP",
            sizes[10],
            "mGC");
        for(int i = 0; i < save->clubeIndex; i++){

            printf("%3i | %*s | %*i | %*i | %*i | %*i | %*i | %*i | %*i | %*i | %*.2lf | %*.2lf |\n",
                i + 1,
                sizes[0],
                clubes[i].clube->nome,
                sizes[1],
                clubes[i].pontos,
                sizes[2],
                clubes[i].jogos,
                sizes[3],
                clubes[i].vitorias,
                sizes[4],
                clubes[i].empates,
                sizes[5],
                clubes[i].derrotas,
                sizes[6],
                clubes[i].gp,
                sizes[7],
                clubes[i].gc,
                sizes[8],
                clubes[i].gp - clubes[i].gc,
                sizes[9],
                ((double)clubes[i].gp) / clubes[i].jogos,
                sizes[10],
                ((double)clubes[i].gc) / clubes[i].jogos);
        }
        free(clubes);
    }
    else{
        int turno = ceil(atoi(bufferComando) / ((double)save->clubeIndex - 1)) - 1;
        int rodada = atoi(bufferComando) - ((save->turnos[turno].rodadaIndex) * (turno)) - 1;

        if(!(turno > save->turnoIndex - 1)){
            if(rodada > save->turnos[turno].rodadaIndex - 1){
                printf("<ESSA RODADA NÃO EXISTE>\n");
                return;
            }
        }
        else{
            printf("<ESSA RODADA NÃO EXISTE>\n");
            return;
        }

        Jogo* jogos = &save->turnos[turno].rodadas[rodada].jogos;
        Clube* clubes = &save->clubes;

        system("cls")/
        printf("TURNO %i - RODADA %i\n\n", turno + 1, rodada + 1);
        for(int i = 0; i < save->turnos[turno].rodadas[rodada].jogoIndex; i++){
            printf("%s - %i X %i - %s | %s | %s\n",
                clubes[jogos[i].mandante].nome,
                jogos[i].golsMandante, jogos[i].golsVisitante,
                clubes[jogos[i].visitante].nome,
                clubes[jogos[i].mandante].estadio,
                clubes[jogos[i].mandante].cidade);
        }
    }
}

#endif
