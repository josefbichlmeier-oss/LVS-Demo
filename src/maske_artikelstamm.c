#include <ctype.h>
#include <stdio.h>

#include "maske_artikelstamm.h"
#include "bildschirm.h"
#include "eingabe.h"
#include "artikel.h"


Ergebnis maske_artikelstamm_anzeigen(void)
{
    char zeile[140];
    int y = 5;

    bildschirm_loeschen();
    bildschirm_titel("ARTIKELSTAMM");
    bildschirm_schreiben(2, 3, "NUMMER     BEZEICHNUNG");
    bildschirm_schreiben(2, 4, "------------------------------------------------------------");

    for (int i = 0; i < artikel_anzahl(); i++)
    {
        Artikel *artikel = artikel_at(i);

        snprintf(
            zeile, sizeof(zeile),
            "%-10s %-30s",
            artikel->nummer,
            artikel->bezeichnung
        );

        bildschirm_feld(2, y, zeile);
        y++;
    }

    bildschirm_aktion("X  ZURUECK  ");
    bildschirm_ausgeben();

    for (;;)
    {
        char taste = (char)toupper((unsigned char)eingabe_taste());

        if (taste == 'X')
        {
            return ERG_ZURUECK;
        }
    }
}
