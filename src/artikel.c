#include <string.h>

#include "artikel.h"


static Artikel artikelbestand[MAX_ARTIKEL];

static int artikel_anzahl = 0;


void artikelbestand_initialisieren(void)
{
    artikel_anzahl = 0;
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
