# Author: David Malášek

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC    = src/main.c src/file.c src/functions.c src/utils.c
OBJ    = $(patsubst src/%.c, build/%.o, $(SRC))
TARGET = a.out

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)
