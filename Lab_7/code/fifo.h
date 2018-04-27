#ifndef FIFO_H
#define FIFO_H
/* ------------------------------------------------------------- */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
/* ------------------------------------------------------------- */

#define MESSAGE_BUF_SIZE 100
#define FIFO_NAME_BUF_SIZE 100
#define PERM_FILE S_IRUSR|S_IWUSR
/* ------------------------------------------------------------- */

struct message
{
  pid_t pid;
  char data[MESSAGE_BUF_SIZE];
};
/* ------------------------------------------------------------- */

void make_srv_fifo_queue_name(char* dest, char* basename, size_t namemax)
{
  snprintf(dest, namemax, "fifo_%s", getlogin());
}
/* ------------------------------------------------------------- */

void make_cnt_fifo_queue_name(char* dest, pid_t p, size_t namemax)
{
  snprintf(dest, namemax, "fifo%ld", (long)p);
}
/* ------------------------------------------------------------- */

/* If returns 0 then user want to exit from application */
int stdin_readall(char* dest, int MAXLEN)
{
  char c;
  int bread = 0, b;
  do
    {
      b = scanf("%c", &c);
      dest[bread] = c;
      bread++;
    }
  while((c != '\n') && (b == 1) && (bread < MAXLEN));

  dest[bread-1] = '\0';

  return strcmp(dest, "q");
}
/* ------------------------------------------------------------- */

#endif
