CC = gcc

CFLAGS = -Wall -Wextra -std=c11

PROGRAM = d621-lvs

SOURCES = \
	src/main.c \
	src/hazeltine.c \
	src/bildschirm.c \
	src/artikel.c \
	src/kunde.c

$(PROGRAM): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(PROGRAM)

clean:
	rm -f $(PROGRAM)
