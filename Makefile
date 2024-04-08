CC=gcc
CFLAGS=-Wall -Wextra -std=c99
LDFLAGS=

SRCS=$(wildcard src/*/*.c)
OBJS=$(SRCS:.c=.o)
EXE=my_program
TEST=my_test
all: $(EXE)
test: $(TEST)
$(EXE): $(filter-out src/item-inventory/test.o, $(OBJS))
	$(CC) $(LDFLAGS) -o $@ $^
$(TEST): $(filter-out src/item-inventory/main.o, $(OBJS))
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXE) $(OBJS)

.PHONY: all clean

