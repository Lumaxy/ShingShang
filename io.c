#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//DIR
#include <sys/types.h>
// #include <unistd.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "structure.h"
#include "io.h"
#include "graphConsole.h"
#define TAILLE 10

int loadConfig(Config *config){
  FILE *file;
  char *mode = "r";
  char filename[255] = "config";
  char property[255];
  char c;

  file = fopen(filename, mode);
  if(file == NULL){
    fprintf(stderr, "Pas de fichier ou pas les droits.\n");
    file = fopen(filename, "w+");
    fprintf(file, "%s = %s\n", "nameTeam1", "Les tigres");
    fprintf(file, "%s = %d\n", "colorTeam1", 31);
    fprintf(file, "%s = %s\n", "nameTeam2", "Les pieuvres");
    fprintf(file, "%s = %d\n", "colorTeam2", 34);
    fprintf(file, "%s = %d\n", "squareColor", 33);
    fprintf(file, "%s = %d\n", "squareChar", '0');
    fprintf(file, "%s = %d\n", "spaceColor", 47);


    fclose(file);
    printf("Fichier de sauvegarde créé.\n");
    file = fopen(filename, mode);
  }
  while(fscanf(file, "%s = ", property) != EOF){
    char value[255];
    int index = 0;
    int squareChar;

    do {
      fscanf(file,"%c", &c);
      if(strcmp(property, "squareChar") == 0 && index == 0){
        squareChar = ((int)c-48)*10;// - 48 pour la conversion ascii en vrai nombre
      }else if(strcmp(property, "squareChar") == 0&& index == 1){
        squareChar+= ((int)c-48 );
      }

      if(c != '\n'){
        value[index] = c;
        index++;
      }else {
        value[index] = '\0';
      }
    } while(c != '\n');

    if(strcmp(property,"nameTeam1") == 0){
      strcpy(config->nameTeam1,value);
    }else if(strcmp(property,"colorTeam1") == 0){
      config->colorTeam1 = atoi(value);
    }else if(strcmp(property,"nameTeam2") == 0){
      strcpy(config->nameTeam2, value);
    }else if(strcmp(property,"colorTeam2") == 0){
      config->colorTeam2 = atoi(value);
    }else if(strcmp(property, "squareColor") == 0){
      config->squareColor = atoi(value);
    }else if(strcmp(property, "squareChar") == 0 && index == 2){
      config->squareChar = (char)squareChar;
    }else if(strcmp(property, "frameColor") == 0){
      config->frameColor = atoi(value);
    }
  }
  fclose(file);
  return 0;
}

void saveConfig(Config config){
  FILE *file;
  char *mode = "w+";
  char filename[255] = "config";

  file = fopen(filename, mode);

  if(file == NULL){
    printf("Error\n");
  }else{
    fprintf(file, "%s = %s\n", "nameTeam1", config.nameTeam1);
    fprintf(file, "%s = %d\n", "colorTeam1", config.colorTeam1);
    fprintf(file, "%s = %s\n", "nameTeam2", config.nameTeam2);
    fprintf(file, "%s = %d\n", "colorTeam2", config.colorTeam2);
    fprintf(file, "%s = %d\n", "squareColor", config.squareColor);
    fprintf(file, "%s = %d\n", "squareChar", config.squareChar);
  }
}

int loadGame(Square tab[][TAILLE]){
  // FILE *file;
  // char *mode = "r";
  // char filename[255] = "save";
  // int tmp;
  // char c;
  // int x = 0, y = 0;
  //
  // file = fopen(filename, mode);
  // if(file == NULL){
  //   fprintf(stderr, "Pas de fichier ou pas les droits.\n");
  //   file = fopen(filename, "w+");
  //   fclose(file);
  //   printf("Fichier de sauvegarde créé.\n");
  //   return 1;
  // }else{
  //   while(fscanf(file, "%d%c", &tmp, &c) != EOF){
  //     tab[x][y] = tmp;
  //     if(c == ':'){
  //       x++;
  //     }else{
  //       y++;
  //       x=0;
  //     }
  //   }
  //   fclose(file);
  return 0;
  // }
}

void saveGame(Square tab[][TAILLE]){
  FILE *map_type;
  FILE *map_isFill;

  FILE *pieces_type;
  FILE *pieces_numEquip;

  // FILE *data;


  //https://stackoverflow.com/questions/7430248/creating-a-new-directory-in-c


  //   struct stat stSave = {0};
  //
  //   if (stat("/some/directory", &st) == -1) {
  //       mkdir("/some/directory", 0700);
  //   }
  //
  // struct stat st = {0};
  //
  // if (stat("/some/directory", &st) == -1) {
  //     mkdir("/some/directory", 0700);
  // }
  //
  // struct stat st = {0};
  //
  // if (stat("/some/directory", &st) == -1) {
  //     mkdir("/some/directory", 0700);
  // }
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
    couleur(31);
    fprintf(stderr, "Error while saving map_type\n");
    couleur(0);
  }else{
    for(x = 0; x < TAILLE; x++){
      for(y = 0; y < TAILLE; y++){
        fprintf(map_type, "%d", tab[x][y].type);
        if(y != TAILLE - 1){
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
    couleur(31);
    fprintf(stderr, "Error while saving map_isFill\n");
    couleur(0);
  }else{
    for(x = 0; x < TAILLE; x++){
      for(y = 0; y < TAILLE; y++){
        fprintf(map_isFill, "%d", tab[x][y].isFill);
        if(y != TAILLE - 1){
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
    couleur(31);
    fprintf(stderr, "Error while saving pieces_type\n");
    couleur(0);
  }else{
    for(x = 0; x < TAILLE; x++){
      for(y = 0; y < TAILLE; y++){
        if(tab[x][y].isFill == 1){
          fprintf(pieces_type, "%d", tab[x][y].piece.type);
        }else{
          fprintf(pieces_type, "0");
        }
        if(y != TAILLE - 1){
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
    couleur(31);
    fprintf(stderr, "Error while saving pieces_numEquip\n");
    couleur(0);
  }else{
    for(x = 0; x < TAILLE; x++){
      for(y = 0; y < TAILLE; y++){
        if(tab[x][y].isFill == 1){
          fprintf(pieces_numEquip, "%d", tab[x][y].piece.team->numEquip);
        }else{
          fprintf(pieces_numEquip, "0");

        }
        if(y != TAILLE - 1){
          fprintf(pieces_numEquip, ":");
        }
      }
      fprintf(pieces_numEquip, "\n");
    }
    fclose(pieces_numEquip);
    printf("Saving pieces_numEquip : OK\n");
  }


}
