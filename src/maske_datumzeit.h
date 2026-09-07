#ifndef D621_MASKE_DATUMZEIT_H
#define D621_MASKE_DATUMZEIT_H

/*
 * Erlaubt das manuelle Einstellen von Datum und Uhrzeit
 * (systemzeit_setzen()). Vor allem fuer den ESP32 gedacht, der
 * keine eingebaute Echtzeituhr besitzt - siehe systemzeit.h.
 */
void maske_datumzeit_anzeigen(void);

#endif
