#ifndef IO_H
#define IO_H
#define TAILLE 10

int loadGame(Square tab[][TAILLE], Team *red, Team *blue);
void saveGame(Square tab[][TAILLE]);

int loadConfig(Config *config);
void saveConfig(Config config);

#endif
