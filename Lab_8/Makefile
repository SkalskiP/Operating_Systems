all: shm sem clean

shm: ./code/shm.c ./code/unix.h
	gcc ./code/shm.c -o ./bin/shm

sem: ./code/sem.c ./code/unix.h
	gcc ./code/sem.c -o ./bin/sem

.PHONY: clean

clean:
	rm -f *.o