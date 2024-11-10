server: server.c
	gcc server.c -o server -pthread

web: server.c http_message.c
	gcc server.c http_message.c -o web -pthread