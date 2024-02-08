CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = $(wildcard src/*/*.c)
OBJ = $(SRC:.c=.o)
EXECUTABLE = mon_programme

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

clear : clean
	rm -f $(EXECUTABLE)
