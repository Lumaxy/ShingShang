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

#include "moteur/plateau.h"
#include "moteur/move.h"
#include "moteur/jump.h"
#include "moteur/coor.h"
#include "moteur/moteur.h"

#include "graphConsole.h"

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


/*
###################DEBUG####################
printf("Jump distance(p, x1, y1) : %d\n", distance(p, x1, y1));
printf("oC.x : %d oC.y : %d x : %d y : %d x1 : %d y1 : %d resJump : %d \n", oldCoor[0], oldCoor[1], x, y, x1, y1, resJump);
############################################
*/

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

int main(int argc, char const *argv[]) {
  //TODO traduction en plusieurs language avec les DEFINE
  //TODO jeux en reseau TCP socket
  //TODO creer le fichier manquant loadGame(IO)
  //TODO faire de ne pas terminer sur un portail a la fin d'un tour
  //TODO System de message indicatif
  //TODO Verif les define au debut des include .h
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
  Coordonnees oldBushi;
  Data tmp; //Pour la sauvegarde

  int reseau = 0; // 0 -> pas de jeu en reseau

  //socket
  SOCKET sock;
  SOCKADDR_IN sin;

  SOCKET csock;
  SOCKADDR_IN csin;
  socklen_t recsize = sizeof(csin);

  int sock_err;
  int port;
  char ip[20];
  Square buffer[TAILLE * TAILLE];

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
    case 1: // Nouvelle partie
    initMap(map);
    initPiece(map, red, blue);
    break;

    case 2: //Reprise de partie
    loadGame(map, red, blue, &tmp);
    player = tmp.player;
    nbDragRed = tmp.nbDragRed;
    nbDragBlue = tmp.nbDragBlue;
    switchPlayer = tmp.switchPlayer;
    oldBushi.x = (tmp.oldBushi).x;
    oldBushi.y = (tmp.oldBushi).y;
    break;

    case 3: //Jeux en reseau heberge
    //TODO enlever
    printf("En cours de developpement\n");
    //Afficher son adresse IP
    printf("Entrez le port : ");
    scanf("%d", &port);
    /* ---- Creation socket ---- */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock != INVALID_SOCKET){
      printf("Socket %d opérationelle\n", sock);
    }

    /* ---- Configuration socket ---- */
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

    sock_err = bind(sock, (SOCKADDR*)&sin, sizeof(sin));
    if(sock_err != SOCKET_ERROR){
      sock_err = listen(sock, 1); //Une seule connexion autorisee
      if(sock_err != SOCKET_ERROR){
        printf("Attente d'un joueur adverse sur le port %d\n", port);
        csock = accept(sock, (SOCKADDR *) &csin, &recsize);
        printf("Adversaire connecté ! Lancement d'une nouvelle partie. Vous êtes l'équipe ");
        couleur(config.colorTeam1);
        printf("%s\n", config.nameTeam1);
        couleur(0);
        sleep(4);
        initMap(map);
        initPiece(map, red, blue);
        reseau = 1; // 1 -> Host
      }else{
        couleur(31);
        printf("Erreur reseau\n");
        couleur(0);
      }
    }else{
      couleur(31);
      printf("Erreur reseau\n");
      couleur(0);
    }
    break;

    case 4: //Jeux en reseau rejoindre
    //TODO enlever
    printf("En cours de developpement\n");
    printf("Entrez l'adresse IP : ");
    scanf("%s", ip);
    printf("Entrez le port : ");
    scanf("%d", &port);

    /* ---- Creation socket ---- */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock != INVALID_SOCKET){
      printf("Socket %d opérationelle\n", sock);
    }

    /* ---- Configuration socket ---- */
    sin.sin_addr.s_addr = inet_addr(ip);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

    printf("Connection sur le port %d\n", port);
    do {
      sock_err = connect(sock, (SOCKADDR *)&sin, sizeof(sin));
    } while(sock_err == SOCKET_ERROR);
    printf("Connection reussi ! Lancement d'une nouvelle partie. Vous êtes l'équipe ");
    couleur(config.colorTeam2);
    printf("%s\n", config.nameTeam2);
    couleur(0);
    sleep(4);
    initMap(map);
    initPiece(map, red, blue);
    reseau = 2; // 2 -> Join
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

  /*
  recv(sock, (char*)&tmp, sizeof(char), 0);
  send(csock, buffer, 32, 0);
  */
  //Echange du joueur qui commencce
  if(reseau == 1){
    char tmp = player;
    send(csock, &tmp, sizeof(char), 0);
  }else if(reseau == 2){
    char tmp;
    recv(sock, &tmp, sizeof(char), 0);
    player = (int)tmp;
  }

  if(reseau != 0){
    //On vide le buffer rempli par les sockets
    clearBuffer();
  }

  //Chaque boucle correspond a un tour.
  while(isPlaying && nbDragRed > 0 && nbDragBlue > 0){
    Coordonnees position; //Coordonnees actuelle
    Coordonnees target; //Coordonnees visees
    Coordonnees old = {0,0}; //Coordonnees de la derniere case
    int sautTotal = 0; //Nombre de saut effectuer dans un tour


    //sauvegarde automatique si on ne joue pas en reseau
    if(reseau == 0){
      Data tmp = {player, nbDragRed, nbDragBlue, switchPlayer, oldBushi};
      saveGame(map, tmp);
    }

    printMap(map, config);

    if((reseau == 1 && player == 1) || (reseau == 2 && player == 2) || reseau == 0){
      if(reseau == 0){
        //On affiche le joueur actif
        printf(PLAYER, player);
      }else{
        if(player == 1){
          printf("C'est votre tour ! (");
          couleur(config.colorTeam1);
          printf("%s", config.nameTeam1);
          couleur(0);
          printf(")\n");
        }else{
          printf("C'est votre tour ! (");
          couleur(config.colorTeam2);
          printf("%s", config.nameTeam2);
          couleur(0);
          printf(")\n");
        }
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
          printf("Vers quel point souhaitez vous le bouger ?\n");
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
            printf("Souhaitez vous encore sauter ? O/N (%d pos)\n", numJump(position, old, map));

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
                //Recup des nouvelle Coordonnees
                getCoor(&target);
                printf("test %d;%d//%d;%d\n", position.x, position.y, target.x, target.y);

                resJump = testJump(position, target, old, map);
              }while(resJump != 1 || (target.x == old.x && target.y == old.y));

              sautTotal++;
              if (sautTotal >= 2) {
                //Alors on supprime le pion de la case au milieu Si le pion est de l'equipe adverse
                Square tmp = map[(position.x + target.x) / 2][(position.y + target.y) / 2];
                if(tmp.piece.team.numEquip != player){

                  //saut d'un dragon?------------------------
                  if(tmp.piece.type == 3){
                    if(tmp.piece.team.numEquip == 1){
                      nbDragRed--;
                    }else{
                      nbDragBlue--;
                    }
                  }
                  //-------------------------------------------

                  //actualisation de la case à VIDE
                  map[(position.x + target.x) / 2][(position.y + target.y) / 2].isFill = 0;
                  move(map, target, &position, &old);

                  //Obligation de changer de bushi ou d'arreter de jouer
                  printMap(map, config);
                  printf("Changer de Bushi et continuer à jouer ? O/N\n");

                  //Obtention de la reponse du joueur--
                  char rep;
                  do{
                    scanf("%c", &rep);
                  }while(rep != 'O' && rep != 'N' && rep != 'o' && rep != 'n');
                  clearBuffer();
                  //-----------------------------------

                  if(rep == 'o' || rep == 'O'){
                    printf("Entrez le bushi à jouer\n");
                    switchPlayer = 0;
                    oldBushi = position;
                  }else{
                    switchPlayer = 1;
                  }

                }else{
                  move(map, target, &position, &old);
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
          if(switchPlayer == 1){
            if(player == 1){
              player++;
            }else{
              player--;
            }
            if(reseau == 1){
              codeMap(map, buffer);
              send(csock, buffer, sizeof(Square) * TAILLE * TAILLE, 0);
            }else if(reseau == 2){
              codeMap(map, buffer);
              send(sock, buffer, sizeof(Square) * TAILLE * TAILLE, 0);
            }
          }
          //--------------------
        }

      }else{
        msg[0] = '\0';
        msgColor = 31;
        strcpy(msg,"Mauvais pion");
      }
    }else{
      printf("Patientez, c'est le tour de l'adversaire\n");
      if(reseau == 1){
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

    printf("Victoire de l'équipe ");
    printf("%s\n", victoryName);
    couleur(0);

    if(reseau == 1){
      shutdown(csock, 2);
    }
    if(reseau != 0){
      printf("Fermeture de la socket...\n");
      close(sock);
      printf("Fermeture du serveur terminee\n");
    }

  }

  return 0;
}
