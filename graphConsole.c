#include <stdio.h>
#include "structure.h"
#include "graphConsole.h"
#include <unistd.h>

/*
30 Noir
31 Rouge
32 Vert
33 Jaune
34 Bleu
35 Magenta
36 Cyan
37 Blanc

40 Gris
42 Vert
41 Rouge
43 Jaune
44 Bleu
45 Magenta
46 Cyan
47 Blanc
48 transparant
*/

/* ------------------------------------------ LINUX -------------------------------------*/
// #ifdef __unix__
#include <stdlib.h>
#include <string.h>

//getWidth Linux
#include <sys/ioctl.h>

int getWidth()  {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
}

int getHeight()  {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_row;
}

void couleur(int couleur){
  printf("\033[%dm", couleur);
}

void clear() {
  printf("\033[H\033[2J");
}

void ligne(Config config){
  int i;
  int espace = getWidth();

  couleur(config.frameColor);
  for(i = 0; i < espace; i++){
    printf(" ");
  }
  couleur(0);
}

void printCoor(Config config){
  int i;
  centrer(config);
  couleur(config.frameColor);
  printf("  ");
  for(i = 0; i < 9; i++){
    printf("%c%c", i + 48, ' ');
  }
  printf("9");
  couleur(31);
  printf(" X  ");
  couleur(0);

  /* FIN DE LIGNE */
  int espace = (getWidth() / 2) - (TAILLE + 4) - 4;

  if(espace%2 == 0){
    espace--;
  }

  couleur(config.frameColor);
  for(i = 0; i < espace+6; i++){
    printf(" ");
  }
  couleur(0);
  /* ------------ */

}
/* --------------------------------------------------------------------------------------- */

/* ------------------------------------- WINDOWS ----------------------------------------- */
// #elif defined(_WIN32) || defined(WIN32)
//
// #include <windows.h>
// #include <tchar.h>
// #define DIV 1048576
//
// int getWidth() {
//   CONSOLE_SCREEN_BUFFER_INFO csbi;
//   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
//   return csbi.srWindow.Right - csbi.srWindow.Left + 1;
// }
//
// void couleur(int couleur){}
// void clear(Config config){}
// void ligne(config config){}
// #endif
/* ---------------------------------------------------------------------------------------- */


#define TAILLE 10

//Fonction graphique
void centrer(Config config){
  int i;
  int espace = (getWidth() / 2) - (TAILLE) - 2;
  couleur(config.frameColor);
  for(i = 0; i < espace; i++){
    printf(" ");
  }
  couleur(0);
}

void finLigne(Config config){
  int i;
  int espace = (getWidth() / 2) - (TAILLE + 4);

  if(espace%2 == 0){
    espace--;
  }

  couleur(config.frameColor);
  for(i = 0; i < espace+6; i++){
    printf(" ");
  }
  couleur(0);
}

void printSquare(Square square, Config config){
  switch(square.type){
    //Hors plateau
    case -1:
    couleur(config.frameColor);
    printf(" ");
    break;
    //Normal
    case 0:
    //Case Pleine ?
    if(square.isFill == 1){
      couleur(square.piece.team->color);
      //type du pion?
      int type = square.piece.type;
      if(type == 1){
        printf("S");
      }else if(type == 2){
        printf("L");
      }else if(type == 3){
        printf("D");
      }
    }else{
      couleur(config.squareColor);
      // char sqr = config.squareChar;
      printf("%c",config.squareChar);
    }
    break;
    case 2:
    if(square.isFill == 1){
      couleur(square.piece.team->color);
      int type = square.piece.type;
      if(type == 1){
        printf("S");
      }else if(type == 2){
        printf("L");
      }else if(type == 3){
        printf("D");
      }
    }else{
      couleur(config.colorTeam1);
      printf("P");
    }
    break;
    case 3:
    if(square.isFill == 1){
      couleur(square.piece.team->color);
      int type = square.piece.type;
      if(type == 1){
        printf("S");
      }else if(type == 2){
        printf("L");
      }else if(type == 3){
        printf("D");
      }
    }else{
      couleur(config.colorTeam2);
      printf("P");
    }
    break;
  }
}

void printMap(Square map[][TAILLE], Config config){
  int x, y;

  clear();

  ligne(config);
  ligne(config);
  printCoor(config);

  //--------------------Parcous tableau---------------------
  for(y = 0; y < TAILLE; y++){
    centrer(config);
    couleur(config.frameColor);
    printf("%d ", y);
    couleur(0);
    for(x = 0; x < TAILLE; x++){
      if(x != 0){
        printf(" ");
      }
      //Test du type de la case eet action en consquence
      printSquare(map[x][y], config);
      couleur(0);
    }
    finLigne(config);
    printf("\n");
  }
  // ---------------------------------------------------

  //Affiche le Y en bas
  centrer(config);
  couleur(config.frameColor);
  couleur(31);
  printf("Y");
  for(x = 0; x < TAILLE; x++){
    printf("  ");
  }
  couleur(0);
  finLigne(config);
  //---------------------

  //ligne du bas
  ligne(config);
  ligne(config);
  printf("\n");
}
