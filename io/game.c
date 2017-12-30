#include "../structure.h"
#include "../language.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/types.h>
#define TAILLE 10

int loadGame(Square tab[][TAILLE], Team red, Team blue, Data *dataBuff){
  FILE *map_type;
  FILE *map_isFill;

  FILE *pieces_type;
  FILE *pieces_teamNum;

  FILE *data;

  char *mode = "r";
  char *map_type_name = "save/Map/type";
  char *map_isFill_name = "save/Map/isFill";

  char *pieces_teamNum_name = "save/Pieces/teamNum";
  char *pieces_type_name = "save/Pieces/type";
  char *data_name = "save/data";

  map_type = fopen(map_type_name, mode);
  map_isFill = fopen(map_isFill_name, mode);

  pieces_teamNum = fopen(pieces_teamNum_name, mode);
  pieces_type = fopen(pieces_type_name, mode);

  data = fopen(data_name, mode);

  int x = 0, y = 0;

  if(map_type == NULL || map_isFill == NULL || pieces_teamNum == NULL || pieces_type == NULL || data == NULL){
    fprintf(stderr, "Erreur de lecture de sauvegarde. Un fichier est manquant.\n");
    //TODO creer le fichier manquant
    // printf("Fichier de sauvegarde créé.\n");
    return 1;
  }else{
    int valMapType;
    int valMapIsFill;
    int valPieceNumEquip;
    int valPieceType;
    char c, tmp;
    //Chargement Plateau avec pions
    while(fscanf(map_type, "%d%c", &valMapType, &c) != EOF){
      fscanf(map_isFill, "%d%c", &valMapIsFill, &tmp);
      fscanf(pieces_teamNum, "%d%c", &valPieceNumEquip, &tmp);
      fscanf(pieces_type, "%d%c", &valPieceType, &tmp);
      tab[x][y].type = valMapType;
      tab[x][y].isFill = valMapIsFill;
      if(valMapIsFill == 1){
        Coordinate tmp = {x, y};
        Piece p = {tmp, valPieceType, blue};
        if(valPieceNumEquip == 1){
          p.team = red;
        }
        tab[x][y].piece = p;
      }
      if(c == ':'){
        x++;
      }else{
        y++;
        x=0;
      }
    }

    fscanf(data, "%d/", &(dataBuff->player));
    fscanf(data, "%d/", &(dataBuff->nbDragRed));
    fscanf(data, "%d/", &(dataBuff->nbDragBlue));
    fscanf(data, "%d/", &(dataBuff->switchPlayer));
    fscanf(data, "%d/", &(dataBuff->oldBushi.x));
    fscanf(data, "%d/", &(dataBuff->oldBushi.y));

    fclose(map_type);
    fclose(map_isFill);
    fclose(pieces_teamNum);
    fclose(pieces_type);
    fclose(data);
    return 0;
  }
}

void saveGame(Square tab[][TAILLE], Data dataBuff){
  FILE *map_type;
  FILE *map_isFill;

  FILE *pieces_type;
  FILE *pieces_teamNum;

  FILE *data;

  //https://stackoverflow.com/questions/7430248/creating-a-new-directory-in-c
  mkdir("save", 0700);
  mkdir("save/Map", 0700);
  mkdir("save/Pieces", 0700);


  char *mode = "w+";
  char *map_type_name  = "save/Map/type";
  char *map_isFill_name  = "save/Map/isFill";

  char *pieces_teamNum_name  = "save/Pieces/teamNum";
  char *pieces_type_name  = "save/Pieces/type";
  char *data_name = "save/data";

  int x, y;

  map_type = fopen(map_type_name, mode);
  map_isFill = fopen(map_isFill_name, mode);

  pieces_teamNum = fopen(pieces_teamNum_name, mode);
  pieces_type = fopen(pieces_type_name, mode);

  data = fopen(data_name, mode);

  //map_type
  if(map_type == NULL){
    fprintf(stderr, "Error while saving map_type\n");
  }else{
    for(y = 0; y < TAILLE; y++){
      for(x = 0; x < TAILLE; x++){
        fprintf(map_type, "%d", tab[x][y].type);
        if(x != TAILLE - 1){
          fprintf(map_type, ":");
        }
      }
      fprintf(map_type, "\n");
    }
    fclose(map_type);
    printf(SAVE_MAP_TYPE);
  }

  //map_isFill
  if(map_isFill == NULL){
    fprintf(stderr, "Error while saving map_isFill\n");
  }else{
    for(y = 0; y < TAILLE; y++){
      for(x = 0; x < TAILLE; x++){
        fprintf(map_isFill, "%d", tab[x][y].isFill);
        if(x != TAILLE - 1){
          fprintf(map_isFill, ":");
        }
      }
      fprintf(map_isFill, "\n");
    }
    fclose(map_isFill);
    printf(SAVE_MAP_ISFILL);
  }


  //pieces_type
  if(pieces_type == NULL){
    fprintf(stderr, "Error while saving pieces_type\n");
  }else{
    for(y = 0; y < TAILLE; y++){
      for(x = 0; x < TAILLE; x++){
        if(tab[x][y].isFill == 1){
          fprintf(pieces_type, "%d", tab[x][y].piece.type);
        }else{
          fprintf(pieces_type, "0");
        }
        if(x != TAILLE - 1){
          fprintf(pieces_type, ":");
        }
      }
      fprintf(pieces_type, "\n");
    }
    fclose(pieces_type);
    printf(SAVE_PIECE_TYPE);
  }


  //pieces_numTeam_name
  if(pieces_teamNum == NULL){
    fprintf(stderr, "Error while saving pieces_teamNum\n");
  }else{
    for(y = 0; y < TAILLE; y++){
      for(x = 0; x < TAILLE; x++){
        if(tab[x][y].isFill == 1){
          fprintf(pieces_teamNum, "%d", tab[x][y].piece.team.teamNum);
        }else{
          fprintf(pieces_teamNum, "0");
        }
        if(x != TAILLE - 1){
          fprintf(pieces_teamNum, ":");
        }
      }
      fprintf(pieces_teamNum, "\n");
    }
    fclose(pieces_teamNum);
    printf(SAVE_PIECE_NUMEQUIP);
  }

  //data
  if(data == NULL){
    fprintf(stderr, "Error while saving data\n");
  }else{
    fprintf(data, "%d/", dataBuff.player);
    fprintf(data, "%d/", dataBuff.nbDragRed);
    fprintf(data, "%d/", dataBuff.nbDragBlue);
    fprintf(data, "%d/", dataBuff.switchPlayer);
    fprintf(data, "%d/", dataBuff.oldBushi.x);
    fprintf(data, "%d/", dataBuff.oldBushi.y);

    fclose(data);
    printf(SAVE_DATA);
    }

  printf(SAVE);
}
