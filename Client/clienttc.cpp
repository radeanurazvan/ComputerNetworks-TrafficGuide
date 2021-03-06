/* cliTCPIt.c - Exemplu de client TCP
   Trimite un numar la server; primeste de la server numarul incrementat.
         
   Autor: Lenuta Alboaie  <adria@infoiasi.ro> (c)2009
*/
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <thread>

/* codul de eroare returnat de anumite apeluri */
extern int errno;

/* portul de conectare la server*/
int port;

void readFromServer(int sd){
  while(true){
    char messageBack[255];
    bzero(messageBack, sizeof(messageBack));
    if (read(sd, messageBack, 255) <= 0)
    {
      perror("[client] Server read error.\n");
      break;
    }

    printf("[client] Received server response: %s\n\n", messageBack);
  }
}

void writeToServer(int sd) {
  while(true) {
    char mesaj[255];
    std::cin.getline(mesaj, 255);
    printf("[client] Sending message %s\n\n", mesaj);
    auto writtenBytes = write(sd, mesaj, 255);
    if (writtenBytes <= 0)
    {
      perror("[client] Write error.\n");
      break;
    }
    else
    {
      printf("[client] Successfully written %d bytes \n", writtenBytes);
    }
  }
}

int main(int argc, char *argv[])
{
  int sd;                    // descriptorul de socket
  struct sockaddr_in server; // structura folosita pentru conectare
                             // mesajul trimis

  /* stabilim portul */
  port = 8080;

  /* cream socketul */
  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("[client]Socket error.\n");
    return errno;
  }

  /* umplem structura folosita pentru realizarea conexiunii cu serverul */
  /* familia socket-ului */
  server.sin_family = AF_INET;
  /* adresa IP a serverului */
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  /* portul de conectare */
  server.sin_port = htons(port);

  /* ne conectam la server */
  if (connect(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
  {
    perror("[client]Connect error .\n");
    return errno;
  }
  else
  {
    printf("[client]Connected\n");
  }

  auto readThread = std::thread([sd]() {
    readFromServer(sd);
  });
  readThread.detach();
  auto writeThread = std::thread([sd]() {
    writeToServer(sd);
  });
  writeThread.join();
  // close(sd);
}
