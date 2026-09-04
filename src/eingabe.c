#include <ctype.h>

#include "eingabe.h"
#include "tastatur.h"
#include "bildschirm.h"


void eingabe_init(void)
{
    tastatur_init();
}


char eingabe_taste(void)  { return tastatur_lesen(); }
char eingabe_warten(void) { return tastatur_lesen(); }
char eingabe_lesen(void)  { return tastatur_lesen(); }


int eingabe_zeile(
    char *puffer,
    size_t puffer_groesse,
    int max_laenge,
    int x,
    int y
)
{
    int laenge = 0;

    puffer[0] = '\0';

    bildschirm_hell();
    bildschirm_cursor(x, y);

    for (;;)
    {
        char taste = eingabe_taste();

        if (taste == '\r' || taste == '\n')
        {
            bildschirm_dunkel();
            break;
        }

        if (taste == '\033')
        {
            bildschirm_dunkel();
            puffer[0] = '\0';
            return -1;
        }

        if (taste == '\b' || taste == 0x7F)
        {
            if (laenge > 0)
            {
                laenge--;
                puffer[laenge] = '\0';

                bildschirm_schreiben(x + laenge, y, " ");
                bildschirm_ausgeben();
                bildschirm_cursor(x + laenge, y);
            }

            continue;
        }

        if (laenge < max_laenge &&
            (size_t)(laenge + 1) < puffer_groesse)
        {
            char zeichen = (char)toupper((unsigned char)taste);
            char einzel[2];

            puffer[laenge] = zeichen;
            laenge++;
            puffer[laenge] = '\0';

            einzel[0] = zeichen;
            einzel[1] = '\0';

            bildschirm_schreiben(x + laenge - 1, y, einzel);
            bildschirm_ausgeben();
        }
    }

    return 0;
}


int eingabe_passwort(
    char *puffer,
    size_t puffer_groesse,
    int max_laenge
)
{
    int laenge = 0;

    puffer[0] = '\0';

    for (;;)
    {
        char taste = eingabe_taste();

        if (taste == '\r' || taste == '\n')
        {
            break;
        }

        if (taste == '\033')
        {
            puffer[0] = '\0';
            return -1;
        }

        if (taste == '\b' || taste == 0x7F)
        {
            if (laenge > 0)
            {
                laenge--;
                puffer[laenge] = '\0';
            }

            continue;
        }

        if (laenge < max_laenge &&
            (size_t)(laenge + 1) < puffer_groesse)
        {
            puffer[laenge] = (char)toupper((unsigned char)taste);
            laenge++;
            puffer[laenge] = '\0';
        }
    }

    return 0;
}
