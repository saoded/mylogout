# Define required macros here
#cc `pkg-config --cflags gtk+-3.0` mylogout.c -o mylogout `pkg-config --libs gtk+-3.0`
SHELL = /bin/sh

OBJS =  mylogout.o
CFLAG = `pkg-config --cflags gtk+-3.0`
CC = cc
INCLUDE = mylogout.c
LIBS =`pkg-config --libs gtk+-3.0`

mylogout:${OBJ}
   ${CC} ${CFLAGS} ${INCLUDES} -o $@ ${OBJS} ${LIBS}

clean:
   -rm -f *.o core *.core

.cpp.o:
   ${CC} ${CFLAGS} ${INCLUDES} -c $<
