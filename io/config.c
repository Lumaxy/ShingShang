#include "../structure.h"
#include "config.h"
#include "../graphConsole.h"
#include "../moteur/moteur.h"
#include "../language.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/types.h>

int loadConfig(Config *config){
  FILE *file;
  char *mode = "r";
  char filename[255] = "config";
  char property[255];
  char c;

  file = fopen(filename, mode);
  if(file == NULL){
    fprintf(stderr, ERR_NO_FILE);
    file = fopen(filename, "w+");
    fprintf(file, "%s = %s\n", "nameTeam1", "Les tigres");
    fprintf(file, "%s = %d\n", "colorTeam1", 31);
    fprintf(file, "%s = %s\n", "nameTeam2", "Les pieuvres");
    fprintf(file, "%s = %d\n", "colorTeam2", 34);
    fprintf(file, "%s = %d\n", "squareColor", 33);
    fprintf(file, "%s = %d\n", "squareChar", '.');
    fprintf(file, "%s = %d\n", "spaceColor", 47);

    fclose(file);
    printf(INFO_NEW_SAVE);
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
    printf(ERR);
  }else{
    fprintf(file, "%s = %s\n", "nameTeam1", config.nameTeam1);
    fprintf(file, "%s = %d\n", "colorTeam1", config.colorTeam1);
    fprintf(file, "%s = %s\n", "nameTeam2", config.nameTeam2);
    fprintf(file, "%s = %d\n", "colorTeam2", config.colorTeam2);
    fprintf(file, "%s = %d\n", "squareColor", config.squareColor);
    fprintf(file, "%s = %d\n", "squareChar", config.squareChar);
    fprintf(file, "%s = %d\n", "frameColor", config.frameColor);

    printf(SAVE_CONFIG);
    fclose(file);
  }
}

void inputString(char buff[255]){
  int c;
  int size;
  scanf("%s", buff);
  size = strlen(buff);
  do {
    c = getchar();
    if(c != EOF && c != '\n'){
      buff[size] = c;
      size++;
    }
  } while (c != EOF && c != '\n');
}

void configuration(Config *config){
  int exitConfig = 0;
  do{
    char buffer[255];
    clear();
    printf(CONF_TITLE);
    printf(CONF_1);
    printf(CONF_2);
    printf(CONF_3);
    printf(CONF_4);
    switch(choix(4)){
      clear();
      case 1:
      printf(CONF_11);
      printf(CONF_12);
      printf(CONF_13);
      switch (choix(2)) {
        case 1:
        printf(CONF_121);
        inputString(buffer);
        strcpy(config->nameTeam1, buffer);
        break;
        case 2:
        printf(CONF_131);
        scanf("%d", &(config->colorTeam1));
        break;
      }
      break;
      case 2:
      printf(CONF_21);
      printf(CONF_22);
      printf(CONF_23);
      switch (choix(2)) {
        case 1:
        printf(CONF_121);
        inputString(buffer);
        strcpy(config->nameTeam1, buffer);
        break;
        case 2:
        printf(CONF_131);
        scanf("%d", &(config->colorTeam1));
        break;
      }
      break;
      case 3:
      clear();
      printf("--- Configuration du plateau ---\n");
      printf("1) Couleur des cases vides\n");
      printf("2) Caractère des cases vides\n");
      printf("3) Couleur du cadre autour\n");
      switch (choix(3)) {
        case 1:
        printf("Entrez le code couleur des cases vides\n");
        scanf("%d", &(config->squareColor));
        break;
        case 2:
        printf("Entrez le caractère des cases vides\n");
        scanf("%c", &(config->squareChar));
        break;
        case 3:
        printf("Entrez le code couleur du cadre autour\n");
        scanf("%d", &(config->frameColor));
        break;
      }
      break;
      case 4:
      exitConfig = 1;
      break;
    }
    saveConfig(*config);
    clearBuffer();
    clear();
  }while(exitConfig == 0);
}
