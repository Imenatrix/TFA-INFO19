#ifndef CLUBE_RANKING_H
#define CLUBE_RANKING_H

typedef struct{

    Clube* clube;
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
    int lastPos;

} ClubeRanking;

#endif