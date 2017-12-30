#ifndef SOCK_H
#define SOCK_H

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

int join(SOCKET *sock, SOCKADDR_IN *sin);
void host(SOCKET *sock, SOCKET *csock, SOCKADDR_IN *sin, SOCKADDR_IN *csin);

#endif
