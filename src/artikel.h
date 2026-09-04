#ifndef D621_ARTIKEL_H
#define D621_ARTIKEL_H

#define MAX_ARTIKEL 100

typedef struct
{
    char nummer[16];
    char bezeichnung[64];
    int  bestand;
    char lagerplatz[16];
} Artikel;


void artikelbestand_initialisieren(void);

Artikel *artikel_anlegen(
    const char *nummer,
    const char *bezeichnung,
    int bestand,
    const char *lagerplatz
);

Artikel *artikel_finden(
    const char *nummer
);

int artikel_anzahl(void);

Artikel *artikel_at(
    int index
);

#endif
