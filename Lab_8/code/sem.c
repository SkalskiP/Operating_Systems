/*
    Wspolna pamiec + semafory
    -------------------------

*/

#include "unix.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define KLUCZ 12345
// wszystkie osoby musza miec inny klucz !
// (nr legitymacji ?)

struct KONTA {
  long konto1, konto2;
};
typedef struct KONTA *konta_t;
konta_t c;

int koniec=0;

void ObslugaSIGINT(int i)
{
  printf("SIGINT: getpid()=%i, konto1+konto2=%li\n",
	 getpid(),
    c->konto1+c->konto2
	 );
  koniec=1;
}

int main()
{
  signal(SIGINT,ObslugaSIGINT);

  int pid=fork();
  if(pid!=0)
    { // pm
      printf("pm: poczatek; getpid()=%i\n", getpid());

      if(fork()==0)
	{ // pp2
	  /*
         to jest jedynie proces kontrolny !
	  */

	  printf("pp2: poczatek; getpid()=%i\n", getpid());
	  sleep(1);

	  int i,j;
	  printf("pp2: uzyskujemy id wspolnej pamieci ...\n");
	  int id= shmget(KLUCZ, 0, 0);
	  if(id==-1) perror("pp2: shmget; Blad !!!");

	  c=(konta_t)shmat(id, 0, 0);
	  if(c==(konta_t)-1) { perror("pp2: shmat; Blad !!!"); exit(1); }

	  while(1) {
	    sleep(1);
	    printf("pp2: konto1+konto2=%li\n", 
          c->konto1+c->konto2
		   );
	    if(koniec) break;
	  }
    
	  i=shmdt(c);
	  if(i==-1) perror("pp2: shmdt; Blad !!!");
      
	  printf("pp2: koniec\n");
	  exit(0);
	}
        
      int i,j;
      printf("pm: uzyskujemy id wspolnej pamieci ...\n");
      int id= shmget(KLUCZ, sizeof(struct KONTA), IPC_CREAT|IPC_EXCL|0777);
      if(id==-1) perror("pm: shmget; Blad !!!");

      printf("pm: uzyskujemy id zbioru semaforow ...\n");
      int id2= semget(KLUCZ, 1, IPC_CREAT|IPC_EXCL|0777);
      if(id2==-1) perror("pm: semget; Blad !!!");
    
      printf("pm: inicjujemy semafory ...\n");
      // podobno to powinno byc zdefiniowane w <sys/sem.h> ???
      union semun {
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
      };
      union semun arg;
      arg.val=0;
      j=semctl(id2, 0, SETVAL, arg);
      if(j==-1) perror("pm: semctl; Blad !!!");

      c=(konta_t)shmat(id, 0, 0);
      if(c==(konta_t)-1) { perror("pm: shmat; Blad !!!"); exit(1); }

      c->konto1=1234567L;
      c->konto2=0;
    
      while(1) {

	struct sembuf buf;
	buf.sem_num=0;
	buf.sem_op=-1;
	buf.sem_flg=0;
	i=semop(id2, &buf, 1);
	if(i==-1) perror("pm: semop(-1); Blad !!!");
    
	long przelew=random();
	c->konto1-=przelew;
	c->konto2+=przelew;
      
	buf.sem_num=0;
	buf.sem_op=+1;
	buf.sem_flg=0;
	i=semop(id2, &buf, 1);
	if(i==-1) perror("pm: semop(+1); Blad !!!");
      
	if(koniec) break;
      }
    
      i=shmdt(c);
      if(i==-1) perror("pm: shmdt; Blad !!!");

      int pid1,status;
      printf("pm: wait() ...\n");
      pid1=wait(&status);
      printf("pm: wait()=%i status=%04X\n", pid1, status);
      printf("pm: wait() ...\n");
      pid1=wait(&status);
      printf("pm: wait()=%i status=%04X\n", pid1, status);

      printf("pm: usuwamy segment pamieci dzielonej\n");
      i=shmctl(id, IPC_RMID, NULL);
      if(i==-1) perror("pm: shmctl(IPC_RMID); Blad !!!");

      printf("pm: usuwamy zbior semaforow\n");
      i=semctl(id2, 0, IPC_RMID, NULL);
      if(i==-1) perror("pm: semctl(IPC_RMID); Blad !!!");

      printf("pm: koniec\n");
    }
  else
    { // pp
      printf("pp: poczatek; getpid()=%i\n", getpid());
      sleep(1);

      int i,j;
      printf("pp: uzyskujemy id wspolnej pamieci ...\n");
      int id= shmget(KLUCZ, 0, 0);
      if(id==-1) perror("pp: shmget; Blad !!!");

      printf("pp: uzyskujemy id zbioru semaforow ...\n");
      int id2= semget(KLUCZ, 0, 0);
      if(id2==-1) perror("pp: semget; Blad !!!");

      c=(konta_t)shmat(id, 0, 0);
      if(c==(konta_t)-1) { perror("pp: shmat; Blad !!!"); exit(1); }

      while(1) {

	struct sembuf buf;
	buf.sem_num=0;
	buf.sem_op=-1;
	buf.sem_flg=0;
	i=semop(id2, &buf, 1);
	if(i==-1) perror("pp: semop(-1); Blad !!!");
    
	long przelew=random();
	c->konto1-=przelew;
	c->konto2+=przelew;

	buf.sem_num=0;
	buf.sem_op=+1;
	buf.sem_flg=0;
	i=semop(id2, &buf, 1);
	if(i==-1) perror("pp: semop(+1); Blad !!!");
      
	if(koniec) break;
      }
    
      i=shmdt(c);
      if(i==-1) perror("pp: shmdt; Blad !!!");

      printf("pp: koniec\n");
      exit(0);
    }

}
