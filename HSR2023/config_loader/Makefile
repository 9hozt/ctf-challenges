CC=gcc

CFLAGS=
LDFLAGS=
SRC=confloader.c
OBJ=$(SRC:.c=.o)
BIN=bin/chall

.PHONY : clean

all:
	$(MAKE) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $@

.o:
	$(CC) $(CFLAGS) $< -o $@

challenge: all
	rm -f $(OBJ)

clean:
	rm -f $(BIN) $(OBJ)%         