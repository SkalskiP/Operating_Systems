    #include <string.h>
     
    int main(void) {
      char *kod[]={".- ","-... ","-.-. ","-.. ",". ","..-. ","--. ",".... ",".. ",".--- ",
    	        "-.- ",".-.. ","-- ","-. ","--- ",".--. ","--.- ",".-. ","... ","- ",
    	        "..- ","...- ",".-- ","-..- ","-.-- ","--.. "};
      char bufor[6] = "";
      char znak;
     
      while(read(0,&znak,1) && znak != '\n') {
        strcpy(bufor,kod[znak-'a']);
        write(1,bufor, 6);
      }
     
      return 0;
    }

