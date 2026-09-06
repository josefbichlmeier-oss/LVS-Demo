/*
 * D621-LVS
 *
 * Kleiner, wiederverwendbarer Helfer fuer seitenweises Blaettern
 * durch Listen (Lagerbestand, Artikelstamm, Artikelsuche,
 * Kundenuebersicht, Auftragsuebersicht, Lagerbewegungen), die
 * mehr Eintraege haben koennten, als auf einen Bildschirm passen.
 */

#ifndef D621_PAGINIERUNG_H
#define D621_PAGINIERUNG_H

#include <stddef.h>

typedef struct
{
    int seite;             /* aktuelle Seite, 0-basiert */
    int zeilen_pro_seite;
    int gesamt_anzahl;

} Paginierung;

int paginierung_seiten_anzahl(const Paginierung *p);

/* Erster Index (einschliesslich) der aktuellen Seite */
int paginierung_start_index(const Paginierung *p);

/* Letzter Index (ausschliesslich) der aktuellen Seite */
int paginierung_ende_index(const Paginierung *p);

void paginierung_naechste(Paginierung *p);
void paginierung_vorherige(Paginierung *p);

/* Schreibt z.B. "SEITE 2/3  (+/- BLAETTERN)" nach puffer, oder
 * einen leeren String, wenn ohnehin alles auf eine Seite passt. */
void paginierung_hinweis(char *puffer, size_t groesse, const Paginierung *p);

#endif
