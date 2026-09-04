#include <ctype.h>
#include <stdio.h>

#include "maske_auftragsanzeige.h"
#include "bildschirm.h"
#include "eingabe.h"
#include "kunde.h"
#include "artikel.h"


Ergebnis maske_auftragsanzeige_anzeigen(const Auftrag *auftrag)
{
    char titel[32];
    char plz_ort[48];
    char zeile[140];
    char anzahl_puffer[8];

    Kunde *kunde = kunde_finden(auftrag->kundennummer);

    bildschirm_loeschen();

    snprintf(titel, sizeof(titel), "AUFTRAG %d", auftrag->nummer);
    bildschirm_titel(titel);

    bildschirm_schreiben(2, 3, "KUNDE:");

    if (kunde)
    {
        bildschirm_feld(15, 3, kunde->nummer);
        bildschirm_feld(15, 4, kunde->name);
        bildschirm_feld(15, 5, kunde->strasse);

        snprintf(plz_ort, sizeof(plz_ort), "%s %s", kunde->plz, kunde->ort);
        bildschirm_feld(15, 6, plz_ort);
    }
    else
    {
        bildschirm_feld(15, 3, "UNBEKANNT");
    }

    bildschirm_schreiben(2, 8, "STATUS:");
    bildschirm_feld(15, 8, auftrag_status_text(auftrag->status));

    bildschirm_schreiben(2, 11, "POS ART      BEZEICHNUNG                     MENGE");
    bildschirm_schreiben(2, 12, "------------------------------------------------------------");

    int y = 13;

    for (int i = 0; i < auftrag->positionen_anzahl; i++)
    {
        const Auftragsposition *position = &auftrag->positionen[i];
        Artikel *artikel = artikel_finden(position->artikelnummer);

        const char *nummer = artikel ? artikel->nummer : position->artikelnummer;
        const char *bezeichnung = artikel ? artikel->bezeichnung : "?";

        snprintf(
            zeile, sizeof(zeile),
            "%3d %-8s %-28s %8d",
            i + 1,
            nummer,
            bezeichnung,
            position->menge
        );

        bildschirm_feld(2, y, zeile);
        y++;
    }

    bildschirm_schreiben(2, 9, "POSITIONEN:");

    snprintf(anzahl_puffer, sizeof(anzahl_puffer), "%d", auftrag->positionen_anzahl);
    bildschirm_feld(15, 9, anzahl_puffer);

    if (auftrag->status != AUFTRAG_ABGESCHLOSSEN)
    {
        bildschirm_schreiben(10, 24, "A  AUSLIEFERN");
    }

    bildschirm_aktion("X  ZURUECK");
    bildschirm_ausgeben();

    for (;;)
    {
        char taste = (char)toupper((unsigned char)eingabe_taste());

        if (taste == 'A')
        {
            return ERG_AUSLIEFERN;
        }

        if (taste == 'X')
        {
            return ERG_ZURUECK;
        }
    }
}
