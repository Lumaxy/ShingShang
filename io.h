#ifndef IO_H
#define IO_H
#define TAILLE 10

int loadGame(int tab[][TAILLE], int size);
void saveGame(int tab[][TAILLE], int size);

int loadConfig(Config *config);
void saveConfig(Config config);

#endif
