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
 * Wie eingabe_zeile(), aber das erste Zeichen wurde bereits vorher
 * ausserhalb gelesen (z.B. um es auf eine Sonderbedeutung wie
 * Seitennavigation zu pruefen, bevor entschieden ist, dass es sich
 * um den Beginn einer normalen Eingabe handelt) und wird hier so
 * behandelt, als waere es soeben getippt worden (inkl. Echo).
 */
int eingabe_zeile_mit_erstem_zeichen(
    char erstes_zeichen,
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
