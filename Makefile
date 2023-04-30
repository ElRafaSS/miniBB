#CC=arm-linux-gnueabihf-gcc
CC=gcc
GFLAGS=-Wall -Wextra -pedantic
TARGET=all

$(TARGET): minibusybox_Rafael.c common.h common.c sleep.h sleep.c rm.c rm.h touch.h touch.c chmod.h chmod.c
	$(CC) $(CFLAGS) -o m minibusybox_Rafael.c common.c sleep.c rm.c cat.c touch.c chmod.c;
	ln -s m sleep;ln -s m cat;ln -s m touch;ln -s m chmod;ln -s m rm
com: minibusybox_Rafael.c common.h common.c sleep.h sleep.c rm.c rm.h touch.h touch.c chmod.h chmod.c cat.c cat.h
	$(CC) $(CFLAGS) -o m minibusybox_Rafael.c common.c sleep.c rm.c cat.c touch.c chmod.c;
	ln -s m sleep;ln -s m cat;ln -s m touch;ln -s m chmod;ln -s m rm
link:
	ln -s m sleep;ln -s m cat;ln -s m touch;ln -s m chmod;ln -s m rm
main: main.c
	$(CC) $(CFLAGS) -o $@ main.c
clean:
	rm sleep touch chmod cat rm m;


