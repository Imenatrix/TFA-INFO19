#ifndef CLUBE_H
#define CLUBE_H

typedef struct{

    char nome[30];
    char cidade[30];
    char estadio[30];

} Clube;

Clube newClube(int index, char* nome, char* cidade, char* estadio){
    Clube clube;
    memset(&clube, 0, sizeof(Clube));

    strcpy(clube.nome, nome);
    strcpy(clube.cidade, cidade);
    strcpy(clube.estadio, estadio);

    return clube;
}

#endif
