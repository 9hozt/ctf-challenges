CC=gcc

CFLAGS= -fno-stack-protector -O3
SRC=chall.c
OBJ=$(SRC:.c=.o)
BIN=chall

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