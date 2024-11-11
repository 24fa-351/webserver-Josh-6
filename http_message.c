#include "http_message.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdbool.h>

bool is_complete_http_message(char *buffer)
{

    if (strlen(buffer) < 10)
    {
        //printf("buffer is less than 10 characters!\n");
        return false;
    }
    else if (strncmp(buffer, "GET ", 4) != 0)
    {
        printf("buffer start with \"GET \"!\n");
        return false;
    }
    // else if (strncmp(buffer + strlen(buffer) - 4, "\n\n", 2) != 0) {
    // printf("Spces!\n");
    // return false;
    //}
    return true;
}

void read_http_client_message(int client_sock, http_client_message_t **msg, http_read_result_t *result)
{

    *msg = malloc(sizeof(http_client_message_t));
    if (*msg == NULL)
    {
        *result = BAD_REQUEST;
        return;
    }
    //*msg =  NULL;
    char buffer[1024];
    strcpy(buffer, "");

    while (!is_complete_http_message(buffer))
    {
        
        int bytes_read = read(client_sock, buffer + strlen(buffer), sizeof(buffer) - strlen(buffer));
        if (bytes_read == 0)
        {
            *result = CLOSED_CONNECTION;
            return;
        }
        else if (bytes_read < 0)
        {
            *result = BAD_REQUEST;
            return;
        }
        printf("Buffer content: \n%s\n", buffer);
    }
    (*msg)->method = strndup(buffer, 3);
    char *path_start = buffer + 4;
    char *path_end = strchr(buffer + 4, ' ');
    (*msg)->path = path_end;
    char *http_end = strchr(path_end, ' ');
    (*msg)->http_version = http_end;

    if (path_end != NULL)
    {
        (*msg)->path = strndup(path_start, path_end - path_start); // Extract the path
    }

    if (strcmp((*msg)->path, "/calc") == 0)
    {
        printf("Path is calc\n");

        char *body_start = strchr(buffer, '\n'); // Find the first newline (end of headers)
        if (body_start != NULL)
        {
            body_start++; // Move past the newline character

            // Now parse the numbers from the body (the line after the newline)
            int a, b;
            int num_items = sscanf(body_start, "%d %d", &a, &b);
            if (num_items == 2)
            {
                printf("a = %d\n", a);
                printf("b = %d\n", b);
            }
            else
            {
                printf("Failed to parse numbers from the body\n");
            }
        }
    }
    else if (strcmp((*msg)->path, "/stats") == 0)
    {
        printf("Path is stats\n");
    }
    else if (strcmp((*msg)->path, "/static") == 0)
    {
        printf("Path is static\n");
    }

    *result = MESSAGE;
}

void http_client_message_free(http_client_message_t *msg) { free(msg); }