# ex1open is dependent on ex1open.c Hence, whenever there is a change in any of dependencies, make will take action
ex1open: ex1open.c
	# -pedantic - 	issue all the warnings demanded by strict ISO C and ISO C++
	# -ansi - 		compliance with the ANSI C standard
	# -Wall - 		enables all the warnings about constructions that some users consider questionable, and that are easy to avoid
	gcc -Wall -ansi -pedantic -o ex1open ex1open.c

# phony target made to run commands that do not represent physical files in the file system
.PHONY: clean
# delete *.o files that may remain after compilation
clean:
	rm -f ex1open.o
