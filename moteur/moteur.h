#ifndef MOTEUR_H
#define MOTEUR_H
#define TAILLE 10

void testWin(int *isplaying, Square map[][TAILLE]);
int clearBuffer();
int choix(int i);
int answer(const char question[255]);

void decodeMap(Square map[TAILLE][TAILLE], Square buffer[TAILLE*TAILLE]);
void codeMap(Square map[TAILLE][TAILLE], Square buffer[TAILLE*TAILLE]);


#endif
