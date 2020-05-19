SRCS:=libvchan.c
DEPS:=$(SRCS:.c=.o)
BIN:=libvchan-kvm.so
LIBS=-lrt -pthread -lkvmchan
DEBUG:=true

CFLAGS:=-D_GNU_SOURCE=1 -O2 -Wall -Wextra -Wvla -fpic -fvisibility=hidden -std=gnu99 -I. \
	   -fstack-protector-strong -D_FORITY_SOURCE=2 $(shell pkg-config --cflags kvmchan) $(pkg-config --libs kvmchan)

PREFIX ?= /usr/local
LIBDIR ?= $(PREFIX)/lib
INCLUDEDIR ?= $(PREFIX)/include

ifneq ($(DEBUG),false)
CFLAGS += -g
endif

COMPILER_NAME:=$(shell $(CC) --version |cut -d' ' -f1 |head -n1)
ifneq ($(COMPILER_NAME),clang)
# This flag is GCC-only
CFLAGS += -fstack-clash-protection
endif

.PHONY all: library vchan-kvm.pc

library: $(DEPS)
	$(CC) -shared $(CFLAGS) $(DEPS) -o $(BIN) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

vchan-kvm.pc: vchan-kvm.pc.in
	sed -e "s/@VERSION@/`cat ../version`/" \
		-e "s:@PREFIX@:$(PREFIX):" \
		-e "s:@LIBDIR@:$(LIBDIR):" \
		-e "s:@INCLUDEDIR@:$(INCLUDEDIR):" \
		$< > $@

install: all
	install $(BIN) $(LIBDIR)/
	install libvchan.h $(INCLUDEDIR)/
	install vchan-kvm.pc $(LIBDIR)/pkgconfig/

clean:
	rm -f $(DEPS)
	rm -f $(BIN)
	rm -f vchan-kvm.pc

print-%  : ; @echo $* = $($*)
