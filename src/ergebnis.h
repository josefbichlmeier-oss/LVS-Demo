/*
 * D621-LVS
 *
 * Gemeinsame Ergebnis-/Navigationscodes.
 *
 * In Ruby wurden lose Symbole (:zurueck, :ok, :esc, ...) zur
 * Ablaufsteuerung zwischen Masken und Anwendung.rb verwendet. In C
 * bilden wir das mit einem einzigen, zentralen enum nach - jede
 * Maske liefert einen dieser Werte zurueck, anwendung.c wertet sie
 * per switch() aus. Nicht jede Maske nutzt jeden Wert.
 */

#ifndef D621_ERGEBNIS_H
#define D621_ERGEBNIS_H

typedef enum
{
    ERG_NICHTS = 0,

    /* Navigation */
    ERG_WEITER,
    ERG_ZURUECK,
    ERG_ESC,
    ERG_ENDE,

    /* Anmeldung */
    ERG_ANGEMELDET,

    /* Hauptmenue */
    ERG_LAGER,
    ERG_ARTIKEL,
    ERG_KUNDE,
    ERG_AUFTRAG,
    ERG_DATUMZEIT,

    /* Lagermenue */
    ERG_BESTAND,
    ERG_SUCHE,
    ERG_WARENEINGANG,
    ERG_WARENAUSGANG,
    ERG_BEWEGUNGEN,

    /* Auftragsmenue */
    ERG_NEU,
    ERG_ANZEIGEN,
    ERG_AUSLIEFERN,

    /* Buchungs-/Ausliefer-Ergebnisse */
    ERG_OK,
    ERG_NICHT_GEFUNDEN,
    ERG_BESTAND_UNZUREICHEND,
    ERG_BEREITS_AUSGELIEFERT,
    ERG_ARTIKEL_NICHT_GEFUNDEN

} Ergebnis;

#endif
