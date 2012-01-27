.PHONY: all
all:
	cd dgm_hdump && ${MAKE}
	cd dgm_rampack && ${MAKE}

.PHONY: clean
clean:
	cd dgm_hdump && ${MAKE} clean
	cd dgm_rampack && ${MAKE} clean


