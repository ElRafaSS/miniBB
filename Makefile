CROSS_COMPILE =
CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Werror
TARGET = minibusybox
MKDIR_PATH =libCat
LIBS = -lcat
MAIN = minibusybox.c

.PHONY: all install clean
all: $(TARGET)

$(TARGET): main.o libcat.so
	$(CC) $(CFLAGS) $< $(LIBS) -L. -o $@
	ln -s $@ cat;
main.o: $(MAIN)
	$(CC) $(CFLAGS) -c $< -o $@
libcat.so: $(MKDIR_PATH)/cat.c $(MKDIR_PATH)/cat.h
	$(CC) $(CFLAGS) -c -fpic $< -o cat.o
	$(CC) -shared -o $@ cat.o
install: libcat.so
	sudo cp $< /usr/lib
	sudo cp $(MKDIR_PATH)/cat.h /usr/include
clean:
	rm *.o *.so $(TARGET) cat


