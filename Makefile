#
# D621-LVS - Linux-Debug-Build
#
# Baut das Programm mit ANSI-Ausgabe auf der virtuellen Konsole.
# Fuer den ESP32/Hazeltine-Zielbetrieb siehe platformio.ini.
#

CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -Iconfig -Isrc

PROGRAM = d621-lvs

SOURCES = \
	src/main.c \
	src/anwendung.c \
	src/bildschirm.c \
	src/eingabe.c \
	src/eingabefeld.c \
	src/paginierung.c \
	src/systemzeit.c \
	src/monotonzeit_linux.c \
	src/terminal_linux.c \
	src/tastatur_linux.c \
	src/zeit_port_linux.c \
	src/artikel.c \
	src/kunde.c \
	src/auftrag.c \
	src/auftragsposition.c \
	src/auftragsverwaltung.c \
	src/lagerbewegung.c \
	src/lagerbewegungsbestand.c \
	src/demo.c \
	src/maske_start.c \
	src/maske_anmeldung.c \
	src/maske_hauptmenue.c \
	src/maske_lager.c \
	src/maske_lagerbestand.c \
	src/maske_lagerbewegungen.c \
	src/maske_artikelstamm.c \
	src/maske_artikelsuche.c \
	src/maske_artikelanzeige.c \
	src/maske_wareneingang.c \
	src/maske_warenausgang.c \
	src/maske_auftragsmenue.c \
	src/maske_auftragsuebersicht.c \
	src/maske_auftragsanzeige.c \
	src/maske_neuerauftrag.c \
	src/maske_kundenmenue.c \
	src/maske_kundenuebersicht.c \
	src/maske_kundenanzeige.c \
	src/maske_datumzeit.c \
	src/maske_fehlermeldung.c \
	src/maske_meldung.c

$(PROGRAM): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(PROGRAM)

clean:
	rm -f $(PROGRAM)

.PHONY: clean
