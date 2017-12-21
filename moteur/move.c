#include "../structure.h"
#include "calcul.h"
#include "move.h"
#define TAILLE 10

//Check si le deplacement es tautorise : 1 si oui, 0 sinon.
int testMove(Coordonnees position, Coordonnees target, Square map[][TAILLE]){
  int res = 0;
  int tmp = 0; //Permet de ne pas repeter le test du coef directeur

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
        if(distance(position, target) == 2*2 && map[(position.x + target.x) / 2][(position.y + target.y) / 2].isFill == 0){
          tmp = 1;
        }else if(distance(position, target) == 1 || distance(position, target) == 2 /* Cas spécial en diagonal*/){
          tmp = 1;
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
        if(distance(position, target) == 1){
          res = 1;
        }
        break;
        //dragon = 0 car aucun deplacement
      }
    }
  }

  return res;
}
int numMove(Coordonnees position, Square map[][TAILLE]){
  int res = 0;
  int i, j;

  for(i = position.x - 1; i <= position.x + 1; i++){
    for(j = position.y -1; j <= position.y + 1; j++){
      //On test si les nouvelles coordonnées ne débordent pas du tableau et differente du centre
      if(i >= 0 && i <= 9 && j >= 0 && j <= 9){
        //coord differente du centre
        if(!(i == position.x && j == position.y)){
          Square tmp = map[i][j];
          //test du type de la map
          if(tmp.type >= 0){
            //La case est elle occupé?
            if(tmp.isFill == 0){
              res++;
            }
          }
        }
      }
    }
  }
  return res;
}
void move(Square map[][TAILLE], Coordonnees target, Coordonnees *position, Coordonnees *old){
  Piece p = map[position->x][position->y].piece; //Le pion a la position
  p.x = target.x; //Nouvelle position
  p.y = target.y;

  map[target.x][target.y].piece = p;
  map[target.x][target.y].isFill = 1;
  map[position->x][position->y].isFill = 0;

  //Update des coord
  old->x = position->x;
  old->y = position->y;
  position->x = target.x;
  position->y = target.y;
}
