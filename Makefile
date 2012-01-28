PROGS=dgm_hdump dgm_rampad dgm_s3ramgen
CFLAGS+=-g

.PHONY: all
all: ${PROGS}

dgm_romlib.o: dgm_romlib.c dgm_romlib.h
	${CC} ${CFLAGS} ${CPPFLAGS} -c -o $@ dgm_romlib.c

dgm_hdump: dgm_hdump.c dgm_romlib.o
	${CC} ${CFLAGS} ${CPPFLAGS} -o $@ dgm_romlib.o $@.c

dgm_rampad: dgm_rampad.c dgm_romlib.o
	${CC} ${CFLAGS} ${CPPFLAGS} -o $@ dgm_romlib.o $@.c

dgm_s3ramgen: dgm_s3ramgen.c dgm_romlib.o
	${CC} ${CFLAGS} ${CPPFLAGS} -o $@ dgm_romlib.o $@.c

.PHONY: clean
clean:
	rm -f ${PROGS} dgm_romlib.o

