#ifndef D621_AUFTRAG_H
#define D621_AUFTRAG_H

#include "auftragsposition.h"

#define MAX_POSITIONEN 20

typedef enum
{
    AUFTRAG_NEU,
    AUFTRAG_BEARBEITET,
    AUFTRAG_ABGESCHLOSSEN

} Auftragsstatus;


typedef struct
{
    int nummer;
    char kundennummer[16];

    Auftragsstatus status;

    Auftragsposition positionen[MAX_POSITIONEN];
    int positionen_anzahl;

} Auftrag;


void auftrag_initialisieren(
    Auftrag *auftrag,
    int nummer,
    const char *kundennummer
);

int auftrag_position_hinzufuegen(
    Auftrag *auftrag,
    const char *artikelnummer,
    int menge
);

/*
 * Prueft und bebucht den kompletten Auftrag (entspricht der
 * Ruby-Klasse Auslieferung). Rueckgabewerte:
 *
 *   0  Auftrag erfolgreich ausgeliefert, Status ist jetzt
 *      AUFTRAG_ABGESCHLOSSEN.
 *  -1  ein Artikel einer Position wurde nicht gefunden. Status
 *      bleibt unveraendert (kein Teilbuchen).
 *  -2  Bestand einer Position reicht nicht aus. Status bleibt
 *      unveraendert.
 *  -3  Fehler beim eigentlichen Buchen (sollte nach erfolgreicher
 *      Pruefung praktisch nie auftreten).
 *  -4  auftrag ist NULL.
 *  -5  Auftrag ist bereits abgeschlossen (mehrfache Auslieferung
 *      verhindern).
 */
int auftrag_bestand_abbuchen(
    Auftrag *auftrag
);

/* Kurztext des Status fuer die Bildschirmausgabe (max. 15 Zeichen) */
const char *auftrag_status_text(
    Auftragsstatus status
);

#endif
