CFLAGS=-g

all: dgenmen

dgenmen: rom.o
	${CC} -o dgenmen ${CFLAGS} ${LDFLAGS} rom.o dgenmen.c

rom.o: rom.h rom.c
	${CC} -c ${CFLAGS} -o rom.o rom.c
