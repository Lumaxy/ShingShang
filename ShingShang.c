/*
###################################
# Nom du projet : ShingShang      #
# Auteur : Maxence Morin          #
# Version : v1.0                  #
###################################
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "structure.h"
#include "graphConsole.h"
#include "moteur.h"
#include "io.h"

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

/*
###################DEBUG####################
printf("Jump distance(p, x1, y1) : %d\n", distance(p, x1, y1));
printf("oC.x : %d oC.y : %d x : %d y : %d x1 : %d y1 : %d resJump : %d \n", oldCoor[0], oldCoor[1], x, y, x1, y1, resJump);
############################################
*/


int main(int argc, char const *argv[]) {
  Config config;
  loadConfig(&config);
  srand(time(NULL));
  int isPlaying = 1; //tant que personne ne gagne, isPlaying = 1
  int player = (rand()% 2) + 1; // Premier joueur a jouer
  //Message indicatif pour le joueur
  char msg[50];
  msg[0] = '\0';
  int msgColor = 31;
  int nbDragRed = 2;
  int nbDragBlue = 2;

  Square map[TAILLE][TAILLE]; // Plateau de jeu

  //A SUPPRIMER
  player = 1; // Forcer le premier joueur pour les test

  //Liste des equipe
  Team red = {31, 1, "Les tigres"};
  Team blue = {34, 2, "Les pieuvres"};

  initMap(map);
  initPiece(map, &red, &blue);

  //Chaque boucle correspond a un tour.
  while(isPlaying && nbDragRed > 0 && nbDragBlue > 0){
    int x,y; //Coordonnees actuelle
    int x1,y1; //Coordonnees visees
    int oldCoor[2] = {0,0}; //Coordonnees de la derniere case
    int sautTotal = 0; //Nombre de saut effectuer dans un tour

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
          //Permet d'eviter que le pion apres avoir bouger puisse sauter
          if(resMove == 0){
            resJump = testJump(x, y, x1, y1,oldCoor, map);
          }
        }while(resMove != 1 && resJump != 1);
        if (resJump == 1) {
          sautTotal++;
        }
        move(&map[x][y], &map[x1][y1], x1, y1);
        printMap(map, squareColor);
        //----------------------------------------------------------

        oldCoor[0] = x;
        oldCoor[1] = y;
        x = x1;
        y = y1;

        //--------- Suite de saut ---------------------------------------
        int again = 0;
        while(numJump(x, y, oldCoor, map) >= 1 && again == 0 && resMove == 0){
          printf("Souhaitez vous encore sauter ? O/N (%d pos)\n", numJump(x, y, oldCoor, map));

          //Obtention de la reponse du joueur
          char rep;
          do{
            scanf("%c", &rep);
          }while(rep != 'O' && rep != 'N' && rep != 'o' && rep != 'n');
          clearBuffer();
          //----------------------------------

          if(rep == 'O'){
            do{
              msg[0] = '\0';
              //Recup des nouvelle Coordonnees
              getCoor(&x1, &y1);
              resJump = testJump(x, y, x1, y1, oldCoor, map);
              printf("oC.x : %d oC.y : %d x : %d y : %d x1 : %d y1 : %d resJump : %d \n", oldCoor[0], oldCoor[1], x, y, x1, y1, resJump);
            }while(resJump != 1 || (x1 == oldCoor[0] && y1 == oldCoor[1]));
            //Execution
            move(&map[x][y], &map[x1][y1], x1, y1);
            sautTotal++;
            if (sautTotal >= 2) {
              //Alors on supprime le pion de la case au milieu Si le pion est de l'equipe adverse
              if(map[(x+x1)/2][(y+y1)/2].piece.team->numEquip != player){
                map[(x+x1)/2][(y+y1)/2].isFill = 0;

                //saut d'un dragon?
                if(map[(x+x1)/2][(y+y1)/2].piece.type == 3){
                  if(map[(x+x1)/2][(y+y1)/2].piece.team->numEquip == 1){
                    nbDragRed--;
                  }else{
                    nbDragBlue--;
                  }
                }
                //----------------
              }
            }
            printMap(map, squareColor);

            oldCoor[0] = x;
            oldCoor[1] = y;
            x = x1;
            y = y1;

          }else{
            again = 1;
          }
        }
        //--------------------------------------------------------------

        testWin(&isPlaying, map);

        //Changement de joueur
        if(player == 1){
          player++;
        }else{
          player--;
        }
        //--------------------
      }

    }else{
      msg[0] = '\0';
      msgColor = 31;
      strcpy(msg,"Mauvais pion");
    }
  }
  char victoryName[255];
  if(isPlaying != 0){
    if(nbDragRed == 0){
      couleur(blue.color);
      strcpy(victoryName, blue.name);
    }else{
      couleur(red.color);
      strcpy(victoryName, blue.name);
    }

    printf("Victoire de l'équipe ");
    printf("%s\n", victoryName);
    couleur(0);
  }

  return 0;
}
