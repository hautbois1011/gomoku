CC = g++
CFLAGS = -Wall -std=c++14 -I/usr/local/include -I/usr/local/include/SDL2 -D_THREAD_SAFE
LDFLAGS = -L/usr/local/lib
LIBS = -lSDL2 -lSDL2_ttf -lSDL2_mixer
OBJS = main.o game.o board.o stone.o
PROGRAM = gomoku

all:	$(PROGRAM)

.SUFFIXES: .cpp .o

$(PROGRAM):	$(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(PROGRAM).out

.cpp.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *~ $(PROGRAM)
