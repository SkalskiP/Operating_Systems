all: hello2 func2 clean

hello2: hello2.c
	gcc -pthread -o hello2 hello2.c

func2: func2.c
	gcc -pthread -o func2 func2.c

.PHONY: clean

clean:
	rm -f *.o
