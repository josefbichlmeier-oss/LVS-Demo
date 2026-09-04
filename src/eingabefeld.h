/*
 * D621-LVS
 *
 * Eingabefeld - entspricht system/eingabefeld.rb.
 *
 * Anders als eingabe_zeile() loescht dieses Feld zunaechst den
 * Anzeigebereich, rendert bei jedem Tastendruck das komplette
 * (linksbuendig aufgefuellte) Feld neu und bewegt den Cursor auch
 * im Passwortmodus logisch mit (ohne ihn dort tatsaechlich sichtbar
 * zu verschieben, da im Original in diesem Modus kein
 * Bildschirm-ausgeben() waehrend der Eingabe erfolgt). Wird aktuell
 * nur von der Anmeldemaske verwendet.
 */

#ifndef D621_EINGABEFELD_H
#define D621_EINGABEFELD_H

#include <stddef.h>

/* Rueckgabe: 0 = ok, -1 = mit ESC abgebrochen */
int eingabefeld_lesen(
    char *puffer,
    size_t puffer_groesse,
    int x,
    int y,
    int laenge
);

int eingabefeld_passwort(
    char *puffer,
    size_t puffer_groesse,
    int x,
    int y,
    int laenge
);

#endif
