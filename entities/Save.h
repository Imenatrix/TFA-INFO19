#ifndef SAVE_H
#define SAVE_H

typedef struct{

    char nome[30];
    char usuario[12];
    int clubeIndex;
    //int rodadaIndex;
    Clube clubes[20];
    ///Rodada rodadas[2][19];
    bool chave[20][20];

} Save;

#endif
