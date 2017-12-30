#include "../structure.h"
#include "../language.h"
#include "jump.h"
#include "calcul.h"

#include <stdio.h>
#define TAILLE 10

int numJump(Coordinate position, Coordinate old, Square map[][TAILLE]){
  int res = 0, i, j;
  for(i = position.x - 2; i <= position.x + 2; i++){
    for(j = position.y - 2; j <= position.y + 2; j++){
      Coordinate tmp = {i, j};
      if(testJump(position, tmp, old, map) == 1){
        res++;
      }
    }
  }
  return res;
}

int testJump(Coordinate position, Coordinate target, Coordinate old, Square map[][TAILLE]){
  // -1 pour trop loin, -2 pour ancienne coor, 1 possible, 0 sinon
  int res = 0;
  Piece p = map[position.x][position.y].piece;

  //verif de la case visee (dans le plateau?)
  if(target.x >= 0 && target.y >= 0 && target.x <= 9 && target.y <= 9){
    if(map[target.x][target.y].type >= 0 && map[target.x][target.y].isFill == 0){
      //Pas les anciennes coord
      if(old.x == target.x && old.y == target.y){
        res = -2;
      }else{
        //La distance en diagonal == 8 (je fais tout au carre pour limiter les calculs)
        if(distance(position, target) == 2*2 || distance(position, target) == 8){
          int xMoy = (position.x + target.x) / 2;
          int yMoy = (position.y + target.y) / 2;
          if(map[xMoy][yMoy].isFill == 1){
            Piece p2 = map[xMoy][yMoy].piece;
            if(p.type >= p2.type){
              //possibilité de sauter
              res = 1;
            }
          }
        }else{
          res = -1;
        }
      }
    }
  }
  return res;
}
