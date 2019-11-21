#ifndef SAVE_H
#define SAVE_H

typedef struct{

    bool chave[20][20];
    int clubeIndex;
    int rodadaIndex;
    int turnoIndex;
    char nome[30];
    char usuario[12];
    Clube clubes[20];
    Rodada rodadas[2][19];

} Save;

#endif
