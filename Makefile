C=gcc
CFLAGS=-std=gnu99 -g -Wall -Wextra -pedantic -pthread

hinfosvc: hinfosvc.o
	$(C) $(CFLAGS) hinfosvc.o -o hinfosvc

hinfosvc.o: hinfosvc.c
	$(C) $(CFLAGS) -c hinfosvc.c -o hinfosvc.o

clean:
	rm *.o hinfosvc -f

zip:
	zip xvalen27.zip *.c Makefile