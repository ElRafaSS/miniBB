CROSS_COMPILE =
CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Werror
TARGET = minibusybox
MKDIR_PATH =libRm
LIBS = -lrm
MAIN = minibusybox.c

.PHONY: all install clean
all: $(TARGET)

$(TARGET): main.o librm.so
	$(CC) $(CFLAGS) $< $(LIBS) -L. -o $@
	ln -s $@ rm;
main.o: $(MAIN)
	$(CC) $(CFLAGS) -c $< -o $@
librm.so: $(MKDIR_PATH)/rm.c $(MKDIR_PATH)/rm.h
	$(CC) $(CFLAGS) -c -fpic $< -o rm.o
	$(CC) -shared -o $@ rm.o
install: librm.so
	sudo cp $< /usr/lib
	sudo cp $(MKDIR_PATH)/rm.h /usr/include
clean:
	rm *.o *.so $(TARGET) rm


