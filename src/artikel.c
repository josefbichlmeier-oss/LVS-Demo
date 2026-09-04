#include <stddef.h>
#include <string.h>

#include "artikel.h"


static Artikel artikelbestand[MAX_ARTIKEL];

static int artikel_anzahl_wert = 0;


void artikelbestand_initialisieren(void)
{
    artikel_anzahl_wert = 0;

    artikel_anlegen("1001", "SCHRAUBE M6X20",       250, "A-01-01");
    artikel_anlegen("1002", "MUTTER M6",             180, "A-01-04");
    artikel_anlegen("1003", "UNTERLEGSCHEIBE M6",    420, "A-01-05");
    artikel_anlegen("1004", "STAHLBLECH 1MM",         10, "C-02-04");
    artikel_anlegen("1005", "STAHLWINKEL 30X30",      42, "C-01-03");
}


Artikel *artikel_anlegen(
    const char *nummer,
    const char *bezeichnung,
    int bestand,
    const char *lagerplatz
)
{
    if (artikel_anzahl_wert >= MAX_ARTIKEL)
        return NULL;


    Artikel *artikel =
        &artikelbestand[artikel_anzahl_wert];


    strncpy(artikel->nummer, nummer, sizeof(artikel->nummer) - 1);
    artikel->nummer[sizeof(artikel->nummer) - 1] = '\0';

    strncpy(artikel->bezeichnung, bezeichnung, sizeof(artikel->bezeichnung) - 1);
    artikel->bezeichnung[sizeof(artikel->bezeichnung) - 1] = '\0';

    strncpy(artikel->lagerplatz, lagerplatz, sizeof(artikel->lagerplatz) - 1);
    artikel->lagerplatz[sizeof(artikel->lagerplatz) - 1] = '\0';

    artikel->bestand = bestand;

    artikel_anzahl_wert++;

    return artikel;
}


Artikel *artikel_finden(
    const char *nummer
)
{
    for (int i = 0; i < artikel_anzahl_wert; i++)
    {
        if (strcmp(artikelbestand[i].nummer, nummer) == 0)
        {
            return &artikelbestand[i];
        }
    }

    return NULL;
}


int artikel_anzahl(void)
{
    return artikel_anzahl_wert;
}


Artikel *artikel_at(
    int index
)
{
    if (index < 0 || index >= artikel_anzahl_wert)
        return NULL;

    return &artikelbestand[index];
}
