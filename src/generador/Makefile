TARGET = generador
CC = gcc
CFLAGS = -w

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
		$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
		$(CC) $(OBJECTS) -w -o $@

clean:
		-rm -f *.o
		-rm -f $(TARGET)