#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>

#include <sys/types.h>
#include <sys/stat.h>
/* ------------------------------------------------------------- */

#include "psx.h"
/* ------------------------------------------------------------- */

int main(void)
{
  char* srvpsxqbasename = "psxsrvqueue";
  char srvpsxqname[PSX_QUEUE_NAME];
  char cntpsxqname[PSX_QUEUE_NAME];
  mqd_t qdsrv,
    qdcnt;
  ssize_t msgsize,
    bread,
    bwrite;
  struct message msg;
  
  printf("Server started...\n");
  setbuf(stdout, NULL);
  msgsize = sizeof(msg);

  /* Creating server psx queue */
  make_srv_psx_name(srvpsxqname, srvpsxqbasename, PSX_QUEUE_NAME);

  /* Opening server psx queue */
  printf("Opening server queue \'%s\' for reading...", srvpsxqname);
  mq_unlink(srvpsxqname);
  qdsrv = mq_open(srvpsxqname, O_RDONLY | O_CREAT, PERM_FILE, NULL);
  if(qdsrv == -1)
    {
      printf("FAIL!\nError: %s.\n", strerror(errno));
      return 0;
    }
  printf("OK\n");

  while(1)
    {
      /* Reading from queue */
      printf("Waiting for data...\n");
      bread = mq_receive(qdsrv, (char*)&msg, msgsize, NULL);
      if(bread == -1)
	{
	  printf("FAIL!\nError: %s\n", strerror(errno));
	  break;
	}
      printf("Message from [%ld]: %s\n", (long)msg.pid, msg.data);

      /* Getting responce */
      printf("Your responce: ");
      if(stdin_readall(msg.data, MESSAGE_BUF_SIZE) == 0)
	break;

      /* Creating client queue name */
      make_cnt_psx_name(cntpsxqname, msg.pid, PSX_QUEUE_NAME);

      /* Opening client fifo for writing  */
      printf("Opening client queue \'%s\' for writing...", cntpsxqname);
      qdcnt = mq_open(cntpsxqname, O_WRONLY);
      if(qdcnt == -1)
	{
	  printf("FAIL!\nError: %s\n", strerror(errno));
	  break;
	}

      /* Sending responce */
      printf("OK\nWritting responce to client %ld...", (long)msg.pid);
      bwrite = mq_send(qdcnt, (const char*)&msg, sizeof(msg), 0);
      if(bwrite == -1)
	{
	  printf("FAIL!\nError: %s\n", strerror(errno));
	  break;
	}
      printf("OK\n");
      mq_close(qdcnt);
    }
  
  
  /* Cleaning up */
  mq_close(qdsrv);
  mq_unlink(srvpsxqname);
  
  return 0;
}
