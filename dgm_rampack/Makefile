all: dgm_rampack

dgm_rampack: dgm_rampack.c
	${CC} ${CFLAGS} ${CPPFLAGS} -o $@ $@.c

.PHONY: clean
clean:
	-rm dgm_rampack
