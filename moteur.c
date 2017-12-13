#include <stdio.h>
#include "structure.h"
#include "moteur.h"
#include "graphConsole.h"
#define TAILLE 10

//Fonction Moteur

void getCoor(Coordonnees *coor){
  char xChar, yChar;
  int nbCarAfter = 0;
  coor->x = -1;
  coor->y = -1;
  do{
    printf("Entrez x :\n");
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
      if(p.team->numEquip == player){
        res = 1;
      }else{
        res = 2;
      }
    }
  }
  return res;
}

//Check si le deplacement es tautorise : 1 si oui, 0 sinon.
int testMove(Coordonnees position, Coordonnees target, Square map[][TAILLE]){
  int res = 0;
  int tmp = 0; //Permet de ne pas repeter le test du coef directeur

  if(map[position.x][position.y].isFill == 1){
    Square caseVisee = map[target.x][target.y];
    //test du type de la map
    if(caseVisee.type == 0){
      //La case est elle occupé?
      if(caseVisee.isFill == 0){
        //Mouvement autoriser selon le pion?
        Piece p1 = map[position.x][position.y].piece;
        switch(p1.type){
          //Singe mouvement de deux case dans la meme direction
          case 1:
          printf("distance : %d\n", distance(position, target));
          if(distance(position, target) == 2*2 && map[(position.x + target.x) / 2][(position.y + target.y) / 2].isFill == 0){
            tmp = 1;
          }else if(distance(position, target) == 1){
            tmp = 1;
          }
          if(tmp == 1){
            // Direction. cas particulier de droite x = k
            if(target.x == position.x){
              res = 1;
            }else{
              float coef = (target.y - position.y) / (target.x - position.x); //coef directeur
              if(abso(coef) == 1 || coef == 0){
                res = 1;
              }
            }
          }
          break;
          //Lion 1 case
          case 2:
          if(distance(position, target) == 1){
            res = 1;
          }
          break;
          //dragon = 0 car aucun deplacement
        }
      }
    }
  }
  return res;
}


//TODO: quand je choisis de nouveau la case il me change les coordonnées
// et du coup ma case devient isFill == 0
int testJump(Coordonnees position, Coordonnees target, Coordonnees old, Square map[][TAILLE]){
  int res = 0;
  // center = map[x][y];
  Piece p = map[position.x][position.y].piece;
  //verif de la case visee
  if(target.x >= 0 && target.y >= 0 && target.x <= 9 && target.y <= 9){
    if(map[target.x][target.y].type >= 0){

      if(old.x == target.x && old.y == target.y){
        printf("Impossible de faire retour\n");
      }else{
        if(distance(position, target) == 2*2 || distance(position, target) == 8){
          int xMoy = (position.x + target.x) / 2;
          int yMoy = (position.y + target.y) / 2;
          Piece p2 = map[xMoy][yMoy].piece;

          if(p.type >= p2.type){
            //possibilité de sauter
            res = 1;
          }

        }else{
          printf("La case n'est pas à la bonne distance de saut\n" );
        }
      }
    }
  }
  return res;
}


int numMove(Coordonnees position, Square map[][TAILLE]){
  int res = 0;
  int i, j;

  for(i = position.x - 1; i <= position.x + 1; i++){
    for(j = position.y -1; j <= position.y + 1; j++){
      //On test si les nouvelles coordonnées ne débordent pas du tableau et differente du centre
      if(i >= 0 && i <= 9 && j >= 0 && j <= 9){
        //coord differente du centre
        if(!(i == position.x && j == position.y)){
          Square tmp = map[i][j];
          //test du type de la map
          if(tmp.type >= 0){
            //La case est elle occupé?
            if(tmp.isFill == 0){
              res++;
            }
          }
        }
      }
    }
  }
  return res;
}

int numJump(Coordonnees position, Coordonnees old, Square map[][TAILLE]){
  int res = 0, i, j;
  Square center = map[position.x][position.y];

  for(i = position.x -1; i <= position.x + 1; i++){
    for(j = position.y -1; j <= position.y + 1; j++){
      //On test si les nouvelles coordonnées ne débordent pas du tableau et differente du centre
      if(i >= 0 && i <= 9 && j >= 0 && j <= 9){
        //coord differente du centre
        if(!(i == position.x && j == position.y)){
          Square tmp = map[i][j];
          //test du type de la case/ La case est elle occupé?
          if(tmp.type >= 0 && tmp.isFill == 1){
            Piece tmpP = tmp.piece;
            //Le pion est il plus petit ou de meme taille ?
            if(tmpP.type <= center.piece.type){
              //test des coor opposer, si elle sont bien dsans la grille
              int xA = (2*i)-position.x;
              int yA = (2*j)-position.y;
              if(xA >= 0 && xA <= 9 && yA >= 0 && yA <= 9  && !(xA == old.x && yA == old.y)){
                // si possible
                if(map[xA][yA].type >= 0){
                  // si vide
                  if(map[xA][yA].isFill == 0){
                    res++;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return res;
}

int distance(Coordonnees position,Coordonnees target){
  //Pour eviter la racine carre, je renvoie le res au carre.
  return ((position.x - target.x)*(position.x - target.x) + (position.y - target.y)*(position.y - target.y));
}

float abso(float x){
  if(x < 0){
    x *= -1;
  }
  return x;
}

//init
void initMap(Square map[][TAILLE]){
  int x, y;

  //Création de toutes les cases
  for(x = 0; x < TAILLE; x++){
    for(y = 0; y < TAILLE; y++){
      Square tmp;
      tmp.isFill = 0;
      tmp.type = 0;
      map[x][y] = tmp;
    }
  }

  //Bordure hors plateau
  for(x = 0; x < TAILLE; x+=9){
    for(y = 0; y < TAILLE; y++){
      map[x][y].type = -1;
    }
  }

  //bordure Normal
  map[0][4].type = 0;
  map[0][5].type = 0;
  map[9][4].type = 0;
  map[9][5].type = 0;

  //porte
  int team = 1;
  for(y = 1; y < 9; y+=7){
    team++;
    for(x = 4; x <= 5; x++){
      map[x][y].type = team;
    }
  }
}

void initPiece(Square map[][TAILLE], Team *red, Team *blue){
  int x,y;

  //Haut Gauche
  for(y = 0; y < 3; y++){
    for(x = 1; x < 4 - y; x++){
      Piece p = {x, y, 4 - (x + y), red};
      map[x][y].piece = p;
      map[x][y].isFill = 1;
    }
  }

  //Haut Droite
  for(y = 0; y < 3; y++){
    for(x = 8; x > 5 + y ; x--){
      Piece p = {x, y, x - (5+y), red};
      map[x][y].piece = p;
      map[x][y].isFill = 1;
    }
  }

  // bas Gauche
  for(y = 7; y < 10; y++){
    for(x = 1; x < y - 5; x++){
      Piece p = {x, y, (y-x)-5, blue};
      map[x][y].piece = p;
      map[x][y].isFill = 1;
    }
  }

  // bas Droite
  for(y = 7; y < 10; y++){
    for(x = 8; x > 14 - y; x--){
      Piece p = {x, y, (x+y) - 14, blue};
      map[x][y].piece = p;
      map[x][y].isFill = 1;
    }
  }
}


void move(Square map[][TAILLE], Coordonnees target, Coordonnees *position, Coordonnees *old){
  Piece p = map[position->x][position->y].piece; //Le pion a la position
  p.x = target.x; //Nouvelle position
  p.y = target.y;

  map[target.x][target.y].piece = p;
  map[target.x][target.y].isFill = 1;
  map[position->x][position->y].isFill = 0;

  //Update des coord
  old->x = position->x;
  old->y = position->y;
  position->x = target.x;
  position->y = target.y;
}

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
