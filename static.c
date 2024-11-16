#include "static.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdbool.h>

char* bin(char* subpath1, char* subpath2)
{
    if (!subpath1 || !subpath2)
    {
        return NULL; // Invalid input
    }

    //printf("Subpath 1 = %s\n", subpath1);
    //printf("Subpath 2 = %s\n", subpath2);

    // Make file path
    char filepath[1000];
    snprintf(filepath, sizeof(filepath), "%s/%s", subpath1, subpath2);
    printf("File path: %s\n", filepath);

    FILE *file = fopen(filepath, "rb");  // Open the file in binary mode
    if (!file) {
        printf("Error opening file\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END); // Puts pointer to the end of the file
    long filesize = ftell(file); // Determines the size of the file
    rewind(file); // Puts pointer back to the beginning

    char *content = malloc(filesize + 2);
    fread(content, 1, filesize, file);
    fclose(file);

    printf("Returing binary content:\n");
    printf("\n%s\n",content);

    content[filesize] = '\0';  // Adds a null termination at the end of content
    return content;
}