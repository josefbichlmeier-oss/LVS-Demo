#include <string.h>

#include "maske_anmeldung.h"
#include "bildschirm.h"
#include "eingabe.h"
#include "eingabefeld.h"


typedef struct
{
    const char *benutzer;
    const char *kennwort;
} Benutzerkonto;


static const Benutzerkonto benutzer_liste[] =
{
    { "SCHMIDT", "123"  },
    { "DEMO",    "DEMO" },
    { "JOBI",    "X"    }
};

#define BENUTZER_ANZAHL \
    (int)(sizeof(benutzer_liste) / sizeof(benutzer_liste[0]))


static int benutzer_pruefen(const char *benutzer, const char *kennwort)
{
    for (int i = 0; i < BENUTZER_ANZAHL; i++)
    {
        if (strcmp(benutzer, benutzer_liste[i].benutzer) == 0 &&
            strcmp(kennwort, benutzer_liste[i].kennwort) == 0)
        {
            return 1;
        }
    }

    return 0;
}


Ergebnis maske_anmeldung_anzeigen(void)
{
    char benutzer[21];
    char kennwort[21];

    for (;;)
    {
        bildschirm_loeschen();
        bildschirm_titel("SYSTEMANMELDUNG");
        bildschirm_schreiben(5, 8, "BENUTZER :");
        bildschirm_schreiben(5, 10, "KENNWORT :");
        bildschirm_ausgeben();

        eingabefeld_lesen(benutzer, sizeof(benutzer), 17, 8, 20);
        eingabefeld_passwort(kennwort, sizeof(kennwort), 17, 10, 20);

        if (benutzer_pruefen(benutzer, kennwort))
        {
            return ERG_ANGEMELDET;
        }

        bildschirm_schreiben(56, 26, "FALSCHE ANMELDUNG");
        bildschirm_schreiben(2, 26, "NOCH EIN VERSUCH MIT CR");
        bildschirm_ausgeben();

        eingabe_warten();
    }
}
