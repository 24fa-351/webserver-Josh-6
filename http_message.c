#include "http_message.h"
#include <stdlib.h>
#include <stdio.h>

void read_http_client_message(int client_sock, http_client_message_t** msg, http_read_result_t* result)
{
    
    *msg =  NULL;
    *result = CLOSED_CONNECTION;
}

void http_client_message_free(http_client_message_t* msg) { free(msg);}