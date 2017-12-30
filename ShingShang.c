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
#include "language.h"
#include "graphConsole.h"

#include "sockets.h"

#include "moteur/board.h"
#include "moteur/move.h"
#include "moteur/jump.h"
#include "moteur/coor.h"
#include "moteur/moteur.h"


#include "io/config.h"
#include "io/game.h"

#include "menu.h"

//Random
#include <time.h>
#include <stdlib.h>

//socket
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1


#define TAILLE 10 //definie la taille du plateau

int main(int argc, char const *argv[]) {
  //TODO traduction en plusieurs language avec les DEFINE
  //TODO System de message indicatif
  //TODO gerer les erreur afficher au joueur

  //Initialisation des variables ---------------------------------
  Config config;
  loadConfig(&config);
  srand(time(NULL));
  int isPlaying = 1; //tant que personne ne gagne, isPlaying = 1

  //Message indicatif pour le joueur
  char msg[50];
  msg[0] = '\0';
  int msgColor = 31;

  int player = (rand()% 2) + 1; // Premier joueur a jouer
  int nbDragRed = 2;
  int nbDragBlue = 2;
  int switchPlayer = 1; // permet de savoir si il y a changement de joueur (== 0 si la personne a manger un bushi adverse et souhaite rejouer)
  Coordinate oldBushi;
  Data tmp; //Pour la sauvegarde

  int network = 0; // 0 -> pas de jeu en reseau

  //socket
  SOCKET sock;
  SOCKADDR_IN sin;

  SOCKET csock;
  SOCKADDR_IN csin;

  Square buffer[TAILLE * TAILLE];

  //-----------------------------------------------------------------

  //Liste des équipes -------------------
  Team red;
  red.teamNum = 1;
  red.color = config.colorTeam1;
  strcpy(red.name, config.nameTeam1);
  Team blue;
  blue.teamNum = 2;
  blue.color = config.colorTeam2;
  strcpy(blue.name, config.nameTeam2);
  //--------------------------------------

  Square map[TAILLE][TAILLE]; // Plateau de jeu
  switch(menu()){
    case 1: // Nouvelle partie
    initMap(map);
    initPiece(map, red, blue);
    break;

    case 2: //Reprise de partie
    if(loadGame(map, red, blue, &tmp) == 0){
      player = tmp.player;
      nbDragRed = tmp.nbDragRed;
      nbDragBlue = tmp.nbDragBlue;
      switchPlayer = tmp.switchPlayer;
      oldBushi.x = (tmp.oldBushi).x;
      oldBushi.y = (tmp.oldBushi).y;
    }else{
      initMap(map);
      initPiece(map, red, blue);
    }
    break;

    case 3: //Jeux en reseau heberge
    host(&sock, &csock, &sin, &csin);
    printf(SOCK_START1);
    couleur(config.colorTeam1);
    printf("%s\n", config.nameTeam1);
    couleur(0);
    sleep(4);
    initMap(map);
    initPiece(map, red, blue);
    network = 1; // 1 -> Host
    break;

    case 4: //Jeux en reseau rejoindre
    join(&sock, &sin);
    printf(SOCK_CONNECTED);
    couleur(config.colorTeam2);
    printf("%s\n", config.nameTeam2);
    couleur(0);
    sleep(4);
    initMap(map);
    initPiece(map, red, blue);
    network = 2; // 2 -> Join
    break;

    case 5: //Configuration
    configuration(&config);
    red.color = config.colorTeam1;
    blue.color = config.colorTeam2;
    strcpy(red.name, config.nameTeam1);
    strcpy(blue.name, config.nameTeam2);
    initMap(map);
    initPiece(map, red, blue);
    break;
  }

  //Echange du joueur qui commencce
  if(network == 1){
    char tmp = player;
    send(csock, &tmp, sizeof(char), 0);
  }else if(network == 2){
    char tmp;
    recv(sock, &tmp, sizeof(char), 0);
    player = (int)tmp;
  }

  if(network != 0){
    //On vide le buffer rempli par les sockets
    clearBuffer();
  }

  //Chaque boucle correspond a un tour.
  while(isPlaying && nbDragRed > 0 && nbDragBlue > 0){
    /*---- VARIABLES RELATIVES A CHAQUE TOUR ---- */
    Coordinate position; //Coordinate actuelle
    Coordinate target; //Coordinate visees
    Coordinate old = {0,0}; //Coordinate de la derniere case
    int sautTotal = 0; //Nombre de saut effectuer dans un tour
    /* ---- ------------------------------ ---- */

    //sauvegarde automatique si on ne joue pas en reseau
    if(network == 0){
      Data tmp = {player, nbDragRed, nbDragBlue, switchPlayer, oldBushi};
      saveGame(map, tmp);
    }

    printMap(map, config);

    //Si c'est notre tour
    if((network == 1 && player == 1) || (network == 2 && player == 2) || network == 0){
      //On affiche le joueur actif
      if(network == 0){
        printf(PLAYER, player);
      }else{
        printf(TURN);
        if(player == 1){
          couleur(config.colorTeam1);
          printf("%s", config.nameTeam1);
        }else{
          couleur(config.colorTeam2);
          printf("%s", config.nameTeam2);
        }
        couleur(0);
        printf(")\n");
      }

      //On affiche le msg
      couleur(msgColor);
      printf("%s\n", msg);
      couleur(0);

      //Obtention Coordonnée du pion à bouger
      if(switchPlayer == 0){
        do {
          getCoor(&position);
        } while(position.x == oldBushi.x && position.y == oldBushi.y);
      }else{
        getCoor(&position);
      }

      //Si le test est 1 c'est un de ses pion, il peux donc le bouger
      if(testCoor(position, map, player) == 1){
        //Test du nombre de coup possible (saut + move)
        if(numJump(position, old, map)+numMove(position, map) >= 1){
          couleur(32);
          printf(COOR_WHERE);
          couleur(0);

          //------- Premier mouvement (Jump/Move) --------------------
          int resMove = 0, resJump = 0;
          msg[0] = '\0';
          do{
            getCoor(&target);
            //On test si la case pointer est bien libre et s'il peux y acceder
            resMove = testMove(position, target, map);
            //Permet d'eviter que le pion apres avoir bouger puisse sauter
            if(resMove == 0){
              resJump = testJump(position, target, old, map);
              if(resJump == -1){
                printf(ERR_JUMP_DISTANCE);
              }else if(resJump == -2){
                printf(ERR_JUMP_BACK);
              }
            }
          }while(resMove != 1 && resJump != 1);
          if (resJump == 1) {
            sautTotal++;
          }
          move(map, target, &position, &old);
          switchPlayer = 1;
          printMap(map, config);
          //----------------------------------------------------------

          //--------- Suite de saut ---------------------------------------
          int again = 0;
          while(numJump(position, old, map) >= 1 && again == 0 && resMove == 0){
            again = 0;
            printf(JUMP_AGAIN, numJump(position, old, map));

            //Obtention de la reponse du joueur--
            char rep;
            do{
              scanf("%c", &rep);
            }while(rep != 'O' && rep != 'N' && rep != 'o' && rep != 'n');
            clearBuffer();
            //-----------------------------------

            if(rep == 'O' || rep == 'o'){
              msg[0] = '\0';
              do{
                //Recup des nouvelle Coordinate
                getCoor(&target);
                resJump = testJump(position, target, old, map);
              }while(resJump != 1 || (target.x == old.x && target.y == old.y));

              sautTotal++;
              if (sautTotal >= 2) {
                //Alors on supprime le pion de la case au milieu Si le pion est de l'equipe adverse
                Square tmp = map[(position.x + target.x) / 2][(position.y + target.y) / 2];
                if(tmp.piece.team.teamNum != player){

                  //saut d'un dragon?------------------------
                  if(tmp.piece.type == 3){
                    if(tmp.piece.team.teamNum == 1){
                      nbDragRed--;
                    }else{
                      nbDragBlue--;
                    }
                  }
                  //-------------------------------------------

                  //actualisation de la case à VIDE
                  map[(position.x + target.x) / 2][(position.y + target.y) / 2].isFill = 0;
                  move(map, target, &position, &old);
                  printMap(map, config);

                  if(nbDragRed > 0 && nbDragBlue > 0){
                    //Obligation de changer de bushi ou d'arreter de jouer
                    printf(CHANGE_BUSHI);

                    //Obtention de la reponse du joueur--
                    char rep;
                    do{
                      scanf("%c", &rep);
                    }while(rep != 'O' && rep != 'N' && rep != 'o' && rep != 'n');
                    clearBuffer();
                    //-----------------------------------

                    if(rep == 'o' || rep == 'O'){
                      printf(CHOOSE_BUSHI);
                      switchPlayer = 0;
                      oldBushi = position;
                      again = 1;
                    }else{
                      switchPlayer = 1;
                      printMap(map, config);
                      again = 1;
                    }
                  }
                }else{
                  move(map, target, &position, &old);
                  printMap(map, config);
                }
              }
            }else{
              again = 1;
            }
          }
          //--------------------------------------------------------------

          testWin(&isPlaying, map);

          //Changement de joueur
          if(switchPlayer == 1){
            if(player == 1){
              player++;
            }else{
              player--;
            }
            if(network == 1){
              codeMap(map, buffer);
              send(csock, buffer, sizeof(Square) * TAILLE * TAILLE, 0);
            }else if(network == 2){
              codeMap(map, buffer);
              send(sock, buffer, sizeof(Square) * TAILLE * TAILLE, 0);
            }
          }
          //--------------------
        }

      }else{
        msg[0] = '\0';
        msgColor = 31;
        strcpy(msg, WRONG_PIECE);
      }
    }else{
      printf(WAIT_TURN);
      if(network == 1){
        recv(csock, buffer, sizeof(Square) * TAILLE * TAILLE, 0);
        decodeMap(map, buffer);
        printMap(map, config);
      }else{
        recv(sock, buffer, sizeof(Square) * TAILLE * TAILLE, 0);
        decodeMap(map, buffer);
        printMap(map, config);
      }
      if(player == 1){
        player++;
      }else{
        player--;
      }
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

    printf(VICTORY, victoryName);
    // printf("%s\n", victoryName);
    couleur(0);

    if(network == 1){
      shutdown(csock, 2);
    }
    if(network != 0){
      printf(SOCK_CLOSE);
      close(sock);
      printf(SOCK_CLOSE_OK);
    }
  }

  return 0;
}
