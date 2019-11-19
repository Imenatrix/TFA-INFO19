#ifndef SAVE_H
#define SAVE_H

typedef struct{

    int clubeIndex;
    int rodadaIndex;
    int turnoIndex;
    char nome[30];
    usuario coiso;
    clube clubes[20];
    rodada rodadas[2][19];

} save;

#endif
