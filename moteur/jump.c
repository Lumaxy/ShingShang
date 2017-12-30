#include "../structure.h"
#include "../language.h"
#include "jump.h"
#include "calcul.h"

#include <stdio.h>
#define TAILLE 10

int numJump(Coordinate position, Coordinate old, Square map[][TAILLE]){
  int res = 0, i, j;
  Square center = map[position.x][position.y];

  for(i = position.x -1; i <= position.x + 1; i++){
    for(j = position.y -1; j <= position.y + 1; j++){
      //On test si les nouvelles coordonnées ne débordent pas du tableau et differente du centre
      if(i >= 0 && i <= 9 && j >= 0 && j <= 9){
        //coord differente du centre
        if(!(i == position.x && j == position.y)){
          Square tmp = map[i][j];
          //test du type de la case/ La case est elle occupé?
          if(tmp.type >= 0 && tmp.isFill == 1){
            Piece tmpP = tmp.piece;
            //Le pion est il plus petit ou de meme taille ?
            if(tmpP.type <= center.piece.type){
              //test des coor opposer, si elle sont bien dsans la grille
              int xA = (2*i)-position.x;
              int yA = (2*j)-position.y;
              if(xA >= 0 && xA <= 9 && yA >= 0 && yA <= 9  && !(xA == old.x && yA == old.y)){
                // si possible
                if(map[xA][yA].type >= 0){
                  // si vide
                  if(map[xA][yA].isFill == 0){
                    res++;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return res;
}

//TODO: quand je choisis de nouveau la case il me change les coordonnées
// et du coup ma case devient isFill == 0
int testJump(Coordinate position, Coordinate target, Coordinate old, Square map[][TAILLE]){
  int res = 0;
  // center = map[x][y];
  Piece p = map[position.x][position.y].piece;
  //verif de la case visee
  if(target.x >= 0 && target.y >= 0 && target.x <= 9 && target.y <= 9){
    if(map[target.x][target.y].type >= 0){

      if(old.x == target.x && old.y == target.y){
        printf(ERR_JUMP_BACK);
      }else{
        if(distance(position, target) == 2*2 || distance(position, target) == 8){
          int xMoy = (position.x + target.x) / 2;
          int yMoy = (position.y + target.y) / 2;
          Piece p2 = map[xMoy][yMoy].piece;

          if(p.type >= p2.type){
            //possibilité de sauter
            res = 1;
          }
        }else{
          printf(ERR_JUMP_DISTANCE);
        }
      }
    }
  }
  return res;
}
