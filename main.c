#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8080
#define BUF_SIZE 1024

int main()
{
    int servidor_fd, cliente_fd;
    struct sockaddr_in direccion;
    char buffer[BUF_SIZE];

    servidor_fd = socket(AF_INET, SOCK_STREAM, 0);

    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = INADDR_ANY;
    direccion.sin_port = htons(PORT);

    bind(servidor_fd, (struct sockaddr *)&direccion, sizeof(direccion));
    listen(servidor_fd, 5);
    printf("Servidor esperando en puerto %d...\n", PORT);

    cliente_fd = accept(servidor_fd, NULL, NULL);
    printf("Cliente conectado\n");

    while (1)
    {
        int bytes = recv(cliente_fd, buffer, BUF_SIZE, 0);
        if (bytes <= 0)
            break;
        buffer[bytes] = '\0';
        printf("Cliente dice: %s", buffer);
        send(cliente_fd, buffer, bytes, 0); // Echo
    }

    close(cliente_fd);
    close(servidor_fd);
    return 0;
}
