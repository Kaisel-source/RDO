# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lSDL2 -lSDL2_image -lm

# Dossiers
SRCDIR = src
BINDIR = bin

# Fichiers sources
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(BINDIR)/%.o)

# Exécutable
EXEC = $(BINDIR)/mon_programme

# Règles
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean
