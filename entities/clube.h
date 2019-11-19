#ifndef CLUBE_H
#define CLUBE_H

typedef struct{

    char nome[30];
    char cidade[30];
    char estadio[30];

} clube;

clube Clube(int index, char* nome, char* cidade, char* estadio){
    clube temp;
    memset(&temp, 0, sizeof(clube));

    strcpy(temp.nome, nome);
    strcpy(temp.cidade, cidade);
    strcpy(temp.estadio, estadio);

    return temp;
}

#endif
