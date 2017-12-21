#ifndef GAME_H
#define GAME_H
#define TAILLE 10

int loadGame(Square tab[][TAILLE], Team *red, Team *blue);
void saveGame(Square tab[][TAILLE]);

#endif
