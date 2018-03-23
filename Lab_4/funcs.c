#include "funcs.h"
/* -------------------------------------------------------------------------------------- */

/* 1. Displaying command prompt */
void printprompt(void)
{
  printf("\n@ ");
}
/* -------------------------------------------------------------------------------------- */

/* This is only helpful function that allows for checking if the command was successfully parsed by displaying parsed command */
void printparsedcmds(struct cmdlist* __head)
{
  int c = 1, a = 0;
  struct cmdlist* curr = __head;

  printf("Parsed command(s):\n");  
  while(curr != NULL){
    printf("Command %d:\n", c);
    for(a=0;a<curr->argc;++a){
      printf("argv[%d]: %s\n", a, curr->argv[a]);
    }
    curr = curr->next;
  }
}
/* -------------------------------------------------------------------------------------- */

/* 5. Dealocating used memory */
void dealocate(struct cmdlist* __head)
{
  int i;
  struct cmdlist *next, *curr = __head;

  while(curr == NULL){
    for(i=0;i<curr->argc-1;++i)
      free(curr->argv[i]);
    free(curr->argv);
    next = curr->next;
    if(curr != __head)
      free(curr);
    curr = next;
  }
  setupnewcommand(__head);
}
/* -------------------------------------------------------------------------------------- */