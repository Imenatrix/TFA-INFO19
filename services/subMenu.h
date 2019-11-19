#ifndef SUBMENU_H
#define SUBMENU_H

void menuAlterarDados(char* login){
    char nome[30];
    char senha[12];

    printf("NOVO NOME: ");
    fgetstr(nome, 30, stdin);
    printf("NOVA SENHA: ");
    fgetstr(senha, 12, stdin);
    if(alterarUsuario(nome, login, senha)){
        printf("<DADOS ALTERADOS COM SUCESSO>\n");
    }
    else{
        printf("<OCORREU UM ERRO>\n");
    }
}

void verUsuarios(){

    usuario *lista = listarUsuarios();

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

    char nome[30];
    char login[12];
    char senha[12];

    if(tipo){
        printf("-CADASTRO DO ADMIN-\n");
    }
    else{
        printf("-CADASTRO DO USUARIO-\n");
    }
    printf("NOME: ");
    fgetstr(nome, 30, stdin);
    printf("LOGIN: ");
    fgetstr(login, 12, stdin);
    printf("SENHA: ");
    fgetstr(senha, 12, stdin);

    if(cadastrarUsuario(tipo, nome, login, senha)){
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

void menuRodadas(save* _save){
    for(int i = _save->clubeIndex; i < 20; _save->clubeIndex = i++){

        clube _clube;
        char buffer[30];
        memset(&_clube, 0, sizeof(clube));

        printf("-CADASTRO DE CLUBE %i-\n", i + 1);
        printf("<DIGITE /sair PARA VOLTAR AO MENU INICIAL>\n");

        printf("NOME: \n");
        fgetstr(buffer, 30, stdin);
        if(!strcmp(buffer, "/sair")){return;}
        strcpy(_clube.nome, buffer);

        printf("CIDADE: \n");
        fgetstr(buffer, 30, stdin);
        if(!strcmp(buffer, "/sair")){return;}
        strcpy(_clube.nome, buffer);

        printf("ESTADIO: \n");
        fgetstr(buffer, 30, stdin);
        if(!strcmp(buffer, "/sair")){return;}
        strcpy(_clube.nome, buffer);

        _save->clubes[i] = _clube;
    }
    _save->clubeIndex++;
    for(int i = _save->turnoIndex; i < 2; _save->turnoIndex = i++){
        for(int j = _save->rodadaIndex; j < 19; _save->rodadaIndex = j++){
            for(int k = _save->rodadas[i][j].jogoIndex; k < 10; _save->rodadas[i][j].jogoIndex = k++){
                _save->rodadas[i][j].jogos[k];
            }
        }
    }
    _save->turnoIndex++;
}

void menuSalvar(save _save){

    if(!strcmp(_save.nome, "")){
        printf("NOME: ");
        fgetstr(_save.nome, 30, stdin);
    }
    Salvar(_save);
}

save menuContinuar(){
    save *saves = listarSaves();
    for(int i = 0; saves[i].clubeIndex != -1; i++){
        printf("%i) %s\n", i + 1, saves[i].nome);
    }
    int op;
    scanf("%i", &op);
    printf("<SAVE CARREGADO, APERTE (ENTER) PARA CONTINUAR>\n");
    return saves[op - 1];
}
#endif
