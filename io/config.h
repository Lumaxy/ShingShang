#ifndef CONFIG_H
#define CONFIG_H
#define TAILLE 10

int loadConfig(Config *config);
void saveConfig(Config config);
void configuration(Config *config);
void inputString(char buff[255]);

#endif
