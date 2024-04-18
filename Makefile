CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -L/usr/include/SDL2 -lSDL2 -lSDL2_image -lSDL2main -lSDL2_ttf -lm

SRCDIR = src
BUILDDIR = build
TARGET = my_program
TEST = my_test

SRCS = $(wildcard src/*/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))

all: $(TARGET)

test: $(TEST)

$(TARGET): $(filter-out $(BUILDDIR)/item-inventory/test.o, $(OBJS))
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST): $(filter-out $(BUILDDIR)/mouvement/main_mov.o, $(OBJS))
	$(CC) -g $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(TEST) $(OBJS)

.PHONY: all clean
