#ifndef MOVE_H
#define MOVE_H
#define TAILLE 10

int testMove(Coordinate position, Coordinate target, Square map[][TAILLE]);
int numMove(Coordinate position, Square map[][TAILLE]);
void move(Square map[][TAILLE], Coordinate target, Coordinate *position, Coordinate *old);

#endif
