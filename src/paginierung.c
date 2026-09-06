#include <stdio.h>

#include "paginierung.h"


int paginierung_seiten_anzahl(const Paginierung *p)
{
    if (p->gesamt_anzahl <= 0 || p->zeilen_pro_seite <= 0)
    {
        return 1;
    }

    return (p->gesamt_anzahl + p->zeilen_pro_seite - 1) / p->zeilen_pro_seite;
}


int paginierung_start_index(const Paginierung *p)
{
    return p->seite * p->zeilen_pro_seite;
}


int paginierung_ende_index(const Paginierung *p)
{
    int ende = paginierung_start_index(p) + p->zeilen_pro_seite;

    if (ende > p->gesamt_anzahl)
    {
        ende = p->gesamt_anzahl;
    }

    return ende;
}


void paginierung_naechste(Paginierung *p)
{
    int anzahl_seiten = paginierung_seiten_anzahl(p);

    if (p->seite < anzahl_seiten - 1)
    {
        p->seite++;
    }
}


void paginierung_vorherige(Paginierung *p)
{
    if (p->seite > 0)
    {
        p->seite--;
    }
}


void paginierung_hinweis(char *puffer, size_t groesse, const Paginierung *p)
{
    int anzahl_seiten = paginierung_seiten_anzahl(p);

    if (anzahl_seiten <= 1)
    {
        puffer[0] = '\0';
        return;
    }

    snprintf(
        puffer, groesse,
        "SEITE %d/%d  (+/- BLAETTERN)",
        p->seite + 1,
        anzahl_seiten
    );
}
