all: dgm_rampad

dgm_rampad: dgm_rampad.c
	${CC} ${CFLAGS} ${CPPFLAGS} -o $@ ../dgm_romlib/dgm_romlib.o $@.c

.PHONY: clean
clean:
	-rm dgm_rampad
