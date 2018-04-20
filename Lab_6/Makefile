all: simple_pipe_new clean

simple_pipe_new: simple_pipe_new.c
	gcc -pthread -o simple_pipe_new simple_pipe_new.c

.PHONY: clean

clean:
	rm -f *.o