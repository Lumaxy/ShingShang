#include "../structure.h"
#include "calcul.h"
#include "move.h"
#include <stdio.h>
#define TAILLE 10

int numMove(Coordinate position, Square map[][TAILLE]){
  int res = 0;
  int i, j;

  for(i = position.x - 2; i <= position.x + 2; i++){
    for(j = position.y -2; j <= position.y + 2; j++){
      Coordinate tmp = {i, j};
      if(testMove(position, tmp, map) == 1){
        res++;
      }
    }
  }
  return res;
}

//Check si le deplacement est autorise : 1 si oui, 0 sinon.
int testMove(Coordinate position, Coordinate target, Square map[][TAILLE]){
  int res = 0;
  int tmp = 0; //Permet de ne pas repeter le test du coef directeur

  if(target.x >= 0 && target.y >= 0 && target.x <= 9 && target.y <= 9){
    Square caseVisee = map[target.x][target.y];
    //test du type de la map
    if(caseVisee.type == 0){
      //La case est elle occupé?
      if(caseVisee.isFill == 0){
        //Mouvement autoriser selon le pion?
        Piece p1 = map[position.x][position.y].piece;
        switch(p1.type){
          //Singe mouvement de deux case dans la même direction
          case 1:
          if((distance(position, target) == 2*2 || distance(position, target) == 8) && map[(position.x + target.x) / 2][(position.y + target.y) / 2].isFill == 0){
            tmp = 1;
          }else if(distance(position, target) == 1 || distance(position, target) == 2 /* Cas spécial en diagonal*/){
            res = 1;
          }
          if(tmp == 1){
            // Direction. cas particulier de droite x = k
            if(target.x == position.x){
              res = 1;
            }else{
              float coef = (target.y - position.y) / (target.x - position.x); //coef directeur
              if(abso(coef) == 1 || coef == 0){
                res = 1;
              }
            }
          }
          break;
          //Lion 1 case
          case 2:
          if(distance(position, target) == 1 || distance(position, target) == 2 /* Cas spécial en diagonal*/){
            res = 1;
          }
          break;
          //dragon = 0 car aucun deplacement
        }
      }
    }
  }
  return res;
}

void move(Square map[][TAILLE], Coordinate target, Coordinate *position, Coordinate *old){
  Piece p = map[position->x][position->y].piece; //Le pion a la position
  p.position.x = target.x; //Nouvelle position
  p.position.y = target.y;

  map[target.x][target.y].piece = p;
  map[target.x][target.y].isFill = 1;
  map[position->x][position->y].isFill = 0;

  //Update des coord
  old->x = position->x;
  old->y = position->y;
  position->x = target.x;
  position->y = target.y;
}
