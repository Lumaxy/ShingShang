#include "sockets.h"
#include "language.h"
#include "graphConsole.h"

#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

int join(SOCKET *sock, SOCKADDR_IN *sin){
  char ip[20];
  int port;
  int sock_err;

  printf(SOCK_IP);
  scanf("%s", ip);
  printf(SOCK_PORT);
  scanf("%d", &port);

  /* ---- Creation socket ---- */
  *sock = socket(AF_INET, SOCK_STREAM, 0);
  if(*sock != INVALID_SOCKET){
    printf(SOCK_WORKING, *sock);
  }

  /* ---- Configuration socket ---- */
  sin->sin_addr.s_addr = inet_addr(ip);
  sin->sin_family = AF_INET;
  sin->sin_port = htons(port);

  printf(SOCK_CONNECT, port);
  do {
    sock_err = connect(*sock, (SOCKADDR *)sin, sizeof(*sin));
  } while(sock_err == SOCKET_ERROR);

  return 0;
}

void host(SOCKET *sock, SOCKET *csock, SOCKADDR_IN *sin, SOCKADDR_IN *csin){
  int port;
  int sock_err;
  socklen_t recsize = sizeof(csin);

  //Afficher son adresse IP
  printf(SOCK_PORT);
  scanf("%d", &port);

  /* ---- Creation socket ---- */
  *sock = socket(AF_INET, SOCK_STREAM, 0);
  if(*sock != INVALID_SOCKET){
    printf(SOCK_WORKING, *sock);
  }

  /* ---- Configuration socket ---- */
  sin->sin_addr.s_addr = htonl(INADDR_ANY);
  sin->sin_family = AF_INET;
  sin->sin_port = htons(port);

  sock_err = bind(*sock, (SOCKADDR*)sin, sizeof(*sin));
  if(sock_err != SOCKET_ERROR){
    sock_err = listen(*sock, 1); //Une seule connexion autorisee
    if(sock_err != SOCKET_ERROR){
      printf(SOCK_WAITING, port);
      *csock = accept(*sock, (SOCKADDR *) csin, &recsize);

    }else{
      couleur(31);
      printf(ERR_NETWORK);
      couleur(0);
    }
  }else{
    couleur(31);
    printf(ERR_NETWORK);
    couleur(0);
  }}
