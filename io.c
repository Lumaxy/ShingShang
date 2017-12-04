#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

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
    fclose(file);
    printf("Fichier de sauvegarde créé.\n");
    return 1;
  }else{
    while(fscanf(file, "%s = ", property) != EOF){
      char value[255];
      int index = 0;
      do {
        fscanf(file,"%c", &c);
        if(c != '\n'){
          value[index] = c;
          index++;
        }else{
          value[index] = '\0';
        }
      } while(c != '\n');

      if(strcmp(property,"nameTeam1") == 0){
        strcpy(config->nameTeam1,value);
      }else if(strcmp(property,"colorTeam1") == 0){
        config->colorTeam1 = atoi(value);
      }else if(strcmp(property,"nameTeam2") == 0){
        strcpy(config->nameTeam2,value);
      }else if(strcmp(property,"colorTeam2") == 0){
        config->colorTeam2 = atoi(value);
      }else if(strcmp(property, "squareColor") == 0){
        config->squareColor = atoi(value);
      }
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
  }
}

int loadGame(int tab[][2], int size){
  FILE *file;
  char *mode = "r";
  char filename[255] = "save";
  int tmp;
  char c;
  int x = 0, y = 0;

  file = fopen(filename, mode);
  if(file == NULL){
    fprintf(stderr, "Pas de fichier ou pas les droits.\n");
    file = fopen(filename, "w+");
    fclose(file);
    printf("Fichier de sauvegarde créé.\n");
    return 1;
  }else{
    while(fscanf(file, "%d%c", &tmp, &c) != EOF){
      tab[x][y] = tmp;
      if(c == ':'){
        x++;
      }else{
        y++;
        x=0;
      }
    }
    fclose(file);
    return 0;
  }
}

void saveGame(int tab[][2], int size){
  FILE *file;
  char *mode = "w+";
  char filename[255] = "save";
  int x, y;

  file = fopen(filename, mode);
  if(file == NULL){
    fprintf(stderr, "Error.\n");
  }else{
    for(x = 0; x < size; x++){
      for(y = 0; y < size; y++){
        fprintf(file, "%d", tab[x][y]);
        if(y != size - 1){
          fprintf(file, ":");
        }
      }
      fprintf(file, "\n");
    }
  }
}
