# Makefile for compiling the shell and its commands

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Targets
TARGETS = myshell pwd cat head echo

all: $(TARGETS)

myshell: myshell.c
	$(CC) $(CFLAGS) -o myshell myshell.c

pwd: pwd.c
	$(CC) $(CFLAGS) -o pwd pwd.c

cat: cat.c
	$(CC) $(CFLAGS) -o cat cat.c

head: head.c
	$(CC) $(CFLAGS) -o head head.c

echo: echo.c
	$(CC) $(CFLAGS) -o echo echo.c

clean:
	rm -f $(TARGETS)
