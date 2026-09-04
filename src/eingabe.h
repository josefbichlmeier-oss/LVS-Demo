/*
 * D621-LVS
 *
 * Eingabeverarbeitung - entspricht system/eingabe.rb.
 *
 * Alle Funktionen sind blockierend (wie im Original) und arbeiten
 * plattformunabhaengig ueber die Tastatur-Schnittstelle (tastatur.h).
 */

#ifndef D621_EINGABE_H
#define D621_EINGABE_H

#include <stddef.h>

void eingabe_init(void);

/* Rohes Einzelzeichen lesen (drei gleichbedeutende Namen, wie im
 * Original in verschiedenen Masken verwendet: taste/warten/lesen) */
char eingabe_taste(void);
char eingabe_warten(void);
char eingabe_lesen(void);

/*
 * Liest eine Zeile mit Bildschirmecho an Position (x,y), bis max.
 * max_laenge Zeichen, mit Backspace-Unterstuetzung. Eingaben werden
 * wie im Original in Grossbuchstaben umgewandelt.
 *
 * Rueckgabe: 0 = ok (puffer enthaelt den eingegebenen Text),
 *           -1 = mit ESC abgebrochen (puffer ist leer).
 */
int eingabe_zeile(
    char *puffer,
    size_t puffer_groesse,
    int max_laenge,
    int x,
    int y
);

/*
 * Wie eingabe_zeile, aber ohne jegliche Bildschirmausgabe
 * (Kennworteingabe).
 */
int eingabe_passwort(
    char *puffer,
    size_t puffer_groesse,
    int max_laenge
);

#endif
