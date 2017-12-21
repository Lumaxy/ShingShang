#include <stdio.h>
#include "../structure.h"
#include "moteur.h"
#define TAILLE 10

//Fonction Moteur
void testWin(int *isPlaying, Square map[][TAILLE]){
  //Portail rempli par un dragon de sa couleur ?
  int team = 1;
  int x, y;
  for(y = 1; y < 9; y+=7){
    team++;
    for(x = 4; x <= 5; x++){
      if(map[x][y].isFill == 1){
        if(map[x][y].piece.type == 3){
          if(map[x][y].piece.team->numEquip != team){
            *isPlaying = 0;
            printf("Victoire de l'équipe %s\n", map[x][y].piece.team->name);
          }
        }
      }
    }
  }
}

int clearBuffer(){
  //Vide buffer
  int c;
  int cpt = 0;
  do {
    c = getchar();
    cpt++;
  } while (c != EOF && c != '\n');
  //------------------
  return cpt - 1;
}
