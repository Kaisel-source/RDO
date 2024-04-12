CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I/usr/include/SDL2 -Iinclude
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2main

SRCDIR = src
INCDIR = include
BUILDDIR = build
TARGET = mon_programme

SRCS = $(wildcard $(SRCDIR)/**/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)/*.o $(TARGET)
