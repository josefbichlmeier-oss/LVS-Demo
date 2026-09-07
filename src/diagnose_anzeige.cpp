/*
 * D621-LVS
 *
 * Implementierung des optionalen Nokia-5110-Diagnose-Displays.
 * Nur aktiv, wenn D621_NOKIA5110_AKTIV in config.h auf 1 steht -
 * andernfalls sind beide Funktionen leere No-Ops, und weder die
 * Adafruit-Bibliotheken noch irgendein Pin werden dafuer benoetigt.
 *
 * Verkabelung (Software-SPI, beliebige GPIOs - siehe config.h):
 *   Nokia 5110      ESP32
 *   RST        ->   D621_ESP32_NOKIA_RST_PIN
 *   CE (CS)    ->   D621_ESP32_NOKIA_CS_PIN
 *   DC         ->   D621_ESP32_NOKIA_DC_PIN
 *   DIN (MOSI) ->   D621_ESP32_NOKIA_DIN_PIN
 *   CLK        ->   D621_ESP32_NOKIA_CLK_PIN
 *   VCC        ->   3.3V  (NICHT 5V - das Display vertraegt nur 3.3V!)
 *   BL         ->   3.3V ueber Vorwiderstand (z.B. 330R), oder GND fuer aus
 *   GND        ->   GND
 */

#include "platform.h"

#if defined(PLATFORM_ESP32)

#include "../config/config.h"

extern "C" {
#include "diagnose_anzeige.h"
}

#if D621_NOKIA5110_AKTIV

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

extern "C" {
#include "uart_port.h"
}

static Adafruit_PCD8544 display(
    D621_ESP32_NOKIA_CLK_PIN,
    D621_ESP32_NOKIA_DIN_PIN,
    D621_ESP32_NOKIA_DC_PIN,
    D621_ESP32_NOKIA_CS_PIN,
    D621_ESP32_NOKIA_RST_PIN
);

static unsigned long letzte_aktualisierung = 0;


void diagnose_anzeige_init(void)
{
    display.begin();
    display.setContrast(55);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(BLACK);

    display.setCursor(0, 0);
    display.println("D621-LVS");
    display.println("STARTE...");
    display.display();

    letzte_aktualisierung = 0;
}


void diagnose_anzeige_tick(void)
{
    unsigned long jetzt = millis();

    if (letzte_aktualisierung != 0 && jetzt - letzte_aktualisierung < 1000)
    {
        return;
    }

    letzte_aktualisierung = jetzt;

    unsigned long laufzeit_s = jetzt / 1000UL;
    unsigned long stunden = laufzeit_s / 3600UL;
    unsigned long minuten = (laufzeit_s / 60UL) % 60UL;
    unsigned long sekunden = laufzeit_s % 60UL;

    unsigned long tx_bytes;
    unsigned long rx_bytes;
    unsigned char letztes_byte;

    uart_port_diagnose(&tx_bytes, &rx_bytes, &letztes_byte);

    char zeile[16];

    display.clearDisplay();

    display.setCursor(0, 0);
    display.println("D621-LVS");

    snprintf(zeile, sizeof(zeile), "LZ %02lu:%02lu:%02lu", stunden, minuten, sekunden);
    display.println(zeile);

    snprintf(zeile, sizeof(zeile), "TX:%-5lu", tx_bytes);
    display.println(zeile);

    snprintf(zeile, sizeof(zeile), "RX:%-5lu", rx_bytes);
    display.println(zeile);

    snprintf(zeile, sizeof(zeile), "TASTE 0x%02X", letztes_byte);
    display.println(zeile);

    snprintf(zeile, sizeof(zeile), "HEAP %luKB", (unsigned long)(ESP.getFreeHeap() / 1024));
    display.println(zeile);

    display.display();
}

#else /* !D621_NOKIA5110_AKTIV - Display nicht angeschlossen/aktiviert */

void diagnose_anzeige_init(void) {}
void diagnose_anzeige_tick(void) {}

#endif /* D621_NOKIA5110_AKTIV */

#endif /* PLATFORM_ESP32 */
