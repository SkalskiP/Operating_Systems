all: copy1 simple_cat clean

copy1: copy1.c
	gcc -Wall -ansi -pedantic -o copy1 copy1.c
	# gcc -Wall -ansi -pedantic -o copy1 copy1.c

simple_cat: simple_cat.c
	# gcc -o simple_cat simple_cat.c
	gcc -Wall -ansi -pedantic -o simple_cat simple_cat.c

.PHONY: clean

clean:
	rm -f *.o
