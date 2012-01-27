CFLAGS=-g

all: dgm_hdump

dgm_hdump: rom.o
	${CC} -o $@ ${CFLAGS} ${LDFLAGS} rom.o $@.c

rom.o: rom.h rom.c
	${CC} -c ${CFLAGS} -o rom.o rom.c

.PHONY: clean
clean:
	-rm *.o dgm_hdump
