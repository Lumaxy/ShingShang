#include <stdio.h>
#include "language.h"
#include "structure.h"
#include "graphConsole.h"
#include "moteur/moteur.h"

int menu(){
  printf("  Shing - Shang\n");
  printf("-------Menu-------\n");
  printf(MENU_1);
  printf(MENU_2);
  printf(MENU_3);
  printf(MENU_4);
  printf(MENU_5);
  return choix(5);
}
