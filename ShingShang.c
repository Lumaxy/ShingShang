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
#include "menu.h"

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

/*
###################DEBUG####################
printf("Jump distance(p, x1, y1) : %d\n", distance(p, x1, y1));
printf("oC.x : %d oC.y : %d x : %d y : %d x1 : %d y1 : %d resJump : %d \n", oldCoor[0], oldCoor[1], x, y, x1, y1, resJump);
############################################
*/


int main(int argc, char const *argv[]) {

  //TODO Menu pour choisir console / sdl / config
  //TODO faire de ne pas terminer sur un portail a la fin d'un tour
  //TODO changer de bushi si saut d'un adversaire

  //Initialisation des variables ---------------------------------
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
  //-----------------------------------------------------------------

  //Liste des équipes -------------------
  Team red;
  red.numEquip = 1;
  red.color = config.colorTeam1;
  strcpy(red.name, config.nameTeam1);
  Team blue;
  blue.numEquip = 2;
  blue.color = config.colorTeam2;
  strcpy(blue.name, config.nameTeam2);
  //--------------------------------------

  Square map[TAILLE][TAILLE]; // Plateau de jeu
  switch(menu()){
    case 1:
    initMap(map);
    initPiece(map, &red, &blue);
    saveGame(map);
    break;

    case 2:
    loadGame(map, &red, &blue);
    break;

    case 3:

    break;

    case 4:

    break;
  }

  //TODO A SUPPRIMER
  player = 1; // Forcer le premier joueur pour les test

  //Chaque boucle correspond a un tour.
  while(isPlaying && nbDragRed > 0 && nbDragBlue > 0){
    Coordonnees position; //Coordonnees actuelle
    Coordonnees target; //Coordonnees visees
    Coordonnees old = {0,0}; //Coordonnees de la derniere case
    int sautTotal = 0; //Nombre de saut effectuer dans un tour

    printMap(map, config);

    //On affiche le joueur actif
    printf("Joueur %d\n", player);

    //On affiche le msg
    couleur(msgColor);
    printf("%s\n", msg);
    couleur(0);

    //Obtention Coordonnée du pion à bouger
    getCoor(&position);

    //Si le test est 1 c'est un de ses pion, il peux donc le bouger
    if(testCoor(position, map, player) == 1){

      //Test du nombre de coup possible (saut + move)
      if(numJump(position, old, map)+numMove(position, map) >= 1){
        couleur(32);
        printf("Vers quel point souhaitez vous le bouger ?\n");
        couleur(0);

        //------- Premier mouvement (Jump/Move) --------------------
        int resMove = 0, resJump = 0;
        do{
          msg[0] = '\0';
          getCoor(&target);
          //On test si la case pointer est bien libre et s'il peux y acceder
          resMove = testMove(position, target, map);
          //Permet d'eviter que le pion apres avoir bouger puisse sauter
          if(resMove == 0){
            resJump = testJump(position, target, old, map);
          }
        }while(resMove != 1 && resJump != 1);
        if (resJump == 1) {
          sautTotal++;
        }
        move(map, target, &position, &old);
        printMap(map, config);
        //----------------------------------------------------------

        //--------- Suite de saut ---------------------------------------
        int again = 0;
        while(numJump(position, old, map) >= 1 && again == 0 && resMove == 0){
          printf("Souhaitez vous encore sauter ? O/N (%d pos)\n", numJump(position, old, map));

          //Obtention de la reponse du joueur--
          char rep;
          do{
            scanf("%c", &rep);
          }while(rep != 'O' && rep != 'N' && rep != 'o' && rep != 'n');
          clearBuffer();
          //-----------------------------------

          if(rep == 'O'){
            do{
              msg[0] = '\0';
              //Recup des nouvelle Coordonnees
              getCoor(&target);
              resJump = testJump(position, target, old, map);
            }while(resJump != 1 || (target.x == old.x && target.y == old.y));
            //Execution
            move(map, target, &position, &old);
            sautTotal++;
            if (sautTotal >= 2) {
              //Alors on supprime le pion de la case au milieu Si le pion est de l'equipe adverse
              if(map[(position.x + target.x) / 2][(position.y + target.y) / 2].piece.team->numEquip != player){
                map[(position.x + target.x) / 2][(position.y + target.y) / 2].isFill = 0;

                //saut d'un dragon?
                if(map[(position.x + target.x) / 2][(position.y + target.y) / 2].piece.type == 3){
                  if(map[(position.x + target.x) / 2][(position.y + target.y) / 2].piece.team->numEquip == 1){
                    nbDragRed--;
                  }else{
                    nbDragBlue--;
                  }
                }
                //----------------


              }
            }
            printMap(map, config);

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
