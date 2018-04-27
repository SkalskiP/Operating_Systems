#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "fifo.h"

/* ------------------------------------------------------------- */

int main(void) {
    struct message msg;
    char* fifosrvbasename = "srvfifoqueue";
    char fifosrvname[FIFO_NAME_BUF_SIZE];
    char fifocntname[FIFO_NAME_BUF_SIZE];
    int fdsrv, fdcnt1,
            fdcnt,
            bread,
            bwrite;

    printf("Client [%ld] started...\n", (long) getpid());
    setbuf(stdout, NULL);
    msg.pid = getpid();

    /* Creating client fifo name */
    make_cnt_fifo_queue_name(fifocntname, msg.pid, FIFO_NAME_BUF_SIZE);
    printf("Creating client fifo queue \'%s\'...", fifocntname);
    if ((mkfifo(fifocntname, PERM_FILE) == -1) && (errno != EEXIST)) {
        printf("FAIL!\nError: %s\n", strerror(errno));
        return 0;
    }

    /* Opening server fifo for writing */
    make_srv_fifo_queue_name(fifosrvname, fifosrvbasename, FIFO_NAME_BUF_SIZE);
    printf("OK\nOpening server fifo queue \'%s\' for writing...", fifosrvname);
    fdsrv = open(fifosrvname, O_WRONLY);
    if (fdsrv == -1) {
        printf("FAIL!\nError: %s\n", strerror(errno));
        return 0;
    }
    printf("OK\n");

    while (1) {
        /* Getting message */
        printf("Send message: ");
        if (stdin_readall(msg.data, MESSAGE_BUF_SIZE) == 0)
            break;

        /* Sending message to server */
        printf("Writing message to server...");
        bwrite = write(fdsrv, &msg, sizeof (msg));
        if (bwrite == -1) {
            printf("FAIL!\nError: %s\n", strerror(errno));
            break;
        }

        /* Opening client fifo for reading */
        printf("OK\nOpening client fifo queue \'%s\' for reading...", fifocntname);
        fdcnt = open(fifocntname, O_RDONLY | O_NONBLOCK);
        fcntl(fdcnt, F_SETFL, fcntl(fdcnt, F_GETFL, 0) & ~O_NONBLOCK);
        fdcnt1 = open(fifocntname, O_WRONLY);
        if (fdcnt == -1) {
            printf("FAIL!\nError: %s\n", strerror(errno));
            break;
        }
        printf("OK\n");

        /* Reading responce */
        printf("Waiting for data...");
        bread = read(fdcnt, &msg, sizeof (msg));
        if (bread == -1) {
            printf("FAIL!\nError: %s\n", strerror(errno));
            close(fdcnt);
            break;
        }
        close(fdcnt);
        close(fdcnt1);
        printf("OK\nMessage from server: %s\n", msg.data);
    }

    /* Cleaning up */
    close(fdsrv);
    unlink(fifocntname);

    return 0;
}