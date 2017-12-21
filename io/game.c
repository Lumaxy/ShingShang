#include "../structure.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/types.h>
#define TAILLE 10

int loadGame(Square tab[][TAILLE], Team *red, Team *blue){
  FILE *map_type;
  FILE *map_isFill;

  FILE *pieces_type;
  FILE *pieces_numEquip;

  char *mode = "r";
  char map_type_name[255] = "save/Map/type";
  char map_isFill_name[255] = "save/Map/isFill";

  char pieces_numEquip_name[255] = "save/Pieces/numEquip";
  char pieces_type_name[255] = "save/Pieces/type";

  map_type = fopen(map_type_name, mode);
  map_isFill = fopen(map_isFill_name, mode);

  pieces_numEquip = fopen(pieces_numEquip_name, mode);
  pieces_type = fopen(pieces_type_name, mode);

  int x = 0, y = 0;

  if(map_type == NULL || map_isFill == NULL || pieces_numEquip == NULL || pieces_type == NULL){
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
    while(fscanf(map_type, "%d%c", &valMapType, &c) != EOF){
      fscanf(map_isFill, "%d%c", &valMapIsFill, &tmp);
      fscanf(pieces_numEquip, "%d%c", &valPieceNumEquip, &tmp);
      fscanf(pieces_type, "%d%c", &valPieceType, &tmp);
      tab[x][y].type = valMapType;
      tab[x][y].isFill = valMapIsFill;
      if(valMapIsFill == 1){
        Piece p = {x, y, valPieceType, blue};
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
    fclose(map_type);
    fclose(map_isFill);
    fclose(pieces_numEquip);
    fclose(pieces_type);
    return 0;
  }
}

void saveGame(Square tab[][TAILLE]){
  FILE *map_type;
  FILE *map_isFill;

  FILE *pieces_type;
  FILE *pieces_numEquip;

  // FILE *data;

  //https://stackoverflow.com/questions/7430248/creating-a-new-directory-in-c
  mkdir("save", 0700);
  mkdir("save/Map", 0700);
  mkdir("save/Pieces", 0700);


  char *mode = "w+";
  char map_type_name[255] = "save/Map/type";
  char map_isFill_name[255] = "save/Map/isFill";

  char pieces_numEquip_name[255] = "save/Pieces/numEquip";
  char pieces_type_name[255] = "save/Pieces/type";
  // char data_name[255] = "save/data";


  int x, y;

  map_type = fopen(map_type_name, mode);
  map_isFill = fopen(map_isFill_name, mode);

  pieces_numEquip = fopen(pieces_numEquip_name, mode);
  pieces_type = fopen(pieces_type_name, mode);

  // data = fopen(data_name, mode);

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
    printf("Saving map_type : OK\n");
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
    printf("Saving map_isFill : OK\n");
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
    printf("Saving pieces_type : OK\n");
  }


  //pieces_numTeam_name
  if(pieces_numEquip == NULL){
    fprintf(stderr, "Error while saving pieces_numEquip\n");
  }else{
    for(y = 0; y < TAILLE; y++){
      for(x = 0; x < TAILLE; x++){
        if(tab[x][y].isFill == 1){
          fprintf(pieces_numEquip, "%d", tab[x][y].piece.team->numEquip);
        }else{
          fprintf(pieces_numEquip, "0");
        }
        if(x != TAILLE - 1){
          fprintf(pieces_numEquip, ":");
        }
      }
      fprintf(pieces_numEquip, "\n");
    }
    fclose(pieces_numEquip);
    printf("Saving pieces_numEquip : OK\n");
  }
}
