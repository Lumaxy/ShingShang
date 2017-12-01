#ifndef MOTEUR_H
#define MOTEUR_H
#define TAILLE 10

//Fonction Moteur
void getCoor(int *x, int *y);
int testCoor(int x, int y, Square map[][TAILLE], int player);

int testMove(int x, int y, int x1, int y1, Square map[][TAILLE]);
int testJump(int x, int y, int x1, int y1, int oldCoor[2], Square map[][TAILLE]);

int numMove(int x, int y, Square map[][TAILLE]);
int numJump(int x, int y, int oldCoor[2], Square map[][TAILLE]);

int distance(Piece p1, int x1, int y1);
float abso(float x);

void move(Square *s1, Square *s2, int x, int y);
void testWin(int *isplaying, Square map[][TAILLE]);

//Init
void initPiece(Square map[][TAILLE], Team *red, Team *blue);
void initMap(Square map[][TAILLE]);

void clearBuffer();

#endif
