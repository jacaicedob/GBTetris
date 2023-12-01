CC	= /opt/gbdk/bin/lcc
# CFLAGS = -Wa-l -Wl-m -Wl-j --debug
CFLAGS = -Wa-l -Wl-m -Wl-j 

BINS	= ../build/tetris.gb

all:	$(BINS)

# Compile and link single file in one pass
../build/tetris.gb:	main.c
	$(CC) $(CFLAGS) -c -o ../build/main.o main.c
	$(CC) $(CFLAGS) -o ../build/tetris.gb ../build/main.o

clean:
	rm -f ../build/*
#	rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm *.noi