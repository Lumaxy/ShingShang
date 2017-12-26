#include "../structure.h"
#include "../language.h"
#include "coor.h"
#include "../graphConsole.h"
#include "moteur.h"

#include <stdio.h>

void getCoor(Coordonnees *coor){
  char xChar, yChar;
  int nbCarAfter = 0;
  coor->x = -1;
  coor->y = -1;
    do{
      printf(COOR_1);
      scanf("%c", &xChar);

      nbCarAfter = clearBuffer();

      if((int)xChar >= 48 && (int)xChar <= 57 && nbCarAfter == 0){
        coor->x = (int)xChar - 48;
      }else{
        couleur(31);
        printf("Format incorrect.\n");
        couleur(0);
      }
    }while(coor->x < 0 || coor->x > 9);

    do{
      printf("Entrez y :\n");
      scanf("%c", &yChar);

      nbCarAfter = clearBuffer();

      if((int)yChar >= 48 && (int)yChar <= 57 && nbCarAfter == 0){
        coor->y = (int)yChar - 48;
      }else{
        couleur(31);
        printf("Format incorrect.\n");
        couleur(0);
      }
    }while(coor->y < 0 || coor->y > 9);
}

int testCoor(Coordonnees position, Square map[][TAILLE], int player){
  int res = -1;
  Square tmp = map[position.x][position.y];
  //Case potable ?
  if(tmp.type == 0){
    //Case pleine ?
    if(tmp.isFill == 1){
      Piece p = tmp.piece;
      //Le pion lui appartient ?
      if(p.team.numEquip == player){
        res = 1;
      }else{
        res = 2;
      }
    }
  }
  return res;
}
