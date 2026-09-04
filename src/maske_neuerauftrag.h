#ifndef D621_MASKE_NEUERAUFTRAG_H
#define D621_MASKE_NEUERAUFTRAG_H

#include "ergebnis.h"
#include "auftrag.h"

/*
 * Erfasst einen neuen Auftrag (Kunde + Positionen) und legt ihn bei
 * Erfolg direkt in der Auftragsverwaltung an.
 *
 * ERG_OK      -> *erstellter_auftrag_out zeigt auf den neu
 *                angelegten Auftrag (Status AUFTRAG_NEU).
 * ERG_ZURUECK -> abgebrochen (ESC), *erstellter_auftrag_out
 *                unveraendert.
 *
 * Hinweis: Anders als im Ruby-Original wird der Lagerbestand HIER
 * NICHT abgebucht - das geschieht ausschliesslich einmalig bei der
 * Auslieferung (auftrag_bestand_abbuchen). Das Original bucht an
 * beiden Stellen (Neuerauftrag UND Auslieferung), was zu einer
 * doppelten Bestandsminderung fuehrt; das wurde hier bewusst
 * korrigiert. Waehrend der Erfassung wird trotzdem live geprueft,
 * ob genuegend freier (= noch nicht in diesem Auftrag verplanter)
 * Bestand vorhanden ist.
 */
Ergebnis maske_neuerauftrag_anzeigen(Auftrag **erstellter_auftrag_out);

#endif
