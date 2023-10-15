CC=clang
CFLAGS=

UTILSSRC = utils.c

all: ping pong

ping:
	$(CC) $(CFLAGS) ping.c $(UTILSSRC) -o ping -lm
	strip ping

pong:
	$(CC) $(CFLAGS) pong.c  $(UTILSSRC) -o pong -lm
	strip pong

clean:
	rm ping pong