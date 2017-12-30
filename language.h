#ifndef LANG_H
#define LANG_H

#ifdef FR
/* ############### FRANCAIS ############### */
#define PLAYER "Joueur %d\n"
#define CHOICE "Choisissez une option :\n"

/* ---- MENU ---- */
#define MENU_1 "1 - Nouvelle partie\n"
#define MENU_2 "2 - Reprendre la partie\n"
#define MENU_3 "3 - Jeux en réseau : héberger\n"
#define MENU_4 "4 - Jouer en réseau : rejoindre\n"
#define MENU_5 "5 - Paramètres\n"
/* ---- ---- ---- */

/* ---- Erreur ---- */
#define ERR "Erreur\n"
#define ERR_NO_FILE "Pas de fichier.\n"
#define ERR_LOAD_FILE "Erreur de lecture de sauvegarde. Un fichier est manquant.\n"
/* ---- ------ ---- */

/* ---- SOCKETS ---- */
#define SOCK_PORT "Entrez le port : "
#define SOCK_IP "Entrez l'adresse IP : "
#define SOCK_WORKING "Socket %d opérationelle\n"
#define SOCK_WAITING "Attente d'un joueur adverse sur le port %d\n"
#define SOCK_CONNECT "Connection sur le port %d\n"
#define SOCK_CONNECTED "Connection reussi ! Lancement d'une nouvelle partie. Vous êtes l'équipe "
#define SOCK_START1 "Adversaire connecté ! Lancement d'une nouvelle partie. Vous êtes l'équipe "

#define SOCK_CLOSE "Fermeture de la socket...\n"
#define SOCK_CLOSE_OK "Fermeture du serveur terminee\n"

#define TURN "C'est votre tour ! ("
#define WAIT_TURN "Patientez, c'est le tour de l'adversaire\n"

#define ERR_NETWORK "Erreur reseau\n"
/* ---- ------- ---- */

/* ---- Configuration ---- */
#define CONF_TITLE "--- Configuration du jeu ---\n"
#define CONF_1 "1) Modifier l'équipe 1\n"
#define CONF_2 "2) Modifier l'équipe 2\n"
#define CONF_3 "3) Modifier le plateau\n"
#define CONF_4 "4) Quitter et jouer une nouvelle partie\n"

#define CONF_11 "--- Configuration équipe 1 ---\n"
#define CONF_12 "1) Modifier le nom de l'équipe\n"
#define CONF_121 "Entrez le nouveau nom\n"
#define CONF_13 "2) Modifier la couleur de l'équipe\n"
#define CONF_131 "Entrez le code couleur\n"

#define CONF_21 "--- Configuration équipe 2 ---\n"
#define CONF_22 "1) Modifier le nom de l'équipe\n"
#define CONF_221 "Entrez le nouveau nom\n"
#define CONF_23 "2) Modifier la couleur de l'équipe\n"
#define CONF_231 "Entrez le code couleur\n"

#define CONF_31 "--- Configuration du plateau ---\n"
#define CONF_32 "1) Modifier la couleur des cases vides\n"
#define CONF_321 "Entrez le code couleur pour les cases vides\n"
#define CONF_33 "2) Modifier le caractère des cases vides\n"
#define CONF_331 "Entrez le caractère\n"
#define CONF_34 "3) Modifier la couleur du cadre\n"
#define CONF_341 "Entrez le code couleur\n"
/* ---- ------------- ---- */

/* ---- Sauvegarde ---- */
#define INFO_NEW_SAVE "Fichier de sauvegarde créé.\n"
#define SAVE_CONFIG "Sauvegarde config : OK\n"
#define SAVE_MAP_TYPE "Sauvegarde map_type : OK\n"
#define SAVE_MAP_ISFILL "Sauvegarde map_isFill : OK\n"
#define SAVE_PIECE_TYPE "Sauvegarde pieces_type : OK\n"
#define SAVE_PIECE_NUMEQUIP "Sauvegarde pieces_numEquip : OK\n"
#define SAVE_DATA "Sauvegarde data : OK\n"
#define SAVE "Sauvegarde faite.\n"
/* ---- ---------- ---- */

/* ---- JUMP ---- */
#define ERR_JUMP_BACK "Impossible de revenir en arrière\n"
#define ERR_JUMP_DISTANCE "La case n'est pas à la bonne distance de saut\n"
#define JUMP_AGAIN "Souhaitez vous encore sauter ? O/N (%d pos)\n"
/* ---- ---- ---- */

/* ---- INPUT ---- */
#define COOR_1 "Entrez x :\n"
#define COOR_2 "Entrez y :\n"
#define COOR_WHERE "Vers quel point souhaitez vous le bouger ?\n"
#define ERR_FORMAT "Mauvais format\n"
/* ---- ----- ---- */

/* ---- MESSAGE ---- */
#define WRONG_PIECE "Mauvais pion"
/* ---- ------- ---- */

#define CHANGE_BUSHI "Changer de Bushi et continuer à jouer ? O/N\n"
#define CHOOSE_BUSHI "Choisissez un nouveau Bushi\n"
#define VICTORY "L'équipe %s à gagné\n"

#else
/* ############### ENGLISH ############### */
#define CHOICE "Choose an option :\n"
#define PLAYER "Player %d\n"

#define MENU_1 "1 - New game\n"
#define MENU_2 "2 - Load game\n"
#define MENU_3 "3 - Play network : host\n"
#define MENU_4 "4 - Play network : join\n"
#define MENU_5 "5 - Settings\n"

#define ERR "Error\n"
#define ERR_NO_FILE "No file.\n"
#define ERR_LOAD_FILE "Can't load. A file is missing.\n"

/* ---- SAVE ---- */
#define INFO_NEW_SAVE "Backup file created.\n"
#define SAVE_CONFIG "Config backup : OK\n"
#define SAVE_MAP_TYPE "Saving map_type : OK\n"
#define SAVE_MAP_ISFILL "Saving map_isFill : OK\n"
#define SAVE_PIECE_TYPE "Saving pieces_type : OK\n"
#define SAVE_PIECE_NUMEQUIP "Saving pieces_numEquip : OK\n"
#define SAVE_DATA "Saving data : OK\n"
#define SAVE "Backup complete.\n"
/* ---- ---- ---- */

/* ---- Configuration ---- */
#define CONF_TITLE "--- Game configuration ---\n"
#define CONF_1 "1) Alter team 1\n"
#define CONF_2 "2) Alter team 2\n"
#define CONF_3 "3) Alter the game board\n"
#define CONF_4 "4) Leave and play a new game\n"

#define CONF_11 "--- Team 1 configuration ---\n"
#define CONF_12 "1) Alter team name\n"
#define CONF_121 "Enter a new team name\n"
#define CONF_13 "2) Alter team color\n"
#define CONF_131 "Enter the color code\n"

#define CONF_21 "--- Team 2 configuration ---\n"
#define CONF_22 "1) Alter team name\n"
#define CONF_221 "Enter a new team name\n"
#define CONF_23 "2) Alter team color\n"
#define CONF_231 "Enter the color code\n"

#define CONF_31 "--- Board configuration ---\n"
#define CONF_32 "1) Alter empty square color\n"
#define CONF_321 "Enter empty square color code\n"
#define CONF_33 "2) Alter empty square character\n"
#define CONF_331 "Enter empty square character\n"
#define CONF_34 "3) Alter frame color\n"
#define CONF_341 "Enter frame color code\n"
/* ---- ------------- ---- */

/* ---- INPUT ---- */
#define COOR_1 "Enter x :\n"
#define COOR_2 "Enter y :\n"
#define COOR_WHERE "Where do you want to move it?\n"
#define ERR_FORMAT "Wrong format\n"
/* ---- ----- ---- */

/* ---- JUMP ---- */
#define ERR_JUMP_BACK "Impossible to go back\n"
#define ERR_JUMP_DISTANCE "Can't jump\n"
#define JUMP_AGAIN "Do you want to jump again? O/N (%d pos)\n"
/* ---- ---- ---- */

/* ---- SOCKETS ---- */
#define SOCK_PORT "Enter the port : "
#define SOCK_IP "Enter IP : "
#define SOCK_WORKING "Socket %d working\n"
#define SOCK_WAITING "Waiting for a player on the port %d\n"
#define SOCK_CONNECT "Connecting on the port %d\n"
#define SOCK_CONNECTED "Connected ! Starting a new game. You are the team "
#define SOCK_START1 "Player connected ! Starting a new game. You are the team "

#define SOCK_CLOSE "Closing socket...\n"
#define SOCK_CLOSE_OK "Socket closed.\n"

#define TURN "Your turn! ("
#define WAIT_TURN "Wait for your turn.\n"
#define ERR_NETWORK "Error network\n"
/* ---- ------- ---- */

/* ---- MESSAGE ---- */
#define WRONG_PIECE "Wrong piece"
/* ---- ------- ---- */

#define CHANGE_BUSHI "Choose another Bushi and continue to play? O/N\n"
#define CHOOSE_BUSHI "Choose the new bushi to play\n"
#define VICTORY "The team %s has won\n"

#endif
#endif
