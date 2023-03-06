/*
 @author luis ortiz, @author ivan garcia
*/
// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <locale.h>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "en_US.utf8");
    int sock, valread;
    struct sockaddr_in serv_addr; // Información sobre la dirección del servidor
    char buffer[100];
    char mensaje[100];

    // socket() permite entablar comunicación con otro ordenadores
    // indica si es orientado a conexión
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        // Llamada al socket
        printf("Error en la creación del Socket \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr)); // Ver que el socket este vacio

    // Datos del servidor
    serv_addr.sin_family = AF_INET;                // Se puede contectar con otro dispositivo
    serv_addr.sin_addr.s_addr = htons(INADDR_ANY); // Atender a cualquier cliente
    serv_addr.sin_port = htons(6000);              // Puerto en el que se realiza la conexión

    // Convierte la dirección IP en formato de texto a formato binario
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nConexión invalida \n");
        return -1;
    }

    // Indicar al sistema que esta abierto el socket
    // bind sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    // Conecta al socket con el servidor
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        // Llamada a connect()
        printf("\nConexión falllida \n");
        return -1;
    }
    printf("Conexión con Servidor exitosa (:\n");
    // Enviar mensaje al servidor
    printf("Ingrese un mensaje: ");
    fgets(mensaje, sizeof(mensaje), stdin);
    mensaje[strcspn(mensaje, "\n")] = 0; // Eliminar el salto de línea al final del mensaje
    send(sock, mensaje, strlen(mensaje), 0);//mandar al servidor el mensaje

    // Leer respuesta del servidor
    valread = read(sock, buffer, sizeof(buffer));
    printf("Mensaje recibido desde el servidor Java: %s\n", buffer);
     

    return 0;
}