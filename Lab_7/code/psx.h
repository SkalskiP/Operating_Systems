#ifndef PSX_H
#define PSX_H
/* ------------------------------------------------------------- */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
/* ------------------------------------------------------------- */

#define MESSAGE_BUF_SIZE 100
#define PSX_QUEUE_NAME 100
#define PERM_FILE S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH
/* ------------------------------------------------------------- */

struct message
{
  pid_t pid;
  char data[MESSAGE_BUF_SIZE];
};
/* ------------------------------------------------------------- */

void make_srv_psx_name(char* dest, char* name, size_t namemax)
{
  snprintf(dest, namemax, "/psxsrv_%s_%s", name, getlogin());
}
/* ------------------------------------------------------------- */

void make_cnt_psx_name(char* dest, pid_t p, size_t namemax)
{
  snprintf(dest, namemax, "/psxcnt_%ld", (long)p);
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
