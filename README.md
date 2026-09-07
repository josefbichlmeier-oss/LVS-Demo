# D621-LVS - C-Portierung (ESP32/Hazeltine)

C-Portierung der Ruby-Referenzimplementierung einer Lager- und
Auftragsverwaltung fuer ein Museum. Zwei Build-Ziele aus **einem**
gemeinsamen Quellbaum:

- **Linux-Debug-Build** (`make`): Ausgabe per ANSI-Escapecodes auf
  der virtuellen Konsole, Tastatur im Raw-Modus. Zum Testen der
  Anwendungslogik ohne Hardware.
- **ESP32-Zielbuild** (`platformio.ini`, Arduino-Core): Ausgabe an
  ein Hazeltine 2000A/B ueber Hardware-UART2 + externen
  RS232-Pegelwandler (z.B. MAX3232), 9600 8N1. Tastatureingaben
  kommen ueber dieselbe Leitung vom Hazeltine zurueck.

Die Auswahl der passenden Terminal-/Tastatur-/UART-Implementierung
erfolgt automatisch zur Compile-Zeit (`src/platform.h`), nicht zur
Laufzeit - jede Zielplattform ist fest an ein Ausgabegeraet
gebunden.

## Bauen (Linux-Debug)

```
make
./d621-lvs
```

## Bauen (ESP32)

Benoetigt [PlatformIO](https://platformio.org/) (nicht Teil dieses
Pakets, laedt die ESP32-Toolchain beim ersten Aufruf aus dem
Internet nach - in der Sandbox, in der dieser Code entstanden ist,
war das nicht moeglich, siehe "Bekannte Einschraenkungen" unten):

```
pio run -e esp32dev
pio run -e esp32dev -t upload
pio device monitor
```

Board in `platformio.ini` ggf. an das tatsaechlich verwendete
ESP32-Modul anpassen (Standard: `esp32dev`).

### Verkabelung

| ESP32        | MAX3232 | Hazeltine 2000A/B (RS232, DB25/DB9) |
|--------------|---------|--------------------------------------|
| GPIO17 (TX2) | T1IN    | RxD                                    |
| GPIO16 (RX2) | R1OUT   | TxD                                    |
| GND          | GND     | GND                                    |

Pins/UART-Nummer in `config/config.h`
(`D621_ESP32_RXD_PIN`/`D621_ESP32_TXD_PIN`/`D621_ESP32_UART_NUM`)
konfigurierbar. UART0 (USB) bleibt frei fuer Flashen/Log.

## Erweiterungen gegenueber der ersten Portierung

- **Artikeldetails aus dem Lagerbestand**: Unter LAGER -> BESTAND
  ANZEIGEN kann jetzt direkt eine Artikelnummer eingegeben werden,
  um die Detailanzeige zu oeffnen (analog zur Artikelsuche). Leere
  Eingabe zeichnet die Liste einfach neu, ESC geht zurueck ins
  Lager-Menue.
- **Bestaetigung vor Auslieferung**: In der Auftragsanzeige loest
  die Taste "A" (AUSLIEFERN) zunaechst die Rueckfrage "WIRKLICH
  AUSLIEFERN? J/N" aus. Nur "J" fuehrt tatsaechlich zur Buchung
  (`auftrag_bestand_abbuchen`); "N" oder ESC kehren ohne jede
  Nebenwirkung zur Auftragsanzeige zurueck.
- **Paginierung** (`src/paginierung.c/h`): Alle listenbasierten
  Masken (Lagerbestand, Artikelstamm, Artikelsuche,
  Kundenuebersicht, Auftragsuebersicht, Lagerbewegungen) blaettern
  jetzt seitenweise, sobald mehr Eintraege vorhanden sind, als auf
  einen Bildschirm passen - Taste "+" fuer die naechste, "-" fuer
  die vorherige Seite, Anzeige "SEITE x/y" auf dem Bildschirm. Bei
  Masken mit anschliessender Nummerneingabe (Lagerbestand,
  Artikelsuche, Kundenuebersicht, Auftragsuebersicht) wird dazu das
  jeweils erste gedrueckte Zeichen zunaechst auf "+"/"-"/ESC
  geprueft (`eingabe_zeile_mit_erstem_zeichen()` in `src/eingabe.c`)
  und nur bei einer normalen Ziffer als Beginn der Nummerneingabe
  gewertet - dadurch bleibt das Verhalten aller anderen
  Eingabefelder (z.B. Mengenfelder) unveraendert.
- **Datum/Uhrzeit einstellen** (Hauptmenue -> 5): manuelles Setzen
  von Datum und Uhrzeit, die danach in Echtzeit weiterlaeuft -
  siehe Abschnitt "Bewusste Abweichungen" unten. Mit simulierten
  Zeitspruengen getestet (Jahreswechsel, Schaltjahre inkl.
  korrektem Ein-/Ausschluss des 29. Februar).
- **Optionales Nokia-5110-Diagnose-Display** (`src/diagnose_anzeige.cpp`,
  `config.h` -> `D621_NOKIA5110_AKTIV`, standardmaessig **aus**):
  ESP32-only, zeigt auf einem angeschlossenen Nokia 5110/PCD8544-
  Display Laufzeit, gesendete/empfangene UART-Bytes, die zuletzt
  vom Hazeltine empfangene Taste (hex) und freien Heap-Speicher -
  unabhaengig von der Hazeltine-Verbindung, rein zur
  Betriebskontrolle vor Ort (z.B. "kommt ueberhaupt etwas vom
  Terminal an?"). Details, Verkabelung und ein wichtiger Hinweis
  zur Testabdeckung dieses Teils weiter unten unter "Nokia 5110
  Diagnose-Display".

## Projektstruktur

```
config/config.h        Zentrale Konfiguration (Geometrie, Baudrate, Pins)
src/platform.h          Compile-Zeit-Weiche PLATFORM_LINUX/PLATFORM_ESP32
src/terminal*.c/h        Terminal-Treiber (ANSI bzw. Hazeltine-Bytefolgen)
src/uart_port*.h/.cpp    UART-Anbindung ESP32 (Arduino HardwareSerial)
src/tastatur*.c/h        Tastatureingabe (Linux Raw-Mode / Hazeltine-Rueckkanal)
src/zeit_port*.h/.c/.cpp Kopfzeilen-Uhrzeit, Plattform-Standard (Systemzeit / Laufzeit)
src/monotonzeit.h/.c/.cpp Monotone Sekundenuhr (millis() / CLOCK_MONOTONIC)
src/systemzeit.c/h      Manuell gesetzte Uhrzeit, zaehlt danach weiter
src/diagnose_anzeige.cpp Optionales Nokia-5110-Diagnose-Display (ESP32-only)
src/bildschirm.c/h       Bildschirmpuffer mit Dirty-Tracking
src/eingabe*.c/h         Zeilenweise Eingabe, Eingabefeld (Anmeldemaske)
src/paginierung.c/h      Seitenweises Blaettern durch Listen (+/- Tasten)
src/artikel*, kunde*,    Datenmodelle (statische Arrays, kein Dateisystem)
src/auftrag*, lagerbewegung*
src/maske_*.c/h          Alle Bildschirmmasken (1:1 zu masken/*.rb)
src/anwendung.c/h        Zustandsautomat (1:1 zu system/anwendung.rb)
src/main.c               Linux-Einstiegspunkt (main())
src/main_esp32.cpp       ESP32-Einstiegspunkt (setup()/loop())
```

## Bewusste Abweichungen vom Ruby-Original

- **Doppelte Bestandsbuchung korrigiert**: Im Original bucht sowohl
  `Neuerauftrag` (bei der Erfassung) als auch `Auslieferung` (bei
  der Lieferung) den Lagerbestand ab. Hier wird der Bestand nur
  noch **einmal**, bei der Auslieferung, abgebucht
  (`auftrag_bestand_abbuchen` in `src/auftrag.c`). Waehrend der
  Erfassung eines neuen Auftrags erfolgt stattdessen eine reine
  Verfuegbarkeitspruefung (Bestand abzueglich bereits im aktuellen
  Auftragsentwurf verplanter Mengen).
- **Auftragsstatus als C-Enum** (`AUFTRAG_NEU/BEARBEITET/
  ABGESCHLOSSEN`) statt Ruby-Strings ("OFFEN"/"IN BEARBEITUNG"/
  "AUSGELIEFERT") - wie abgestimmt. `auftrag_status_text()` liefert
  fuer die Anzeige die entsprechenden deutschen Texte.
- **Lagerbewegungstext vereinfacht**: Ruby unterscheidet je Vorgang
  z.B. "AUFTRAG 4711" als Buchungstext; das C-Enum
  `Lagerbewegungstyp` kennt nur EINGANG/AUSGANG, die Anzeige zeigt
  entsprechend nur "WARENEINGANG"/"WARENAUSGANG".
- **Uhrzeit in der Kopfzeile**: Linux zeigt wie im Original die
  echte Systemzeit. Der ESP32 hat ohne zusaetzliche Hardware (RTC-
  Modul, NTP) keine eingebaute Wanduhr - dafuer gibt es jetzt im
  Hauptmenue den Punkt "5 DATUM/UHRZEIT EINSTELLEN"
  (`src/maske_datumzeit.c`, `src/systemzeit.c/h`): einmal manuell
  gesetzt, zaehlt die Uhrzeit intern anhand einer monotonen
  Systemuhr (`src/monotonzeit.h` - `millis()` auf dem ESP32,
  `CLOCK_MONOTONIC` unter Linux) in Echtzeit weiter, inklusive
  korrekter Kalenderumrechnung (Monats-/Jahreswechsel,
  Schaltjahre). Nach einem Neustart (Stromausfall, Reset) ist die
  Uhrzeit wieder nicht gesetzt und muss neu eingegeben werden - ein
  DS3231-RTC-Modul oder NTP waeren die naechste sinnvolle Ausbaustufe,
  falls das stoert.
- **Feste Obergrenzen** statt dynamischer Ruby-Arrays: siehe
  `MAX_ARTIKEL`, `MAX_KUNDEN`, `MAX_AUFTRAEGE`, `MAX_POSITIONEN`,
  `MAX_LAGERBEWEGUNGEN` in den jeweiligen Headern - fuer den
  Speicher eines ESP32 unkritisch, im Betrieb aber zu beachten.

## Nokia 5110 Diagnose-Display (optional)

Rein fuer Betriebskontrolle vor Ort gedacht - unabhaengig von der
eigentlichen Anwendung, betrifft nicht die Ruby-Portierung selbst.

### Aktivieren

In `config/config.h`:
```c
#define D621_NOKIA5110_AKTIV 1
```
Standardmaessig auf 0 (aus) - dann wird weder ein Pin dafuer
beansprucht noch die Adafruit-Bibliothek eingebunden.

### Verkabelung (Software-SPI, beliebige freie GPIOs)

| Nokia 5110  | ESP32 (Standardbelegung, config.h) |
|-------------|--------------------------------------|
| RST         | GPIO2  (`D621_ESP32_NOKIA_RST_PIN`) |
| CE (CS)     | GPIO5  (`D621_ESP32_NOKIA_CS_PIN`)  |
| DC          | GPIO4  (`D621_ESP32_NOKIA_DC_PIN`)  |
| DIN (MOSI)  | GPIO23 (`D621_ESP32_NOKIA_DIN_PIN`) |
| CLK         | GPIO18 (`D621_ESP32_NOKIA_CLK_PIN`) |
| VCC         | **3.3V** (nicht 5V!)                 |
| BL          | 3.3V ueber Vorwiderstand (~330R), oder GND fuer aus |
| GND         | GND                                  |

Pins sind per Software-SPI angesprochen, also frei waehlbar -
muessen nur von UART2 (GPIO16/17) verschieden sein.

### Was angezeigt wird

Aktualisiert sich einmal pro Sekunde (intern gedrosselt, ausgeloest
aus der Tastatur-Pollingschleife):
- Laufzeit seit dem letzten Start
- Anzahl gesendeter/empfangener UART-Bytes seit dem Start (zeigt,
  ob ueberhaupt Datenverkehr zum/vom Hazeltine stattfindet)
- Zuletzt vom Hazeltine empfangenes Byte (hex) - hilfreich, um zu
  pruefen, ob Tastendruecke tatsaechlich ankommen
- Freier Heap-Speicher

### Wichtiger Hinweis zur Testabdeckung

Anders als der restliche ESP32-Code (der gegen einen selbst
geschriebenen Arduino-API-Stub kompiliert und verlinkt wurde, siehe
oben) wurde `src/diagnose_anzeige.cpp` zusaetzlich gegen selbst
geschriebene **Fake-Header** fuer `Adafruit_GFX`/`Adafruit_PCD8544`
kompiliert - die echten Bibliotheken konnten mangels
Netzwerkzugriff in dieser Sandbox nicht heruntergeladen werden. Die
verwendete API (Konstruktor, `begin()`, `setContrast()`,
`clearDisplay()`, `setCursor()`, `setTextSize()`,
`setTextColor()`, `println()`, `display()`) entspricht meiner
Erinnerung an die weit verbreitete, seit Jahren stabile
Adafruit-PCD8544-Bibliothek, aber das ist **keine Garantie**, dass
sie exakt zur tatsaechlich von PlatformIO heruntergeladenen Version
passt. Bitte beim ersten echten `pio run` kurz gegenpruefen - falls
es Kompilierfehler in `diagnose_anzeige.cpp` gibt, liegt es
vermutlich an einer leicht abweichenden Methodensignatur der
echten Bibliothek.

## Bekannte Einschraenkungen / noch offen

- Der Linux-Debug-Build wurde in dieser Sandbox tatsaechlich
  kompiliert **und** mit simulierten Tastatureingaben funktional
  durchgetestet (Anmeldung, alle Masken, Auslieferung inkl.
  Bestandsbuchung, Fehlerpfade).
- Der ESP32-Build konnte in dieser Sandbox **nicht** ueber den
  echten PlatformIO/ESP-IDF-Toolchain gebaut werden (kein
  Netzwerkzugriff, PlatformIO laedt Toolchain/Framework beim
  ersten Lauf herunter). Ersatzweise wurden alle ESP32-spezifischen
  Dateien (`terminal_hazeltine.c`, `tastatur_hazeltine.c`,
  `uart_port_esp32.cpp`, `zeit_port_esp32.cpp`, `main_esp32.cpp`)
  gegen einen minimalen Arduino-API-Stub kompiliert und verlinkt,
  um zumindest Syntax-/Typfehler auszuschliessen. Der erste
  reale `pio run -e esp32dev` steht noch aus - bitte kurz
  rueckmelden, ob und mit welchem Fehler er ggf. scheitert.
- Kein Dateisystem/Persistenz - wie im Ruby-Original leben alle
  Daten nur im RAM und sind nach einem Neustart wieder auf dem
  Demo-Stand (siehe `src/demo.c`).
