# D621-LVS - C-Portierung (ESP32/Hazeltine/VT220)

C-Portierung der Ruby-Referenzimplementierung einer Lager- und
Auftragsverwaltung fuer ein Museum. Zwei Build-Ziele aus **einem**
gemeinsamen Quellbaum:

- **Linux-Debug-Build** (`make`): Ausgabe per ANSI-Escapecodes auf
  der virtuellen Konsole, Tastatur im Raw-Modus. Zum Testen der
  Anwendungslogik ohne Hardware.
- **ESP32-Zielbuild** (`platformio.ini`, Arduino-Core): Ausgabe an
  ein angeschlossenes serielles Terminal ueber Hardware-UART2 +
  externen RS232-Pegelwandler (z.B. MAX3232), 9600 8N1.
  Tastatureingaben kommen ueber dieselbe Leitung vom Terminal
  zurueck. Zwei Terminaltypen werden unterstuetzt - welcher davon
  tatsaechlich angesprochen wird, waehlt
  `config/config.h` -> `D621_ESP32_TERMINAL`:
  - **Hazeltine 2000A/B** (`D621_TERMINAL_HAZELTINE`, Standard):
    proprietaeres Bytefolgen-Protokoll, siehe `src/terminal_hazeltine.c`.
  - **DEC VT220** (`D621_TERMINAL_VT220`): Standard-ANSI/VT100-
    Escapecodes, siehe `src/terminal_vt220.c`.

  Beide Terminaltreiber sind immer Teil des Quellbaums, aber pro
  Build ist nur einer davon aktiv - kein gleichzeitiger Betrieb
  beider Terminals an einem ESP32 (dafuer waere eine zweite
  UART-Instanz noetig, was hier nicht umgesetzt ist).

Die Auswahl der passenden Terminal-/Tastatur-/UART-Implementierung
erfolgt automatisch zur Compile-Zeit (`src/platform.h` fuer
Linux/ESP32, `config/config.h` -> `D621_ESP32_TERMINAL` fuer
Hazeltine/VT220 auf dem ESP32), nicht zur Laufzeit - jede
Zielkonfiguration ist fest an ein Ausgabegeraet gebunden.

## Bauen (Linux-Debug)

```
make
./d621-lvs
```

## Bauen (ESP32)

Benoetigt [PlatformIO](https://platformio.org/) (nicht Teil dieses
Pakets, laedt die ESP32-Toolchain beim ersten Aufruf aus dem
Internet nach - in der Sandbox, in der dieser Code entstanden ist,
war das nicht moeglich, siehe "Bekannte Einschraenkungen" unten).
Vor dem Bauen in `config/config.h` den gewuenschten Terminaltyp
einstellen (`D621_ESP32_TERMINAL`, Standard: Hazeltine):

```
pio run -e esp32dev
pio run -e esp32dev -t upload
pio device monitor
```

Board in `platformio.ini` ggf. an das tatsaechlich verwendete
ESP32-Modul anpassen (Standard: `esp32dev`).

### Verkabelung

Bei beiden Terminaltypen identisch (nur ein RS232-Geraet
gleichzeitig angeschlossen, je nach `D621_ESP32_TERMINAL`):

| ESP32        | MAX3232 | Terminal (RS232, DB25/DB9) |
|--------------|---------|------------------------------|
| GPIO17 (TX2) | T1IN    | RxD                           |
| GPIO16 (RX2) | R1OUT   | TxD                           |
| GND          | GND     | GND                           |

Pins/UART-Nummer in `config/config.h`
(`D621_ESP32_RXD_PIN`/`D621_ESP32_TXD_PIN`/`D621_ESP32_UART_NUM`)
konfigurierbar. UART0 (USB) bleibt frei fuer Flashen/Debug-Log
(siehe Abschnitt "Debug-Logging" unten).

Ein VT220 kann in der Praxis auch mit hoeheren Baudraten (19200,
38400) betrieben werden - `D621_BAUDRATE` bei Bedarf anpassen, muss
zur tatsaechlichen Einstellung am VT220 (Setup-Menue) passen.

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
src/terminal*.c/h        Terminal-Treiber (ANSI-Konsole, Hazeltine-Bytefolgen, VT220-Escapecodes)
src/uart_port*.h/.cpp    UART-Anbindung ESP32 (Arduino HardwareSerial)
src/tastatur*.c/h        Tastatureingabe (Linux Raw-Mode / serielles Polling fuer Hazeltine+VT220)
src/zeit_port*.h/.c/.cpp Kopfzeilen-Uhrzeit, Plattform-Standard (Systemzeit / Laufzeit)
src/monotonzeit.h/.c/.cpp Monotone Sekundenuhr (millis() / CLOCK_MONOTONIC)
src/systemzeit.c/h      Manuell gesetzte Uhrzeit, zaehlt danach weiter
src/diagnose_anzeige.cpp Optionales Nokia-5110-Diagnose-Display (ESP32-only)
src/debug_log.h/.c/.cpp  Logging ueber USB/Programmierschnittstelle (UART0) bzw. stderr
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

- **VT220 als zweiter Terminaltyp**: Das Ruby-Original kennt nur
  Hazeltine (und die Linux-Konsole zum Testen). Diese Portierung
  ergaenzt einen zweiten, gleichwertigen ESP32-Zielbetrieb fuer ein
  DEC VT220 ueber Standard-ANSI/VT100-Escapecodes
  (`src/terminal_vt220.c`) - Details siehe Abschnitt "Bauen (ESP32)"
  oben. Fuer die Hervorhebung ("hell"/"dunkel") wird dabei bewusst
  Invers-Video (SGR 7) statt Farbcodes verwendet, da echte
  VT220-Hardware monochrom ist und keine ANSI-Farben kennt.
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

## Debug-Logging ueber die USB/Programmierschnittstelle

Unabhaengig vom Nokia-Display und ohne zusaetzliche Hardware: Ueber
UART0 (Serial, derselbe USB-Anschluss, der auch zum Flashen dient)
gibt der ESP32 Klartext-Logzeilen zu allen wichtigen Vorgaengen aus
- einfach per `pio device monitor` (oder jedem anderen seriellen
Terminal, 115200 8N1) mitzulesen. Voellig getrennt von UART2
(Hazeltine) und vom Nokia-Display.

Protokolliert werden u.a.: Initialisierung, Anmeldeversuche (Name
ja, Kennwort NIE), Wareneingang/-ausgang-Buchungen inkl.
Fehlerfaellen (Artikel nicht gefunden, Bestand nicht ausreichend),
neu angelegte Auftraege und jede Auslieferung (inkl. Ablehnung bei
bereits ausgelieferten Auftraegen).

In `config/config.h` per `D621_DEBUG_LOG_AKTIV` abschaltbar (Standard:
an) und `D621_DEBUG_BAUDRATE` (Standard 115200) einstellbar. Auf
dem Linux-Debug-Build landet dieselbe Ausgabe auf stderr
(`./d621-lvs 2> log.txt`), getrennt von der Bildschirmausgabe auf
stdout.

`debug_log()` ist mit `__attribute__((format(printf,...)))`
markiert, sodass GCC/Clang auf dem Linux-Build Formatstring-Fehler
in den Aufrufstellen (`src/anwendung.c`, `src/maske_anmeldung.c`,
...) bereits beim Kompilieren erkennt - genutzt, um alle
Log-Aufrufe zu verifizieren, da sich die tatsaechliche
Serial-Ausgabe auf echter ESP32-Hardware hier nicht beobachten
liess.

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
  Dateien (`terminal_hazeltine.c`, `terminal_vt220.c`,
  `tastatur_seriell.c`, `uart_port_esp32.cpp`, `zeit_port_esp32.cpp`,
  `main_esp32.cpp`) gegen einen minimalen Arduino-API-Stub
  kompiliert und verlinkt, um zumindest Syntax-/Typfehler
  auszuschliessen - **fuer beide Terminal-Konfigurationen einzeln**
  (`D621_ESP32_TERMINAL` auf Hazeltine bzw. VT220 gestellt), inkl.
  Gegenpruefung per `nm`, dass jeweils nur der aktive Treiber
  tatsaechlich Code erzeugt und der inaktive vollstaendig leer
  bleibt. Der erste reale `pio run -e esp32dev` steht in jedem Fall
  noch aus - bitte kurz rueckmelden, ob und mit welchem Fehler er
  ggf. scheitert. Insbesondere die VT220-Escapecodes selbst
  (`terminal_vt220.c`) sind Standard-ANSI/VT100 und sollten auf
  echter Hardware funktionieren, wurden aber mangels VT220-Emulator
  in dieser Sandbox nicht gegen ein echtes Geraet/eine Emulation
  verifiziert - anders als die Hazeltine-Bytefolgen, die 1:1 aus
  der Ruby-Vorlage uebernommen sind.
- Kein Dateisystem/Persistenz - wie im Ruby-Original leben alle
  Daten nur im RAM und sind nach einem Neustart wieder auf dem
  Demo-Stand (siehe `src/demo.c`).
