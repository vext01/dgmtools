.PHONY: all
all:
	cd dgm_hdump && ${MAKE}
	cd dgm_rampad && ${MAKE}

.PHONY: clean
clean:
	cd dgm_hdump && ${MAKE} clean
	cd dgm_rampad && ${MAKE} clean


