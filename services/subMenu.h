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

        printf("CIDADE: \n");
        fgetstr(buffer, 30, stdin);
        if(!strcmp(buffer, "/sair")){save->clubeIndex++;return;}
        strcpy(clube.cidade, buffer);

        printf("ESTADIO: \n");
        fgetstr(buffer, 30, stdin);
        if(!strcmp(buffer, "/sair")){save->clubeIndex++;return;}
        strcpy(clube.estadio, buffer);

        save->clubes[i] = clube;
    }
    save->clubeIndex++;
    for(int i = save->turnoIndex; i < 2; save->turnoIndex = i++){
        for(int j = save->rodadaIndex; j < 19; save->rodadaIndex = j++){
            for(int k = save->rodadas[i][j].jogoIndex; k < 10; save->rodadas[i][j].jogoIndex = k++){
                save->rodadas[i][j].jogos[k].
            }
        }
    }

    save->turnoIndex++;
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
    buffer = strtok(saves, "\n");
    while(i < op){
        buffer = strtok(NULL, "\n");
        i++;
    }

    printf("<SAVE CARREGADO, APERTE (ENTER) PARA CONTINUAR>\n");
    return resgatarSave(buffer);
}
#endif
