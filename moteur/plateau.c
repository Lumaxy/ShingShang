#include "../structure.h"
#include "plateau.h"

void initPiece(Square map[][TAILLE], Team *red, Team *blue){
  int x,y;

  //Haut Gauche
  for(y = 0; y < 3; y++){
    for(x = 1; x < 4 - y; x++){
      Piece p = {x, y, 4 - (x + y), red};
      map[x][y].piece = p;
      map[x][y].isFill = 1;
    }
  }

  //Haut Droite
  for(y = 0; y < 3; y++){
    for(x = 8; x > 5 + y ; x--){
      Piece p = {x, y, x - (5+y), red};
      map[x][y].piece = p;
      map[x][y].isFill = 1;
    }
  }

  // bas Gauche
  for(y = 7; y < 10; y++){
    for(x = 1; x < y - 5; x++){
      Piece p = {x, y, (y-x)-5, blue};
      map[x][y].piece = p;
      map[x][y].isFill = 1;
    }
  }

  // bas Droite
  for(y = 7; y < 10; y++){
    for(x = 8; x > 14 - y; x--){
      Piece p = {x, y, (x+y) - 14, blue};
      map[x][y].piece = p;
      map[x][y].isFill = 1;
    }
  }
}
void initMap(Square map[][TAILLE]){
  int x, y;

  //Création de toutes les cases
  for(x = 0; x < TAILLE; x++){
    for(y = 0; y < TAILLE; y++){
      Square tmp;
      tmp.isFill = 0;
      tmp.type = 0;
      map[x][y] = tmp;
    }
  }

  //Bordure hors plateau
  for(x = 0; x < TAILLE; x+=9){
    for(y = 0; y < TAILLE; y++){
      map[x][y].type = -1;
    }
  }

  //bordure Normal
  map[0][4].type = 0;
  map[0][5].type = 0;
  map[9][4].type = 0;
  map[9][5].type = 0;

  //porte
  int team = 1;
  for(y = 1; y < 9; y+=7){
    team++;
    for(x = 4; x <= 5; x++){
      map[x][y].type = team;
    }
  }
}
