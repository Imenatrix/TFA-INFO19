#ifndef SAVE_H
#define SAVE_H

typedef struct{

    char nome[30];
    char usuario[12];
    int clubeIndex;
    int turnoIndex;
    Turno turnos[2];
    Clube clubes[20];

} Save;

#endif
