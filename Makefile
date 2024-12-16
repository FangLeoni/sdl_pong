CC = gcc
CFLAGS = -Wall -std=c11
CFLAGS = -lSDL2 -lSDL2_ttf


SRC  = $(wildcard src/**/*.c) $(wildcard src/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c)
OBJ  = $(SRC:.c=.o)

build: $(OBJ)
	$(CC) -o game $^ $(CFLAGS)
run:
	./game
clean: $(OBJ)
	rm game $^