#ifndef GAME_H
#define GAME_H
#define TAILLE 10

int loadGame(Square tab[][TAILLE], Team *red, Team *blue, Data *dataBuff);
void saveGame(Square tab[][TAILLE], Data dataBuff);

#endif
