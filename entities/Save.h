#ifndef SAVE_H
#define SAVE_H

typedef struct{

    bool chave;
    int clubeIndex;
    int rodadaIndex;
    int turnoIndex;
    char nome[30];
    Usuario usuario;
    Clube clubes[20];
    Rodada rodadas[2][19];

} Save;

#endif
