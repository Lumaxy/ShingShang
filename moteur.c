#include <stdio.h>
#include "structure.h"
#include "moteur.h"
#include "graphConsole.h"
#define TAILLE 10

//Fonction Moteur

void getCoor(int *x, int *y){
  char xChar, yChar;
  *x = -1;
  *y = -1;
  do{
    printf("Entrez x :\n");
    scanf("%c", &xChar);

    clearBuffer();

    if((int)xChar >= 48 && (int)xChar <= 57){
      *x = (int)xChar - 48;
    }else{
      printf("Format incorrect\n");
    }
  }while(*x < 0 || *x > 9);

  do{
    printf("Entrez y :\n");
    scanf("%c", &yChar);

    clearBuffer();

    if((int)yChar >= 48 && (int)yChar <= 57){
      *y = (int)yChar - 48;
    }else{
      printf("Format incorrect.\n");
    }
    printf("%d\n", *y);
  }while(*y < 0 || *y > 9);
}

int testCoor(int x, int y, Square map[][TAILLE], int player){
  int res = -1;
  Square tmp = map[x][y];
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

int testMove(int x, int y, int x1, int y1, Square map[][TAILLE]){
  int res = 0;
  int tmp = 0; //Permet de ne pas repeter le test du coef directeur

  if(map[x][y].isFill == 1){
    Square caseVisee = map[x1][y1];
    //Movement ?
    //test du type de la map
    if(caseVisee.type == 0){
      //La case est elle occupé?
      if(caseVisee.isFill == 0){
        //Mouvement autoriser selon le pion?
        Piece p1 = map[x][y].piece;
        switch(p1.type){
          //Singe mouvement de deux case dans la meme direction
          case 1:
          printf("distance(p, x1, y1) : %d\n", distance(p1, x1, y1));
          if(distance(p1, x1, y1) == 2*2 && map[(x+x1)/2][(y+y1)/2].isFill == 0){
            tmp = 1;
          }else if(distance(p1, x1, y1) == 1){
            tmp = 1;
          }
          if(tmp == 1){
            // Direction. cas particulier de droite x = k
            if(x1 == x){
              res = 1;
            }else{
              float coef = (y1 - y) / (x1 - x); //coef directeur
              if(abso(coef) == 1 || coef == 0){
                res = 1;
              }
            }
          }
          break;
          //Lion 1 case
          case 2:
          if(distance(p1, x1, y1) == 1){
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
int testJump(int x, int y, int x1, int y1, int oldCoor[2], Square map[][TAILLE]){
  int res = 0;
  //Test Jump
  Square center = map[x][y];
  Piece p = center.piece;
  if(oldCoor[0] == x1 && oldCoor[1] == y){
    printf("Impossible de faire retour\n");
  }else{
    printf("Jump distance(p, x1, y1) : %d\n", distance(p, x1, y1));
    if(distance(p, x1, y1) == 2*2){
      int xMoy = (x + x1) / 2;
      int yMoy = (y + y1) / 2;

      Piece p2 = map[xMoy][yMoy].piece;

      if(p.type >= p2.type){
        //possibilité de sauter
        res = 1;
      }

    }else if(distance(p, x1, y1) == 8){
      int xMoy = (x + x1) / 2;
      int yMoy = (y + y1) / 2;
      printf("%d//%d\n", xMoy, yMoy );
      Piece p2 = map[xMoy][yMoy].piece;

      if(p.type >= p2.type){
        //possibilité de sauter
        res = 1;
      }
    }else{
      printf("La case n'est pas a la bonne distance de saut\n" );
    }
  }
  return res;
}


int numMove(int x, int y, Square map[][TAILLE]){
  int res = 0;
  int i, j;

  for(i = x -1; i <= x + 1; i++){
    for(j = y -1; j <= y + 1; j++){
      //On test si les nouvelles coordonnées ne débordent pas du tableau et differente du centre
      if(i >= 0 && i <= 9 && j >= 0 && j <= 9){
        //coord differente du centre
        if(!(i == x && j == y)){
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

int numJump(int x, int y, int oldCoor[2], Square map[][TAILLE]){
  int res = 0, i, j;

  Square center = map[x][y];

  for(i = x -1; i <= x + 1; i++){
    for(j = y -1; j <= y + 1; j++){
      //On test si les nouvelles coordonnées ne débordent pas du tableau et differente du centre
      if(i >= 0 && i <= 9 && j >= 0 && j <= 9){
        //coord differente du centre et de l'ancienne case
        if(!(i == x && j == y)){
          Square tmp = map[i][j];
          //test du type de la map
          if(tmp.type >= 0){
            //La case est elle occupé?
            if(tmp.isFill == 1){
              Piece tmpP = tmp.piece;
              //Le pion est il plus petit ou de meme taille ?
              if(tmpP.type <= center.piece.type){
                //test des coor opposer, si elle sont bien dsans la grille
                int xA = (2*i)-x;
                int yA = (2*j)-y;
                if(xA >= 0 && xA <= 9 && yA >= 0 && yA <= 9  && !(xA == oldCoor[0] && yA == oldCoor[1])){

                  // si bien possible( ou hors grille)
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
  }
  return res;
}

int distance(Piece p1, int x, int y){
  //Pour eviter la racine carre, je renvoie le res au carre.
  return ((p1.x - x)*(p1.x - x) + (p1.y - y)*(p1.y - y));
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
  Piece p = {1, 4, 3, red};
  map[1][4].piece = p;
  map[1][4].isFill = 1;

  p.x = 2;
  p.y = 4;
  p.type = 3;
  p.team = blue;
  map[2][4].piece = p;
  map[2][4].isFill = 1;

  p.x = 4;
  p.y = 4;
  map[4][4].piece = p;
  map[4][4].isFill = 1;
  p.x = 6;
  p.y = 4;
  p.team = blue;
  map[6][4].piece = p;
  map[6][4].isFill = 1;
  p.x = 8;
  p.y = 4;
  p.team = blue;
  map[6][4].piece = p;
  map[6][4].isFill = 1;
}


void move(Square *s1, Square *s2, int x, int y){
  Piece p = s1->piece;
  // map[x1][y1]
  p.x = x;
  p.y = y;
  s2->piece = p;
  s2->isFill = 1;

  s1->isFill = 0;
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

void clearBuffer(){
  //Vide buffer
  int c;
  do {
    c = getchar();
  } while (c != EOF && c != '\n');
  //------------------
}
