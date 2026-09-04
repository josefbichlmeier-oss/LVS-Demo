/*
 * D621-LVS
 *
 * Bildschirmspeicher mit Dirty-Tracking.
 *
 * Entspricht system/bildschirm.rb: Aenderungen werden zunaechst nur
 * in einem Puffer gesammelt und erst bei bildschirm_ausgeben() an
 * das Terminal geschickt. Das ist bei einer 9600-Baud-Verbindung
 * zu einem echten Hazeltine-Terminal wichtig - ein kompletter
 * Redraw bei jeder kleinen Aenderung waere spuerbar langsam und
 * wuerde sichtbar flackern.
 */

#ifndef D621_BILDSCHIRM_H
#define D621_BILDSCHIRM_H

void bildschirm_init(void);

/* Leert den Bildschirm sofort (loescht auch am Terminal, nicht
 * erst bei ausgeben()) */
void bildschirm_loeschen(void);

/* Text ohne Hervorhebung schreiben */
void bildschirm_schreiben(int x, int y, const char *text);

/* Text hervorgehoben (hell) schreiben - entspricht Terminal#feld
 * bzw. Bildschirm#feld in Ruby */
void bildschirm_feld(int x, int y, const char *text);

/* Zentrierter Titel in Zeile 0 + Uhrzeit rechts + Trennlinie in
 * Zeile 1 (entspricht Bildschirm#titel) */
void bildschirm_titel(const char *text);

/* Volle Trennlinie in Zeile y */
void bildschirm_linie(int y);

/* Statuszeile (letzte Zeile), hervorgehoben, links Text /
 * rechts Zustand (z.B. "BEREIT" oder "FEHLER") */
void bildschirm_status(const char *text, const char *zustand);

/* Kurzer Aktionshinweis in der letzten Zeile, Spalte 10,
 * linksbuendig auf 20 Zeichen aufgefuellt */
void bildschirm_aktion(const char *text);

/* Cursorposition merken - wird nach dem Senden aller Aenderungen
 * in bildschirm_ausgeben() angefahren */
void bildschirm_cursor(int x, int y);

void bildschirm_cursor_zurueck(void);

void bildschirm_hell(void);
void bildschirm_dunkel(void);

/* Sendet alle gesammelten Aenderungen ans Terminal und faehrt
 * anschliessend die zuletzt gesetzte Cursorposition an. */
void bildschirm_ausgeben(void);

#endif
