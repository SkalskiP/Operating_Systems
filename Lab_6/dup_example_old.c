    #include <unistd.h>
    #include <sys/types.h>
     
    int main(void)
    {
            int     pfd[2];
            pid_t   pid;
            char    string[] = "Test";
            char    buf[10];
     
            pipe(pfd);
            pid = fork();
     
            if(pid == 0) {
    		close(0);              
     		dup(pfd[0]);
            	read(STDIN_FILENO, buf, sizeof(buf));
                    printf("Wypisuje: %s", buf);
            } else {
            	write(pfd[1], string, (strlen(string)+1));        
    	}
     
            return 0;
    }

