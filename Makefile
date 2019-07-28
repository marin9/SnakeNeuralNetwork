CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS=-lSDL2
TARGET=prog

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
