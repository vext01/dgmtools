all: dgm_romlib.o

dgm_romlib.o: dgm_romlib.c dgm_romlib.h
	${CC} ${CPPFLAGS} ${CFLAGS} -c dgm_romlib.c -o $@

.PHONY: clean
clean:
	rm -f dgm_romlib.o
