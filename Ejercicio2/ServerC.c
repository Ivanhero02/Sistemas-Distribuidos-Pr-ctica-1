/*
 @author luis ortiz, @author ivan garcia
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5604

int main(int argc, char *argv[])
{
    int serversock, clientsock, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    int number;
    int numero;

    // Crear socket
    if ((serversock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Asignar dirección y puerto al socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(serversock, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Escuchar por conexiones entrantes
    if (listen(serversock, 1) < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    // Esperar por una conexión entrante y aceptarla
    if ((clientsock = accept(serversock, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    printf("Conexión establecida correctamente\n");
          // Leer el número enviado por el cliente
    do // comienzo de ciclo mientras no se mande un 0
    {
        valread = read(clientsock, buffer, 1024);
        if (valread < 0)
        {
            perror("read failed");
            exit(EXIT_FAILURE);
        }
        number = atoi(buffer);
                printf("Número recibido: %d\n");
                numero = number + 1;
            if (number != 0)
            {
                sprintf(buffer, "%d", numero);
                printf("Enviando el número recibido más una unidad...\n");
                // Enviar la cadena de caracteres al servidor
                send(clientsock, buffer, strlen(buffer), 0);
                numero = 0;
            }

    } while (number != 0);

    close(clientsock);
    close(serversock);

    return 0; 
    }
