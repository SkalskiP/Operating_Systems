all: srvfifo srvsv srvpsx eliza clean

srvfifo: ./code/srvfifo.c ./code/cntfifo.c
	gcc ./code/srvfifo.c -o ./bin/srvfifo
	gcc ./code/cntfifo.c -o ./bin/cntfifo

srvsv: ./code/srvsv.c ./code/cntsv.c
	gcc ./code/srvsv.c -o ./bin/srvsv
	gcc ./code/cntsv.c -o ./bin/cntsv

srvpsx: ./code/srvpsx.c ./code/cntpsx.c
	gcc ./code/srvpsx.c -o ./bin/srvpsx -lrt
	gcc ./code/cntpsx.c -o ./bin/cntpsx -lrt

eliza: ./code/eliza.c ./code/elizaClient.c ./code/elizaServer.c
	gcc ./code/eliza.c -o ./bin/eliza
	gcc ./code/elizaClient.c -o ./bin/elizaClient
	gcc ./code/elizaServer.c -o ./bin/elizaServer

.PHONY: clean

clean:
	rm -f *.o