all: server client clean

server: ./code/server.c
	gcc ./code/server.c -o ./bin/server

client: ./code/client.c
	gcc ./code/client.c -o ./bin/client

.PHONY: clean

clean:
	rm -f *.o