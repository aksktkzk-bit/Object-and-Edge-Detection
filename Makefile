CC = gcc
CFLAGS = -O2 -Wall -Iinclude
LDFLAGS = -lm

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

TARGET = ppmproc.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q src\*.o 2>nul
	del /Q $(TARGET) 2>nul
