#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "sv.h"

/* ------------------------------------------------------------- */

int main(void) {
    struct message msg;
    char svsrvname[SRV_KEYFILE_PATH_SIZE];
    ssize_t brcv,
            bsnd;
    int kfor, /* Key File Opening Result */
            svsrvqid;
    key_t qkey;

    printf("Server started...\n");
    setbuf(stdout, NULL);
    msg.clientid = -1;

    /* Creating server key file */
    printf("Creating server key file:\n");
    make_srv_sv_queue_name(svsrvname, SRV_KEYFILE_PATH_SIZE);
    printf("\tPath: %s\n", svsrvname);
    printf("\tOpening server key file...");
    kfor = open(svsrvname, O_WRONLY | O_CREAT, PERM_FILE);
    if (kfor == -1) {
        printf("FAIL!\nError: %s\n", svsrvname, strerror(errno));
        return 0;
    }
    close(kfor);
    printf("OK\n");

    /* Getting queue key */
    printf("Getting queue key...");
    qkey = ftok(svsrvname, 1);
    if (qkey == -1) {
        printf("FAIL!\nError: %s\n", strerror(errno));
        return 0;
    }
    printf("OK\n");

    /* Getting server queue identifier */
    printf("Getting server queue identifier...");
    svsrvqid = msgget(qkey, PERM_FILE);
    if (svsrvqid == -1) {
        printf("the queue already exists, removing it...");
        msgctl(svsrvqid, IPC_RMID, NULL);
        svsrvqid = msgget(qkey, IPC_CREAT | PERM_FILE);
    }
    if (svsrvqid == -1) {
        printf("FAIL!\nError: %s\n", strerror(errno));
        return 0;
    }
    printf("OK\n");


    while (1) {
        /* Reading from queue */
        printf("Waiting for data...");
        brcv = msgrcv(svsrvqid, &msg, MESSAGE_BUF_SIZE, 0, 0);
        if (brcv == -1)
            break;
        printf("OK\nMessage from client [%ld]: %s\n", msg.clientid, msg.data);

        /* Responce getting and sending */
        printf("Your responce: ");
        if (stdin_readall(msg.data, MESSAGE_BUF_SIZE) == 0)
            break;

        printf("Writting responce to client %ld...", msg.clientid);
        bsnd = msgsnd(msg.clientid, &msg, MESSAGE_BUF_SIZE, 0);
        if (bsnd == -1) {
            printf("FAIL!\nError: %s\n", strerror(errno));
            break;
        }
        printf("OK\n");
    }

    /* Cleaning up */
    unlink(svsrvname);
    msgctl(svsrvqid, IPC_RMID, NULL);
    if (msg.clientid != -1)
        msgctl(msg.clientid, IPC_RMID, NULL);

    return 0;
}