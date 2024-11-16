web: server.c http_message.c calc.c static.c
	gcc server.c http_message.c calc.c static.c -o web -pthread

clean:
	rm -f web