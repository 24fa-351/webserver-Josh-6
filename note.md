-----------
GET /index.html HTTP/1.1
Host: localhost
Date: sdfadas
Accept: text/plain
Content-length: 0

-----------
Date: Wed, 06 Nov 2024 20:22:58 GMT
Server: Apache
Last-Modified: Thu, 05 Nov 2015 04:53:39 CMT
ETag: “ec-523C3e9170d07"
Accept-Ranges: bytes
Content-Length: 21
Vary: Accept-Encoding
Content-Type: text/html
<html>shut ups</html>

----------
GET /calc HTTP/1.1
10 12


-----------
request.h
#ifndef HEADER_H
#define HEADER_H

typedef struct {
    char* method;
    char* path;
    char* version;
} Request;

Request* request_read(int fd);

void request_free(Request* req);

void request_print(Request* req);

#endif

-----------
request.c
while (1) {
        Request* req = request_read(sock_fd);
        if (req == NULL) {
            break;
        }
        request_print(req);
        //dispatch_request(req, sock_fd);
        request_free(req);
    }

----------
server.c
if (argc == 2 && strcmp(argv[1], "-") == 0) {
        Request* req = request_read(stdin);
        if (req != NULL) {
            request_print(req);
            request_free(req);
        }
        printf("done with stdin\n");
        return 0;
    }