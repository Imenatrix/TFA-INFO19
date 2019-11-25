#ifndef SUBMENU_H
#define SUBMENU_H

void menuAlterarDados(char* login){
    Usuario usuario;

    strcpy(usuario.login, login);

    printf("NOVO NOME: ");
    fgetstr(usuario.nome, 30, stdin);
    printf("NOVA SENHA: ");
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
        printf("-CADASTRO DO ADMIN-\n");
    }
    else{
        printf("-CADASTRO DO USUARIO-\n");
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

void menuRodadas(Save* save){
    for(int i = save->clubeIndex; i < 20; save->clubeIndex = i++){

        Clube clube;
        char buffer[30];
        memset(&clube, 0, sizeof(Clube));

        printf("-CADASTRO DE CLUBE %i-\n", i + 1);
        printf("<DIGITE /sair PARA VOLTAR AO MENU INICIAL>\n");

        printf("NOME: \n");
        fgetstr(buffer, 30, stdin);
        if(!strcmp(buffer, "/sair")){save->clubeIndex++;return;}
        strcpy(clube.nome, buffer);

        /*printf("CIDADE: \n");

        fgetstr(buffer, 30, stdin);
        if(!strcmp(buffer, "/sair")){save->clubeIndex++;return;}
        strcpy(clube.cidade, buffer);

        printf("ESTADIO: \n");
        fgetstr(buffer, 30, stdin);
        if(!strcmp(buffer, "/sair")){save->clubeIndex++;return;}
        strcpy(clube.estadio, buffer);*/

        save->clubes[i] = clube;
    }
    save->clubeIndex++;

    for(int i = 0; i < 19; i++){
        int* chave = gerarRodada(i);
        for(int j = 0; j < 10; j++){

            int golsMandante = rand() % 6;
            int golsVisitante = rand() % 6;

            save->clubes[chave[j]].jogos++;
            save->clubes[chave[j + 10]].jogos++;

            if(golsMandante > golsVisitante){
                save->clubes[chave[j]].vitorias++;
                save->clubes[chave[j + 10]].derrotas++;

                save->clubes[chave[j]].pontos += 3;
            }
            else if(golsMandante < golsVisitante){
                save->clubes[chave[j]].derrotas++;
                save->clubes[chave[j + 10]].vitorias++;

                save->clubes[chave[j + 10]].pontos += 3;
            }
            else{
                save->clubes[chave[j]].empates++;
                save->clubes[chave[j + 10]].empates++;

                save->clubes[chave[j]].pontos++;
                save->clubes[chave[j + 10]].pontos++;
            }
            save->clubes[chave[j]].gp += golsMandante;
            save->clubes[chave[j + 10]].gc += golsMandante;
            save->clubes[chave[j]].gc += golsVisitante;
            save->clubes[chave[j + 10]].gp += golsVisitante;

            save->clubes[chave[j]].sg += golsMandante - golsVisitante;
            save->clubes[chave[j + 10]].sg += golsVisitante - golsMandante;

            save->chave[chave[j]][chave[j + 10]] = true;
            save->chave[chave[j + 10]][chave[j]] = true;
        }
        free(chave);
    }

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            printf("%i ", save->chave[i][j]);
        }
        printf("\n");
    }

}

void menuSalvar(Save *save){

    if(!strcmp(save->nome, "")){
        printf("NOME: ");
        fgetstr(save->nome, 30, stdin);
    }
    Salvar(save);
}

 Save menuContinuar(char* login){
     //printf("asjdhkas");
    char* saves = listarSaves(login);
    char* buffer;

    buffer = strtok(saves, "\n");
    int i = 1;

    while(buffer){
        printf("%i) %s\n", i, buffer);
        buffer = strtok(NULL, "\n");
        i++;
    }

    int op;
    scanf("%i", &op);

    i = 1;
    saves = listarSaves(login);
    buffer = strtok(saves, "\n");
    printf("%s", buffer);
    while(i < op){
        buffer = strtok(NULL, "\n");
        printf("%s", buffer);
        i++;
    }
    free(saves);

    printf("<SAVE CARREGADO, APERTE (ENTER) PARA CONTINUAR>\n");
    return resgatarSave(buffer);
}

void menuRanking(Save* save){

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
        printf("%s | %i | %i | %i | %i | %i | %i | %i| %i | %.2lf | %.2lf\n",
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
            copia[i].mgc
        );
    }
}

#endif
