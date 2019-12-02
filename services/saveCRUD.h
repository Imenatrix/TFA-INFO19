#ifndef SAVECRUD_H
#define SAVECRUD_H

bool Salvar(Save* save){
    FILE *saves;
    saves = fopen("saves.txt", "a+");

    Save temp;

    char fbuffer[sizeof(Save)];

    fseek(saves, 0, SEEK_END);
    int fim = ftell(saves);
    fseek(saves, 0, SEEK_SET);

    while(ftell(saves) != fim){

        for(int i = 0; i < sizeof(Save); i++){
            fbuffer[i] = fgetc(saves);
        }
        memcpy(&temp, fbuffer, sizeof(Save));

        if(!strcmp(temp.nome, save->nome)){
            int pos = ftell(saves) - sizeof(Save);
            fclose(saves);
            saves = fopen("saves.txt", "r+");
            fseek(saves, pos, SEEK_SET);

            memcpy(fbuffer, save, sizeof(Save));
            for(int i = 0; i < sizeof(Save); i++){
                fputc(fbuffer[i], saves);
            }

            fclose(saves);
            return true;
        }
    }

    fseek(saves, 0, SEEK_END);
    memcpy(fbuffer, save, sizeof(Save));
    for(int i = 0; i < sizeof(Save); i++){
        fputc(fbuffer[i], saves);
    }

    fclose(saves);
    return true;
}

Save* resgatarSave(char* nome){
    FILE* saves = fopen("saves.txt", "r");

    Save* save = malloc(sizeof(Save));

    char fbuffer[sizeof(Save)];

    fseek(saves, 0, SEEK_END);
    int fim = ftell(saves);
    fseek(saves, 0, SEEK_SET);

    while(ftell(saves) != fim){

        for(int i = 0; i < sizeof(Save); i++){
            fbuffer[i] = fgetc(saves);
        }
        memcpy(save, fbuffer, sizeof(Save));

        if(!strcmp(save->nome, nome)){
            fclose(saves);
            return save;
        }
    }
    fclose(saves);
    return NULL;
}

char* listarSaves(char* usuario){
    FILE* saves = fopen("saves.txt", "r");

    if(saves){

        int rax = 0;
        char* nomes = malloc(sizeof(char));

        Save save;

        char fbuffer[sizeof(Save)];

        fseek(saves, 0, SEEK_END);
        int fim = ftell(saves);
        fseek(saves, 0, SEEK_SET);

        nomes[0] = '\0';
        while(ftell(saves) != fim){

            for(int i = 0; i < sizeof(Save); i++){
                fbuffer[i] = fgetc(saves);
            }
            memcpy(&save, fbuffer, sizeof(Save));

            if(!strcmp(save.usuario, usuario)){
                rax += (strlen(save.nome) + 2) * sizeof(char);
                nomes = realloc(nomes, rax);
                nomes[rax - 1] = '\0';
                strcat(nomes, save.nome);
                strcat(nomes, "\n");
            }
        }

        if(rax == 0){
            return NULL;
        }

        fclose(saves);
        return nomes;
    }
    return NULL;
}
#endif
