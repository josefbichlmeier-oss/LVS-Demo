#ifndef D621_ANWENDUNG_H
#define D621_ANWENDUNG_H

/* Einmalige Initialisierung: Terminal, Bildschirm, Tastatur und
 * Demodaten. Auf dem ESP32 in setup() aufzurufen. */
void anwendung_init(void);

/* Fuehrt eine Sitzung aus: Startbildschirm -> Anmeldung ->
 * Hauptmenue-Schleife, bis sich der Benutzer abmeldet oder die
 * Anmeldung abgebrochen wird. Kehrt danach zurueck - der Aufrufer
 * entscheidet, was als naechstes passiert (z.B. erneut aufrufen,
 * um zum Startbildschirm zurueckzukehren). Auf dem ESP32 in
 * loop() aufzurufen. */
void anwendung_sitzung(void);

/* Bequemlichkeitsfunktion fuer den Linux-Debug-Build:
 * anwendung_init() + eine einzelne anwendung_sitzung(). Entspricht
 * dem einmaligen Lauf des Ruby-Originals (main.rb). */
void anwendung_start(void);

#endif
