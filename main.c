#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>

#define PORT 8080
#define BUF_SIZE 1024

void manejar_cliente(int cliente_fd)
{
    char buffer[BUF_SIZE];

    while (1)
    {
        int bytes = recv(cliente_fd, buffer, BUF_SIZE - 1, 0);
        if (bytes <= 0)
            break;
        buffer[bytes] = '\0';
        printf("Cliente dice: %s", buffer);
        printf("\n"); // Asegura el salto de línea

        send(cliente_fd, buffer, bytes, 0); // Eco
    }

    close(cliente_fd);
    printf("Cliente desconectado\n");
}

int main()
{
    int servidor_fd, cliente_fd;
    struct sockaddr_in direccion;
    socklen_t addr_len = sizeof(direccion);

    // Evitar procesos zombie
    signal(SIGCHLD, SIG_IGN);

    servidor_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (servidor_fd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = INADDR_ANY;
    direccion.sin_port = htons(PORT);

    if (bind(servidor_fd, (struct sockaddr *)&direccion, sizeof(direccion)) < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(servidor_fd, 5) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Servidor escuchando en puerto %d...\n", PORT);

    while (1)
    {
        cliente_fd = accept(servidor_fd, (struct sockaddr *)&direccion, &addr_len);
        if (cliente_fd < 0)
        {
            perror("accept");
            continue;
        }

        printf("Nuevo cliente conectado\n");

        pid_t pid = fork();
        if (pid == 0)
        {
            // Proceso hijo
            close(servidor_fd); // El hijo no necesita el socket del servidor
            manejar_cliente(cliente_fd);
            exit(0); // Termina el hijo
        }
        else if (pid > 0)
        {
            // Proceso padre
            close(cliente_fd); // El padre no maneja esta conexión
        }
        else
        {
            perror("fork");
        }
    }

    close(servidor_fd);
    return 0;
}
