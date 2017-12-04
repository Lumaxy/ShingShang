typedef struct Config {
  char nameTeam1[255];
  int colorTeam1;
  char nameTeam2[255];
  int colorTeam2;
  int squareColor;
} Config;

int loadGame(int tab[][2], int size);
void saveGame(int tab[][2], int size);

int loadConfig(Config *config);
void saveConfig(Config);
