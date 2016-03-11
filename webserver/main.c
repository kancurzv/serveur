#include <stdio.h>
#include <string.h>
#include "socket.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <stdlib.h>


int main()
{
   int serv;
   int socket_client;
   char message [1024] = "";
   const char *message_bienvenue;

   serv = creer_serveur(8080);

   if (serv == -1)
   {
      perror("creer_serveur");
      return -1;
   }

   initialiser_signaux();

   while (1)
   {
      socket_client = accept(serv, NULL, NULL);
      if (socket_client == -1)
      {
         perror("accept");
      }
      int pid = fork();
      if (pid == 0)
      {
         message_bienvenue = "Bienvenue sur notre serveur !";
         write(socket_client, message_bienvenue, strlen(message_bienvenue));

         while (1)
         {
	   FILE * fich;
	   fich = fdopen(socket_client, "w+");
	   while (fgets(message, sizeof(message), fich) != NULL) {
	     printf("<Serveur Web> %s", message);
	   }
         }
	return 0;
      }
      else
      {
         close(socket_client);
      }
   }
   return 0;
}


