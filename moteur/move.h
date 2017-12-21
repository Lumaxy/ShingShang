#ifndef MOVE_H
#define MOVE_H
#define TAILLE 10

int testMove(Coordonnees position, Coordonnees target, Square map[][TAILLE]);
int numMove(Coordonnees position, Square map[][TAILLE]);
void move(Square map[][TAILLE], Coordonnees target, Coordonnees *position, Coordonnees *old);

#endif
