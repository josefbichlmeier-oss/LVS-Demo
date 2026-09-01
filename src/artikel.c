#include <stddef.h>
#include <string.h>

#include "artikel.h"


static Artikel artikelbestand[MAX_ARTIKEL];

static int artikel_anzahl = 0;


void artikelbestand_initialisieren(void)
{
    artikel_anzahl = 0;

    artikel_anlegen(
        "1001",
        "SCHRAUBE M6X20",
        250
    );

    artikel_anlegen(
        "1002",
        "MUTTER M6",
        180
    );

    artikel_anlegen(
        "1003",
        "UNTERLEGSCHEIBE M6",
        500
    );
}


Artikel *artikel_anlegen(
    const char *nummer,
    const char *bezeichnung,
    int bestand
)
{
    if (artikel_anzahl >= MAX_ARTIKEL)
        return NULL;


    Artikel *artikel =
        &artikelbestand[artikel_anzahl];


    strncpy(
        artikel->nummer,
        nummer,
        sizeof(artikel->nummer) - 1
    );

    artikel->nummer[
        sizeof(artikel->nummer) - 1
    ] = '\0';


    strncpy(
        artikel->bezeichnung,
        bezeichnung,
        sizeof(artikel->bezeichnung) - 1
    );

    artikel->bezeichnung[
        sizeof(artikel->bezeichnung) - 1
    ] = '\0';


    artikel->bestand = bestand;

    artikel_anzahl++;

    return artikel;
}


Artikel *artikel_finden(
    const char *nummer
)
{
    for (int i = 0; i < artikel_anzahl; i++)
    {
        if (strcmp(
                artikelbestand[i].nummer,
                nummer
            ) == 0)
        {
            return &artikelbestand[i];
        }
    }

    return NULL;
}
