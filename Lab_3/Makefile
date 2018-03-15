all: stat_info clean

stat_info: stat_info.c
	gcc -o stat_info stat_info.c
	# gcc -Wall -ansi -pedantic -o stat_info stat_info.c

.PHONY: clean

clean:
	rm -f *.o
