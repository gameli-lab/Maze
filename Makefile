CC = gcc
CFLAGS = -Iinc -I/usr/local/include/SDL2 -Wall -Werror -Wextra -pedantic
LDFLAGS = -lSDL2 -lm
SRC = src/ben.c src/ray.c src/func.c
OBJ = $(SRC:.c=.o)
EXEC = maze

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)
PHONY: clean
