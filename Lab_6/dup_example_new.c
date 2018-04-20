#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int pfd[2];
    pid_t pid;
    char string[] = "Test";
    char buf[10];

    if (pipe(pfd) == -1) {
        perror("Something went wrong with pipe:");
        exit(EXIT_FAILURE);
    }
    pid = fork();

    if (pid == 0) {
        close(STDIN_FILENO); /* zamykamy 0,  bo dup go pozniej uzyje jako najnizszego */
        dup2(pfd[0], STDIN_FILENO);
        close(pfd[1]);
        close(pfd[0]);
        read(STDIN_FILENO, buf, sizeof (buf));
        printf("Wypisuje: %s", buf);
    } else {
        close(pfd[0]);
        write(pfd[1], string, (strlen(string) + 1));
    }

    return 0;
}