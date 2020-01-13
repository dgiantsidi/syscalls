CC = gcc
FLAGS = -Wall -g
LDFLAGS = -lrt

.PHONY = all clean

all: clean

main-scone: main.c
	$(CC) $(FLAGS) -o $@ $< $(LDFLAGS)

main-native: main.c
	$(CC) $(FLAGS) -o $@ $< $(LDFLAGS)
clean:
	-rm -f main
