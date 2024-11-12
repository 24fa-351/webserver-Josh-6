web: server.c http_message.c calc.c
	gcc server.c http_message.c calc.c -o web -pthread

clean:
	rm -f web