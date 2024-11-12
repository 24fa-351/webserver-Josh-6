#include "http_message.h"
#include "calc.h"
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
        // printf("buffer is less than 10 characters!\n");
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
    buffer[0] = '\0';

    printf("\nReading message!\n");

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
    }

    /*(*msg)->method = strndup(buffer, 3);
    char *path_start = buffer + 4;
    char *path_end = strchr(buffer + 4, ' ');
    (*msg)->path = path_end;
    char *http_end = strchr(path_end, ' ');
    (*msg)->http_version = http_end;*/

    char *method = strtok(buffer, " ");
    // printf("Full method is: %s\n", method);
    char *path = strtok(NULL, " ");
    // printf("Full path is: %s\n", path);
    char *version = strtok(NULL, "\r\n");
    // printf("Full version is: %s\n", version);

    if (!method || !path || !version)
    {
        *result = BAD_REQUEST;
        free(*msg);
        return;
    }

    (*msg)->method = strdup(method);
    (*msg)->path = strdup(path);
    (*msg)->http_version = strdup(version);
    (*msg)->body = NULL;

    char *initial_path = strtok(path, "/"); // should be equal to stats, static, or calc
    char *subpath1 = NULL;
    char *subpath2 = NULL;

    if (strcmp((*msg)->path, "/stats") == 0)
    {
        printf("Path is stats\n");
    }
    else if (strcmp(initial_path, "calc") == 0)
    {
        subpath1 = strtok(NULL, "/");
        //printf("a = %s\n", subpath1);
        subpath2 = strtok(NULL, "/");
        //printf("b = %s\n", subpath2);

        (*msg)->body = sum(subpath1, subpath2);

    }
    else if (strcmp(initial_path, "static") == 0)
    {
        printf("Path is static\n");

        subpath1 = strtok(NULL, "/");
        printf("Subpath 1 = %s\n", subpath1);
        subpath2 = strtok(NULL, "/");
        printf("Subpath 2 = %s\n", subpath2);
    }

    *result = MESSAGE;
}

void http_client_message_free(http_client_message_t *msg)
{
    if (msg)
    {
        free(msg->method);
        free(msg->path);
        free(msg->http_version);
        free(msg->body); // Free the body
        free(msg);
    }
}