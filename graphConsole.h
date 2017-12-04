#ifndef GRAPHCONSOLE_H
#define GRAPHCONSOLE_H
#define TAILLE 10

//Fonction Graphique
void printMap(Square map[][TAILLE], Config config);
void clear();
void centrer();
void ligne();
void finLigne();

//TODO Source openclassroom
void couleur();
//retourne la taille x du terminal TODO Mettre en source
int getWidth();

#endif
