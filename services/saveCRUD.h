#ifndef SAVECRUD_H
#define SAVECRUD_H

bool Salvar(save _save){
    FILE *saves;
    saves = fopen("saves.bin", "rb+");

    save vSave;
    memset(&vSave, 0, sizeof(save));

    while(fread(&vSave, sizeof(save), 1, saves)){
        if(!strcmp(vSave.nome, _save.nome)){
            vSave = _save;
            fseek(saves, -sizeof(save), SEEK_CUR);
            fwrite(&vSave, sizeof(save), 1, saves);
            fclose(saves);
            return true;
        }
    }

    vSave = _save;
    fwrite(&vSave, sizeof(save), 1, saves);

    fclose(saves);
    return true;
}

bool removerSave(save _save){
    FILE *saves = fopen("saves.bin", "rb+");

    save vSave;
    memset(&vSave, 0, sizeof(save));

    fseek(saves, 0, SEEK_END);
    int tam = ftell(saves) - sizeof(save);
    fseek(saves, 0, SEEK_SET);

    while(fread(&vSave, sizeof(save), 1, saves)){
        if(!strcmp(vSave.nome, _save.nome)){
            if(ftell(saves) - sizeof(save) == tam){
                ftruncate(fileno(saves), tam);
            }
            else{
                int pos = ftell(saves) - sizeof(save);

                fseek(saves, -sizeof(save), SEEK_END);
                fread(&vSave, sizeof(save), 1, saves);

                fseek(saves, pos, SEEK_SET);
                fwrite(&vSave, sizeof(save), 1, saves);
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

save* listarSaves(){
    FILE* saves = fopen("saves.bin", "rb");

    int index = 0;
    save* vSave = malloc(sizeof(save));

    while(fread(&vSave[index], sizeof(save), 1, saves)){
        index++;
        vSave = realloc(vSave, (index + 1) * sizeof(save));
    }

    for(int i = 0; i < index; i++){
        for(int j = index - i; j < index; j++){
            if(strcmp(vSave[i].nome, vSave[j].nome) < 0){
                save aux;
                aux = vSave[i];
                vSave[i] = vSave[j];
                vSave[j] = aux;
            }
        }
    }

    //gambiarra?
    vSave[index].clubeIndex = -1;
    fclose(saves);
    return vSave;
}
#endif
