#ifndef MOTEUR_H
#define MOTEUR_H
#define TAILLE 10

//Fonction Moteur
void getCoor(Coordonnees *coor);
int testCoor(Coordonnees position, Square map[][TAILLE], int player);

int testMove(Coordonnees position, Coordonnees target, Square map[][TAILLE]);
int testJump(Coordonnees position, Coordonnees target, Coordonnees old, Square map[][TAILLE]);

int numMove(Coordonnees position, Square map[][TAILLE]);
int numJump(Coordonnees position, Coordonnees old, Square map[][TAILLE]);

int distance(Coordonnees position, Coordonnees target);
float abso(float x);


void move(Square map[][TAILLE], Coordonnees target, Coordonnees *position, Coordonnees *old);
void testWin(int *isplaying, Square map[][TAILLE]);

//Init
void initPiece(Square map[][TAILLE], Team *red, Team *blue);
void initMap(Square map[][TAILLE]);

int clearBuffer();

#endif
