#ifndef FUNCS_H
#define FUNCS_H
/* -------------------------------------------------------------------------------------- */

#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <stdio.h>
/* -------------------------------------------------------------------------------------- */

#define CONJUD 0     /* undefined operator */
#define CONJOR 1     /* or operator || */
#define CONJAND 2    /* and operator && */
#define MAXCMD 4096
#define RESERROR 0
#define RESSUCCESS 1
/* -------------------------------------------------------------------------------------- */

struct cmdlist
{
  char** argv;               /* The command argv[0] and list of its arguments argv[1...argc-1]  */
  int argc;                  /* The numer of elements in the argv array  */
  int conjuction;            /* Indicates which operator (|| or &&) was used before this command */
  struct cmdlist* next;      /* Pioter to the next command. NULL denotes the last element.  */
};
/* -------------------------------------------------------------------------------------- */

void setupnewcommand(struct cmdlist* __cmd);
void printprompt(void);
int readcmd(char* __buf, int __bufsize);
int parsecmd(char* __buf, int __bufsize, struct cmdlist* __head);
void printparsedcmds(struct cmdlist* __head);
int executecmds(struct cmdlist* __head);
void dealocate(struct cmdlist* __head);
/* -------------------------------------------------------------------------------------- */

#endif