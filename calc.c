#include "calc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdbool.h>

char* sum(char* subpath1, char* subpath2)
{
    if (!subpath1 || !subpath2)
    {
        return NULL; // Invalid input
    }

    int a = atoi(subpath1);
    int b = atoi(subpath2);
    int sum = a + b;

    // Allocate and format the body
    int result_size = snprintf(NULL, 0, "a = %d\nb = %d\nsum = %d\n\n", a, b, sum) + 1; // calculates length of the string
    char* result = malloc(result_size + 1);
    if (result != NULL)
    {
        snprintf(result, result_size, "a = %d\nb = %d\nsum = %d\n\n", a, b, sum);
    }

    return result;
}