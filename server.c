#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#define USERS 5
#define DEFAULT_PORT 80

int main(int argc, char *argv[]) 
{
    int server_socket, client_socket, port;
    struct sockaddr_in server_address, client_address;
    socklen_t client_len = sizeof(client_address);

    // Argument parsing for -p
    if (argc != 3 || strcmp(argv[1], "-p") != 0) {
        //fprintf(stderr, "Format: %s -p <port>\n", argv[0]);
        //exit(EXIT_FAILURE);
        port = DEFAULT_PORT;
    }
    else{
    port = atoi(argv[2]);}
    
    // Create a TCP socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("Socket creation failed..\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Socket successfully created..\n"); 
        bzero(&server_address, sizeof(server_address)); 
    }

    // assign ip to port
    memset(&server_address, '\0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    // Binding newly created socket to given IP and verification 
    if ((bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address))) != 0) { 
        perror("socket bind failed..\n"); 
        close(server_socket);
        exit(EXIT_FAILURE); 
    } 
    else {
        printf("Socket successfully binded..\n"); }

    // Server is ready to listen and verification
    if(listen(server_socket, USERS) == -1)
    {
        perror("listen failed..\n"); 
        close(server_socket);
        exit(EXIT_FAILURE); 
    } 
    else{
        printf("Server listening..\n"); }

    printf("Server listening on port %d\n", port);

    while(1)
    {
        
        // Accept client connection
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_len);

        if (client_socket == -1)
        {
            perror("Accept failed\n");
            continue;
        }
        
        printf("Client connected\n");

        /*int *client_socket_ptr = malloc(sizeof(int));
        *client_socket_ptr = client_socket;

        pthread_t client_thread;
        pthread_create(&client_thread, NULL, handle_client, client_socket_ptr);
        pthread_detach(client_thread);*/ 

    }

    close(server_socket);
    return 0;
}