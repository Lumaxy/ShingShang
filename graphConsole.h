#ifndef GRAPHCONSOLE_H
#define GRAPHCONSOLE_H
#define TAILLE 10

#include "structure.h"

//Fonction Graphique
void printMap(Square map[][TAILLE], Config config);
void clear();
void centrer(Config config);
void ligne(Config config);
void finLigne(Config config);

//TODO Source openclassroom
void couleur();
//retourne la taille x du terminal TODO Mettre en source
int getWidth();
int getHeight();

#endif
