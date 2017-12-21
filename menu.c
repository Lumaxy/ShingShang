#include <stdio.h>
#include "structure.h"
#include "graphConsole.h"
#include "moteur/moteur.h"

int menu(){
  printf("  Shing - Shang\n");
  printf("-------Menu-------\n");
  printf("1 - Nouvelle partie\n");
  printf("2 - Reprendre la partie\n");
  printf("3 - Jeux graphique\n");
  printf("4 - Configuration\n");
  char xChar;
  int nbAfter = 0;
  int x = -1;
  do{
    printf("Entrez votre choix :\n");
    scanf("%c", &xChar);

    nbAfter = clearBuffer();

    if((int)xChar >= 48 && (int)xChar <= 57 && nbAfter == 0){
      x = (int)xChar - 48;
    }else{
      couleur(31);
      printf("Format incorrect.\n");
      couleur(0);
    }
  }while(x < 1 || x > 3);

  return x;
}
