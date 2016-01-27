BIN = ../saf
INC = common.h box.h iff.h path.h

DEBUG = -g3 -Wall -pedantic

CFLAGS +=$(DEBUG)

$(BIN) : $(INC) main.c box.o iff.o path.o
	$(CC) $(CFLAGS) main.c box.o iff.o path.o -o $(BIN)

clean:
	$(RM) *.o $(BIN)
