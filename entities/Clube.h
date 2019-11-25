#ifndef CLUBE_H
#define CLUBE_H

typedef struct{

    int pontos;
    int jogos;
    int vitorias;
    int empates;
    int derrotas;
    int gp;
    int gc;
    int sg;
    double mgp;
    double mgc;
    //int m;
    char nome[30];
    char cidade[30];
    char estadio[30];

} Clube;

Clube newClube(char* nome, char* cidade, char* estadio){
    Clube clube;
    memset(&clube, 0, sizeof(Clube));

    strcpy(clube.nome, nome);
    strcpy(clube.cidade, cidade);
    strcpy(clube.estadio, estadio);

    return clube;
}

int* gerarRodada(int offset){

    int *chave = malloc(20 * sizeof(int));

    int coiso;

    for(int i = 0; i < 20; i++){

        if(i == 0){
            chave[i] = i;
        }
        else if(i + offset < 20){
            if(i < 10){
                chave[i] = i + offset;
            }
            else{
                chave[19 - (i - 10)] = i + offset;
            }
            coiso = i;
        }
        else{
            if(i < 10){
                chave[i] = i - coiso;
            }
            else{
                chave[19 - (i - 10)] = i - coiso;
            }
        }

    }

    return chave;

}

#endif
