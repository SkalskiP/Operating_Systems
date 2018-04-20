all: simple_pipe_new dup_example_new clean

simple_pipe_new: simple_pipe_new.c
	gcc -ansi -pthread -o simple_pipe_new simple_pipe_new.c

dup_example_new: dup_example_new.c
	gcc -ansi -pthread -o dup_example_new dup_example_new.c

.PHONY: clean

clean:
	rm -f *.o