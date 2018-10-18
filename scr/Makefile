AR=ar
CFLAGS=-g -Wall -W -I/usr/include/SDL
LDFLAGS=
SRC=packet.c sender.c receiver.c
OBJ=$(SRC:.c=.o)
LIBFILE=src.a

all: $(SRC) $(LIBFILE)

$(LIBFILE): $(OBJ)
	ar r $@ $(OBJ)

*.o:
	gcc -o $@ -c $< $(CFLAGS)

clean: scr.a packet.o sender.o receiver.o
	rm scr.a packet.o sender.o receiver.o