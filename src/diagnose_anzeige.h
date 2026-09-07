/*
 * D621-LVS
 *
 * Optionales Nokia 5110 (PCD8544) Diagnose-Display - siehe
 * config.h D621_NOKIA5110_AKTIV. Rein fuer Betriebskontrolle vor
 * Ort gedacht (laeuft der ESP32? kommt Datenverkehr auf der
 * Hazeltine-Leitung an?), voellig unabhaengig von der eigentlichen
 * Anwendungslogik. Ist das Display deaktiviert oder nicht
 * angeschlossen, sind beide Funktionen wirkungslose No-Ops - die
 * Aufrufstellen (main_esp32.cpp, tastatur_hazeltine.c) muessen
 * sich darum nicht kuemmern.
 */

#ifndef D621_DIAGNOSE_ANZEIGE_H
#define D621_DIAGNOSE_ANZEIGE_H

#ifdef __cplusplus
extern "C" {
#endif

void diagnose_anzeige_init(void);

/* Aktualisiert das Display hoechstens einmal pro Sekunde (intern
 * per Zeitstempel gedrosselt) - kann daher beliebig oft aufgerufen
 * werden, z.B. bei jedem Durchlauf der Tastatur-Pollingschleife. */
void diagnose_anzeige_tick(void);

#ifdef __cplusplus
}
#endif

#endif
