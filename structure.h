#ifndef structure_H
#define structure_H

//Structures
typedef struct Team Team;
struct Team{
  int color;
  int numEquip;
  char name[255];
};

typedef struct Piece Piece;
struct Piece{
  int x, y;
  // 3 Dragon / 2 Lion / 1 Singe
  int type;
  struct Team *team;
};

typedef struct Square Square;
struct Square{
  //le pion sur la case, isFill == 0 si aucun
  Piece piece;
  //Type de la case, normal porte (2 red / 3 blue) ou hors plateau (les bords)
  int type;
  //boolean si case porte un pion
  int isFill;
};

#endif
