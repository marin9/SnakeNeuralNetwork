CC=gcc
CFLAGS=-Wall -Wextra -O2
LDFLAGS=-lSDL2
TARGET=snake

SRC=$(wildcard *.c)
INC=$(wildcard *.h)
OBJ=$(SRC:.c=.o)


$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o : %.c $(INC)
	$(CC) $(CFLAGS) -c -o $@ $< 

clean:
	rm -f $(TARGET)
	rm -f *.o
