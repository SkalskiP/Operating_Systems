#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int pfd[2];
    size_t nread;
    char buf[1000];
    char * str = "Ur beautiful pipe example";
    char * str_write_start = "Writing to pipe...\n";
    char * str_write_end = "Writing to pipe ended\n";
    char * str_read_start = "Reading from pipe...\n";
    char * str_read_end = "Reading from pipe ended\n";
    int pid;

    pipe(pfd);
    write(pfd[1], str, strlen(str));
    nread = read(pfd[0], buf, sizeof (buf));
    switch (pid = fork()) {
        case -1:
            exit(EXIT_FAILURE);
        case 0:
            printf("%s" , str_read_start);
            close(pfd[1]);
            nread = read(pfd[0], buf, sizeof(buf));
            (nread != 0) ? printf("%s (%ld bytes)\n", buf, (long) nread) : printf("No data\n");
            printf("%s" , str_read_end);
            break;
        default:
            printf("%s" , str_write_start);
            close(pfd[0]);
            write(pfd[1], str, strlen(str));
            printf("%s" , str_write_end);
    }
    return 0;
}