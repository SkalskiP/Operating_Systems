    #include <stdio.h>
    #include <unistd.h>
    #include <string.h>
     
    int main(int argc, char *argv[]){
     
    int pfd[2];
    size_t nread;
    char buf[100];
     
    pipe(pfd);
    char * str ="Ur beautiful pipe example";
    write(pfd[1], str, strlen(str));
    nread=read(pfd[0],buf, sizeof(buf));
     
    (nread!=0)?printf("%s (%ld bytes)\n",buf,(long)nread):printf("No data\n");
     
    return 0;
    }