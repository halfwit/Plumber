# plumber - plan9 inspired utility to action arbitrary strings
# See LICENSE file for copyright and license details.

PREFIX ?= /usr/local

install:
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f notes ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/notes
	@mkdir -p ${DESTDIR}${PREFIX}/share/notes
	@cp -f new ${DESTDIR}${PREFIX}/share/notes/new

.PHONY: install
