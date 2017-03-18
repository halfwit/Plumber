# plumber - plan9 inspired utility to action arbitrary strings
# See LICENSE file for copyright and license details.

PREFIX ?= /usr/local

SRC = \
	plumber \
	browse \
	edit \
	play \

install:
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f ${SRC} ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/${SRC}
	@mkdir -p ${DESTDIR}${PREFIX}/etc/plumber
	@cp -f cfg/plumber/* ${DESTDIR}${PREFIX}/etc/plumber/

.PHONY: install
