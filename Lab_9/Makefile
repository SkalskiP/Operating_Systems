all: morse ses clean

morse: ./code/morse-temp.c
	gcc ./code/morse-temp.c -o ./bin/morse-temp

ses: ./code/sessions.c
	gcc ./code/sessions.c -o ./bin/sessions

.PHONY: clean

clean:
	rm -f *.o