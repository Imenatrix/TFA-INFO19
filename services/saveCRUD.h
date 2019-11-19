#ifndef SAVECRUD_H
#define SAVECRUD_H

bool Salvar(Save* save){
    FILE *saves;
    saves = fopen("saves.bin", "ab+");

    Save temp;
    memset(&temp, 0, sizeof(Save));

    while(fread(&temp, sizeof(Save), 1, saves)){
        if(!strcmp(temp.nome, save->nome)){
            int pos = ftell(saves) - sizeof(Save);
            fclose(saves);
            saves = fopen("saves.bin", "rb+");
            fseek(saves, pos, SEEK_SET);
            fwrite(save, sizeof(Save), 1, saves);
            fclose(saves);
            return true;
        }
    }

    fwrite(save, sizeof(Save), 1, saves);

    fclose(saves);
    return true;
}

bool removerSave(Save* save){
    FILE *saves = fopen("saves.bin", "rb+");

    Save temp;
    memset(&temp, 0, sizeof(Save));

    fseek(saves, 0, SEEK_END);
    int tam = ftell(saves) - sizeof(Save);
    fseek(saves, 0, SEEK_SET);

    while(fread(&temp, sizeof(Save), 1, saves)){
        if(!strcmp(temp.nome, save->nome)){
            if(ftell(saves) - sizeof(Save) == tam){
                ftruncate(fileno(saves), tam);
            }
            else{
                int pos = ftell(saves) - sizeof(Save);

                fseek(saves, -sizeof(Save), SEEK_END);
                fread(&temp, sizeof(Save), 1, saves);

                fseek(saves, pos, SEEK_SET);
                fwrite(&temp, sizeof(Save), 1, saves);
                ftruncate(fileno(saves), tam);
                break;
            }
            fclose(saves);
            return true;
        }
    }
    fclose(saves);
    return false;
}

Save resgatarSave(char* nome){
    FILE* saves = fopen("saves.bin", "rb");

    Save save;

    while(fread(&save, sizeof(Save), 1, saves)){
        if(!strcmp(save.nome, nome)){
            fclose(saves);
            return save;
        }
    }
    fclose(saves);
    memset(&save, 0, sizeof(Save));
    save.clubeIndex = -1;
    return save;
}

Save listarSaves(){
    FILE* saves = fopen("saves.bin", "rb");

    int index = 0;
    Save save;
    memset(&save, 0, sizeof(Save));
    char** nomes = malloc(sizeof(char*));

    while(fread(&save, sizeof(Save), 1, saves)){
        index++;
        nomes = realloc(nomes, (index + 1) * sizeof(char*));
        nomes[index] = malloc(30 * sizeof(char));
        strcpy(nomes[index], save.nome);
        puts(save.nome);
        puts(nomes[index]);
    }

    for(int i = 0; i < index; i++){
        for(int j = index - i; j < index; j++){
            if(strcmp(nomes[i], nomes[j]) < 0){
                char aux[30];
                strcpy(aux, nomes[i]);
                strcpy(nomes[i], nomes[j]);
                strcpy(nomes[j], aux);
            }
        }
    }

    //char** saves = listarSaves();
    nomes[index] = "";
    fclose(saves);

    for(int i = 0; !strcmp(nomes[i], ""); i++){
        printf("%i) %s\n", i + 1, nomes[i]);
    }
    int op;
    scanf("%i", &op);
    printf("<Save CARREGADO, APERTE (ENTER) PARA CONTINUAR>\n");
    return resgatarSave(nomes[op - 1]);

}
#endif
