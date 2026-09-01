#ifndef D621_ARTIKEL_H
#define D621_ARTIKEL_H

#define MAX_ARTIKEL 100

typedef struct
{
    char nummer[16];
    char bezeichnung[64];
    int bestand;
} Artikel;


void artikelbestand_initialisieren(void);

Artikel *artikel_anlegen(
    const char *nummer,
    const char *bezeichnung,
    int bestand
);

Artikel *artikel_finden(
    const char *nummer
);

#endif
