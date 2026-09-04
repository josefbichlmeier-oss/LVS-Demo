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

## Projektstruktur

```
config/config.h        Zentrale Konfiguration (Geometrie, Baudrate, Pins)
src/platform.h          Compile-Zeit-Weiche PLATFORM_LINUX/PLATFORM_ESP32
src/terminal*.c/h        Terminal-Treiber (ANSI bzw. Hazeltine-Bytefolgen)
src/uart_port*.h/.cpp    UART-Anbindung ESP32 (Arduino HardwareSerial)
src/tastatur*.c/h        Tastatureingabe (Linux Raw-Mode / Hazeltine-Rueckkanal)
src/zeit_port*.h/.c/.cpp Kopfzeilen-Uhrzeit (Systemzeit / Laufzeit seit Boot)
src/bildschirm.c/h       Bildschirmpuffer mit Dirty-Tracking
src/eingabe*.c/h         Zeilenweise Eingabe, Eingabefeld (Anmeldemaske)
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
  Modul, NTP) keine Wanduhr - die Kopfzeile zeigt dort ersatzweise
  die Laufzeit seit dem letzten Start ("LZ hh:mm:ss").
- **Feste Obergrenzen** statt dynamischer Ruby-Arrays: siehe
  `MAX_ARTIKEL`, `MAX_KUNDEN`, `MAX_AUFTRAEGE`, `MAX_POSITIONEN`,
  `MAX_LAGERBEWEGUNGEN` in den jeweiligen Headern - fuer den
  Speicher eines ESP32 unkritisch, im Betrieb aber zu beachten.

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
