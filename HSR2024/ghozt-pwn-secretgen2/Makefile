CC=gcc

CFLAGS=
LDFLAGS=
SRC=chall.c
OBJ=$(SRC:.c=.o)
BIN=data/chall

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
	rm -f $(BIN) $(OBJ)        
