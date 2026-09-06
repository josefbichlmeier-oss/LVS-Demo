#include <stdio.h>
#include <stdlib.h>

#include "maske_auftragsuebersicht.h"
#include "bildschirm.h"
#include "eingabe.h"
#include "auftragsverwaltung.h"
#include "kunde.h"
#include "paginierung.h"

#define ZEILEN_PRO_SEITE 14


static void liste_zeichnen(const Paginierung *seiten)
{
    char zeile[140];
    char hinweis[40];
    int y = 5;

    bildschirm_loeschen();
    bildschirm_titel("AUFTRAGSUEBERSICHT");
    bildschirm_schreiben(2, 3, "NR       KUNDE                     STATUS");
    bildschirm_schreiben(2, 4, "------------------------------------------------------------");

    for (int i = paginierung_start_index(seiten); i < paginierung_ende_index(seiten); i++)
    {
        Auftrag *auftrag = auftrag_at(i);
        Kunde *kunde = kunde_finden(auftrag->kundennummer);

        const char *kundenname = kunde ? kunde->name : "UNBEKANNT";

        snprintf(
            zeile, sizeof(zeile),
            "%-8d %-25s %-15s",
            auftrag->nummer,
            kundenname,
            auftrag_status_text(auftrag->status)
        );

        bildschirm_feld(2, y, zeile);
        y++;
    }

    paginierung_hinweis(hinweis, sizeof(hinweis), seiten);
    bildschirm_schreiben(2, 20, hinweis);

    bildschirm_schreiben(5, 22, "AUFTRAGSNUMMER: ");
    bildschirm_aktion("ESC = ZURUECK");
    bildschirm_ausgeben();
}


Ergebnis maske_auftragsuebersicht_anzeigen(int *nummer_out)
{
    Paginierung seiten = { 0, ZEILEN_PRO_SEITE, auftrags_anzahl() };
    char nummer_puffer[16];

    for (;;)
    {
        liste_zeichnen(&seiten);

        char erste_taste = eingabe_taste();

        if (erste_taste == '+')
        {
            paginierung_naechste(&seiten);
            continue;
        }

        if (erste_taste == '-')
        {
            paginierung_vorherige(&seiten);
            continue;
        }

        if (erste_taste == '\033')
        {
            return ERG_ZURUECK;
        }

        if (eingabe_zeile_mit_erstem_zeichen(
                erste_taste, nummer_puffer, sizeof(nummer_puffer), 10, 21, 22) == -1)
        {
            return ERG_ZURUECK;
        }

        *nummer_out = atoi(nummer_puffer);

        return ERG_OK;
    }
}
