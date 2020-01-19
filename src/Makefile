CC = g++
CFLAGS = -Wall -I/usr/local/include -I/usr/local/include/SDL2 -D_THREAD_SAFE
LDFLAGS = -L/usr/local/lib
LIBS = -lSDL2 -lSDL2_ttf -lSDL2_mixer
OBJS = main.o game.o board.o stone.o
PROGRAM = gomoku

all:	$(PROGRAM)

$(PROGRAM):	$(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(PROGRAM).out

clean:
	rm -f *.o *~ $(PROGRAM)
