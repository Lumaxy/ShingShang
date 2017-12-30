#include "../language.h"
#include "../structure.h"
#include "../graphConsole.h"
#include "moteur.h"

#include <stdio.h>
#define TAILLE 10

//Fonction Moteur
void testWin(int *isPlaying, Square map[][TAILLE]){
  //Portail rempli par un dragon de sa couleur ?
  int x, y;

  for(y = 1; y < 9; y+=7){
    for(x = 4; x <= 5; x++){
      if(map[x][y].isFill == 1){
        if(map[x][y].piece.type == 3 && map[x][y].piece.team.teamNum == map[x][y].type){
          *isPlaying = 0;
          printf(VICTORY, map[x][y].piece.team.name);
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
int answer(const char question[255]){
  char rep;
  int res = 0;
  printf("%s\n", question);
  do{
    scanf("%c", &rep);
  }while(rep != 'O' && rep != 'N' && rep != 'o' && rep != 'n');
  clearBuffer();
  if(rep == 'O' || rep == 'o'){
    res = 1;
  }
  return res;
}

int choix(int i){
  char xChar;
  int nbAfter = 0;
  int x = -1;
  do{
    printf(CHOICE);
    scanf("%c", &xChar);

    nbAfter = clearBuffer();

    if((int)xChar >= 48 && (int)xChar <= 57 && nbAfter == 0){
      x = (int)xChar - 48;
    }else{
      couleur(31);
      printf(ERR_FORMAT);
      couleur(0);
    }
  }while(x < 1 || x > i);
  return x;
}

void codeMap(Square map[TAILLE][TAILLE], Square buffer[TAILLE*TAILLE]){
  int x, y;

  for(y = 0; y < TAILLE; y++){
    for(x = 0; x < TAILLE; x++){
      buffer[x * TAILLE + y] = map[x][y];
    }
  }
}

void decodeMap(Square map[TAILLE][TAILLE], Square buffer[TAILLE*TAILLE]){
  int x, y;

  for(y = 0; y < TAILLE; y++){
    for(x = 0; x < TAILLE; x++){
      map[x][y] = buffer[x * TAILLE + y];
    }
  }
}
