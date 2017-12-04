#include <stdio.h>
#include "structure.h"
#include "graphConsole.h"
#include <unistd.h>

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */

#include <stdlib.h>
#include <string.h>

//getWidth Linux
#include <sys/ioctl.h>

int getWidth()  {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
}
void couleur(int couleur){
  printf("\033[%dm", couleur);
}
void clear() {
  printf("\033[H\033[2J");
}
void ligne(){
  int i;
  int espace = getWidth();

  couleur(47);
  for(i = 0; i < espace; i++){
    printf(" ");
  }
  couleur(0);
}

#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

#include <windows.h>
#include <tchar.h>
#define DIV 1048576

int getWidth() {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
void couleur(int couleur){}
void clear(){}
void ligne(){}
#endif

#define TAILLE 10

//Fonction graphique
void centrer(){
  int i;
  int espace = (getWidth() / 2) - (TAILLE);

  couleur(47);
  for(i = 0; i < espace; i++){
    printf(" ");
  }
  couleur(0);
}

void finLigne(){
  int i;
  int espace = (getWidth() / 2) - (TAILLE + 4);

  couleur(47);
  for(i = 0; i < espace+6; i++){
    printf(" ");
  }
  couleur(0);
}



void printMap(Square map[][TAILLE], int squareColor){
  int x, y;

  clear();

  ligne();
  ligne();

  //--------------------Parcous tableau---------------------
  for(y = 0; y < TAILLE; y++){
    centrer();
    for(x = 0; x < TAILLE; x++){
      if(x != 0){
        printf(" ");
      }
      //Test du type de la case eet action en consquence
      switch(map[x][y].type){
        //Hors plateau
        case -1:
        couleur(47);
        printf(" ");
        break;
        //Normal
        case 0:
        //Case Pleine ?
        if(map[x][y].isFill == 1){
          couleur(map[x][y].piece.team->color);
          //type du pion?
          int type = map[x][y].piece.type;
          if(type == 1){
            printf("S");
          }else if(type == 2){
            printf("L");
          }else if(type == 3){
            printf("D");
          }
        }else{
          couleur(squareColor);
          printf("0");
        }
        break;
        case 2:
        if(map[x][y].isFill == 1){
          couleur(map[x][y].piece.team->color);
          int type = map[x][y].piece.type;
          if(type == 1){
            printf("S");
          }else if(type == 2){
            printf("L");
          }else if(type == 3){
            printf("D");
          }
        }else{
          couleur(31);
          printf("P");
        }
        break;
        case 3:
        if(map[x][y].isFill == 1){
          couleur(map[x][y].piece.team->color);
          int type = map[x][y].piece.type;
          if(type == 1){
            printf("S");
          }else if(type == 2){
            printf("L");
          }else if(type == 3){
            printf("D");
          }
        }else{
          couleur(34);
          printf("P");
        }
        break;
      }
      couleur(0);
    }
    finLigne();
    printf("\n");
  }
  // ---------------------------------------------------

  //ligne du bas
  ligne();
  ligne();
  printf("\n");
}
/*
int getWidth(){
struct winsize w;
ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
return w.ws_col;
}
*/
