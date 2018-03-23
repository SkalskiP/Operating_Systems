all: shell clean

shell: funcs.o funcs.h shell.c
	gcc -Wall -pedantic -ansi -lm funcs.o shell.c -o shell

funcs.o: funcs.h funcs.c
	gcc -c -Wall -pedantic -ansi funcs.c -o funcs.o

.PHONY: clean

clean:
	rm -f *.o
