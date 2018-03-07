/*
 * copy1.c
 * 
 * based on: 
 *
 * Miscellaneous examples for Chap. 2
 * AUP2, Chap. 2
 *
 * modified by WTA
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define BUFSIZE 512

void copy(char *from, char *to)  /* has a bug */
{
	int fromfd = -1, tofd = -1, n;
	ssize_t nread;
	char buf[BUFSIZE];
	
	fromfd = open(from, O_RDONLY);

	if(fromfd == -1) {
        printf("For input file: %s\n", strerror(errno));
        exit(errno);
    }

	tofd = open(to, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR);

	if(tofd == -1) {
        printf("For output file: %s\n", strerror(errno));
        exit(errno);
    }

	while ((nread = read(fromfd, buf, sizeof(buf))) > 0) {
		n = write(tofd, buf, nread);
		if(n == -1) {
			if (errno == EINTR)
				continue;
			else {
				printf("Write error: %s\n", strerror(errno));
        		exit(errno);
			}
		}
	}
	    	
	
    close(fromfd);
	close(tofd);
	return;
}

int main(int argc, char **argv){
	if (argc != 3)
	{
		fprintf(stderr,"usage: %s from_pathname to_pathname\n", argv[0]);
		return 1;
	}
	copy(argv[1], argv[2]);
	return 0;
}