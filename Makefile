web: server.c http_message.c
	gcc server.c http_message.c -o web -pthread