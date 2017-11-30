#include <stdio.h>
#include <string.h>

//structure
#include "structure.h"
#include "graphConsole.h"
#include "moteur.h"
#include <unistd.h>

//Random
#include <time.h>
#include <stdlib.h>

#define TAILLE 10 //definie la taille du plateau

/*
30 Noir
31 Rouge
32 Vert
33 Jaune
34 Bleu
35 Magenta
36 Cyan
37 Blanc
*/


int main(int argc, char const *argv[]) {
  srand(time(NULL));
  int squareColor = 33;
  int isPlaying = 1;
  int player = (rand() % (2 - 1 + 1) + 1);
  char msg[50];
  msg[0] = '\0';
  int msgColor = 31;

  Square map[TAILLE][TAILLE];

  // printf("%f\n", abso(-1.0);

  player = 1;

  //Liste des equipe
  Team red = {31, 1};
  Team blue = {34, 2};

  initMap(map);
  initPiece(map, &red, &blue);


  while(isPlaying){
    int x,y;
    int x1,y1;
    int oldCoor[2] = {0,0};

    //TODO: verif si coord est chiffre, ex avec Maxence
    //C'est fait

    printMap(map, squareColor);

    //On affiche le joueur actif
    printf("Joueur %d\n", player);

    //On affiche le msg
    couleur(msgColor);
    printf("%s\n", msg);
    couleur(0);

    //Obtention Coordonnée du pion à bouger
    getCoor(&x, &y);
    //Si le test est 1 c'est un de ses pion, il peux donc le bouger
    if(testCoor(x, y, map, player) == 1){
      //Le Pion lui appartient
      //Test du nombre de coup possible (saut + move)

      if(numJump(x, y, oldCoor, map)+numMove(x, y, map) >= 1){
        couleur(32);
        printf("Vers quel point souhaitez vous le bouger ?\n");
        couleur(0);

        //------- Premier mouvement (Jump/Move) --------------------
        int resMove = 0, resJump = 0;
        do{
          msg[0] = '\0';
          getCoor(&x1, &y1);
          //On test si la case pointer est bien libre et s'il peux y acceder
          resMove = testMove(x, y, x1, y1, map);
          resJump = testJump(x, y, x1, y1,oldCoor, map);
        }while(resMove != 1 && resJump != 1);
        move(&map[x][y], &map[x1][y1], x1, y1);
        printMap(map, squareColor);
        //----------------------------------------------------------

        oldCoor[0] = x;
        oldCoor[1] = y;
        x = x1;
        y = y1;
        int again = 0;

        //repeter tant que un saut est possible
        while(numJump(x, y, oldCoor, map) >= 1 && again == 0 && resMove == 0){
          printf("Souhaitez vous encore sauter ? O/N (%d pos)\n", numJump(x, y, oldCoor, map));
          char rep;
          do{
            scanf("%c", &rep);
          }while(rep != 'O' && rep != 'N');

          //Vide buffer
          int c;
          do {
            c = getchar();
          } while (c != EOF && c != '\n');
          //------------------

          if(rep == 'O'){

            do{
              msg[0] = '\0';
              getCoor(&x1, &y1);
              resJump = testJump(x, y, x1, y1, oldCoor, map);
              printf("oC.x : %d oC.y : %d x : %d y : %d x1 : %d y1 : %d resJump : %d \n", oldCoor[0], oldCoor[1], x, y, x1, y1, resJump);
            }while(resJump != 1 || x1 == oldCoor[0] || y1 == oldCoor[1]);

            move(&map[x][y], &map[x1][y1], x1, y1);
            printMap(map, squareColor);
            oldCoor[0] = x;
            oldCoor[1] = y;
            x = x1;
            y = y1;

          }else{
            again = 1;
          }
        }

        testWin(&isPlaying, map);

        if(player == 1){
          player++;
        }else{
          player--;
        }
      }

    }else{
      msg[0] = '\0';
      msgColor = 31;
      strcpy(msg,"Mauvais pion");
    }
  }

  return 0;
}
