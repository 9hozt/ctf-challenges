CC=gcc

CFLAGS= -fno-stack-protector 
SRC=chall.c
OBJ=$(SRC:.c=.o)
BIN=data/chall

all:
	$(MAKE) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

.o:
	$(CC) $(CFLAGS) $< -o $@

challenge: all
	rm -f $(OBJ)

clean:
	rm -f $(BIN) $(OBJ)

