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
  return choix(4);
}
