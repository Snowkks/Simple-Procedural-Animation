CC = gcc

CFLAGS = -Wall -Wextra -std=c99 -g

LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC = procedural-animation.c
TARGET = procedural

all:
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LIBS)
	@echo "Build complete! Run with: ./$(TARGET)"

clean:
	rm -f $(TARGET)
