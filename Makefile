CC = gcc

CFLAGS = -Wall -Wextra -std=c11

PROGRAM = d621-lvs

SOURCES = \
	src/main.c \
	src/hazeltine.c \
	src/terminal.c \
	src/bildschirm.c \
	src/artikel.c \
	src/kunde.c \
	src/auftragsposition.c \
	src/auftrag.c \
	src/auftragsverwaltung.c \
	src/lagerbewegung.c \
	src/lagerbewegungsbestand.c \
	src/auftragsanzeige.c \
	src/demo.c 

$(PROGRAM): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(PROGRAM)

clean:
	rm -f $(PROGRAM)
