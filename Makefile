.PHONY: all
all:
	cd dgm_hdump && ${MAKE}
	cd dgm_rampad && ${MAKE}
	cd dgm_romlib && ${MAKE}

.PHONY: clean
clean:
	cd dgm_hdump && ${MAKE} clean
	cd dgm_rampad && ${MAKE} clean
	cd dgm_romlib && ${MAKE} clean


