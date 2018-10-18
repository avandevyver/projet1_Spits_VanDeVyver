CFLAGS += -std=c99
CFLAGS += -Wall
CFLAGS += -Werror
CFLAGS += -Wshadow
CFLAGS += -Wextra
CFLAGS += -O2 -D_FORTIFY_SOURCE=2
CFLAGS += -fstack-protector-all
CFLAGS += -D_POSIX_C_SOURCE=201112L -D_XOPEN_SOURCE

LDFLAGS= -rdynamic

all: clean pkt

debug: CFLAGS += -g -DDEBUG -Wno-unused-parameter -fno-omit-frame-pointer
debug: clean pkt

pkt: packet.o sender.o receiver.o

.PHONY: clean

clean:
	@rm -f pkt packet.o sender.o receiver.o