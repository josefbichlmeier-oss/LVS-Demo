#include <ctype.h>
#include <string.h>

#include "eingabefeld.h"
#include "eingabe.h"
#include "bildschirm.h"

#include "../config/config.h"


static int lesen_intern(
    char *puffer,
    size_t puffer_groesse,
    int x,
    int y,
    int laenge,
    int anzeigen
)
{
    int wlen = 0;
    char blank[D621_BREITE + 1];

    if (laenge > D621_BREITE)
        laenge = D621_BREITE;

    puffer[0] = '\0';

    memset(blank, ' ', (size_t)laenge);
    blank[laenge] = '\0';

    bildschirm_schreiben(x, y, blank);
    bildschirm_ausgeben();
    bildschirm_cursor(x, y);

    for (;;)
    {
        char taste = eingabe_lesen();

        if (taste == '\r' || taste == '\n')
        {
            return 0;
        }

        if (taste == '\033')
        {
            puffer[0] = '\0';
            return -1;
        }

        if (taste == '\b' || taste == 0x7F)
        {
            if (wlen > 0)
            {
                wlen--;
                puffer[wlen] = '\0';
            }
        }
        else if (wlen < laenge &&
                 (size_t)(wlen + 1) < puffer_groesse)
        {
            puffer[wlen] = (char)toupper((unsigned char)taste);
            wlen++;
            puffer[wlen] = '\0';
        }

        if (anzeigen)
        {
            char zeile[D621_BREITE + 1];
            int i = 0;

            for (; i < wlen; i++)
                zeile[i] = puffer[i];

            for (; i < laenge; i++)
                zeile[i] = ' ';

            zeile[laenge] = '\0';

            bildschirm_schreiben(x, y, zeile);
            bildschirm_ausgeben();
        }

        bildschirm_cursor(x + wlen, y);
    }
}


int eingabefeld_lesen(
    char *puffer,
    size_t puffer_groesse,
    int x,
    int y,
    int laenge
)
{
    return lesen_intern(puffer, puffer_groesse, x, y, laenge, 1);
}


int eingabefeld_passwort(
    char *puffer,
    size_t puffer_groesse,
    int x,
    int y,
    int laenge
)
{
    return lesen_intern(puffer, puffer_groesse, x, y, laenge, 0);
}
