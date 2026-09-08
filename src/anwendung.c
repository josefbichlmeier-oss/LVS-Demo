#include <stddef.h>

#include "anwendung.h"
#include "ergebnis.h"

#include "terminal.h"
#include "bildschirm.h"
#include "eingabe.h"
#include "tastatur.h"

#include "artikel.h"
#include "kunde.h"
#include "auftrag.h"
#include "auftragsverwaltung.h"
#include "lagerbewegungsbestand.h"
#include "demo.h"

#include "maske_start.h"
#include "maske_anmeldung.h"
#include "maske_hauptmenue.h"
#include "maske_lager.h"
#include "maske_lagerbestand.h"
#include "maske_lagerbewegungen.h"
#include "maske_artikelstamm.h"
#include "maske_artikelsuche.h"
#include "maske_artikelanzeige.h"
#include "maske_wareneingang.h"
#include "maske_warenausgang.h"
#include "maske_auftragsmenue.h"
#include "maske_auftragsuebersicht.h"
#include "maske_auftragsanzeige.h"
#include "maske_neuerauftrag.h"
#include "maske_kundenmenue.h"
#include "maske_kundenuebersicht.h"
#include "maske_kundenanzeige.h"
#include "maske_datumzeit.h"
#include "maske_fehlermeldung.h"
#include "maske_meldung.h"
#include "debug_log.h"


static void lager_verarbeiten(void)
{
    Ergebnis lager_auswahl = maske_lager_anzeigen();

    switch (lager_auswahl)
    {
        case ERG_BESTAND:
        {
            maske_lagerbestand_anzeigen();
            break;
        }

        case ERG_WARENEINGANG:
        {
            char nummer[16];
            int menge;

            Ergebnis eingabe_ergebnis =
                maske_wareneingang_anzeigen(nummer, sizeof(nummer), &menge);

            if (eingabe_ergebnis == ERG_ZURUECK)
                break;

            Ergebnis buchung =
                maske_wareneingang_buchen(nummer, menge);

            if (buchung == ERG_OK)
            {
                debug_log("Wareneingang gebucht: Artikel '%s', Menge %d", nummer, menge);
                maske_meldung_anzeigen("BUCHUNG DURCHGEFUEHRT");
            }
            else if (buchung == ERG_NICHT_GEFUNDEN)
            {
                debug_log("Wareneingang fehlgeschlagen: Artikel '%s' nicht gefunden", nummer);
                maske_fehlermeldung_anzeigen("ARTIKEL NICHT GEFUNDEN");
            }

            break;
        }

        case ERG_BEWEGUNGEN:
        {
            maske_lagerbewegungen_anzeigen();
            break;
        }

        case ERG_WARENAUSGANG:
        {
            char nummer[16];
            int menge;

            Ergebnis eingabe_ergebnis =
                maske_warenausgang_anzeigen(nummer, sizeof(nummer), &menge);

            if (eingabe_ergebnis == ERG_ZURUECK)
                break;

            Ergebnis buchung =
                maske_warenausgang_buchen(nummer, menge);

            if (buchung == ERG_OK)
            {
                debug_log("Warenausgang gebucht: Artikel '%s', Menge %d", nummer, menge);
                maske_meldung_anzeigen("BUCHUNG DURCHGEFUEHRT");
            }
            else if (buchung == ERG_NICHT_GEFUNDEN)
            {
                debug_log("Warenausgang fehlgeschlagen: Artikel '%s' nicht gefunden", nummer);
                maske_fehlermeldung_anzeigen("ARTIKEL NICHT GEFUNDEN");
            }
            else if (buchung == ERG_BESTAND_UNZUREICHEND)
            {
                debug_log("Warenausgang fehlgeschlagen: Bestand nicht ausreichend fuer '%s' (Menge %d)", nummer, menge);
                maske_fehlermeldung_anzeigen("BESTAND NICHT AUSREICHEND");
            }

            break;
        }

        case ERG_SUCHE:
        {
            char nummer[21];

            Ergebnis suche_ergebnis =
                maske_artikelsuche_anzeigen(nummer, sizeof(nummer));

            if (suche_ergebnis == ERG_ZURUECK)
                break;

            Artikel *artikel = artikel_finden(nummer);

            if (artikel)
            {
                maske_artikelanzeige_anzeigen(artikel);
            }
            else
            {
                maske_fehlermeldung_anzeigen("ARTIKEL NICHT GEFUNDEN");
            }

            break;
        }

        default:
            /* ERG_ZURUECK oder unbekannt - kommentarlos zurueck ins
             * Hauptmenue, wie im Original (Ruby behandelt :zurueck
             * hier ebenfalls nicht explizit). */
            break;
    }
}


static void kunde_verarbeiten(void)
{
    Ergebnis kunden_auswahl = maske_kundenmenue_anzeigen();

    if (kunden_auswahl == ERG_ANZEIGEN)
    {
        char nummer[21];

        Ergebnis ergebnis =
            maske_kundenuebersicht_anzeigen(nummer, sizeof(nummer));

        if (ergebnis == ERG_ZURUECK)
            return;

        Kunde *kunde = kunde_finden(nummer);

        if (kunde)
        {
            maske_kundenanzeige_anzeigen(kunde);
        }
    }
}


static void auftrag_bearbeiten(void)
{
    for (;;)
    {
        Ergebnis auftrag_auswahl = maske_auftragsmenue_anzeigen();

        if (auftrag_auswahl == ERG_NEU)
        {
            Auftrag *neuer_auftrag = NULL;

            Ergebnis ergebnis =
                maske_neuerauftrag_anzeigen(&neuer_auftrag);

            if (ergebnis == ERG_ZURUECK)
                continue;

            debug_log(
                "Neuer Auftrag %d angelegt: Kunde '%s', %d Position(en)",
                neuer_auftrag->nummer,
                neuer_auftrag->kundennummer,
                neuer_auftrag->positionen_anzahl
            );

            maske_meldung_anzeigen("AUFTRAG ERHALTEN");
        }
        else if (auftrag_auswahl == ERG_ANZEIGEN)
        {
            int nummer;

            Ergebnis ergebnis =
                maske_auftragsuebersicht_anzeigen(&nummer);

            if (ergebnis == ERG_ZURUECK)
                continue;

            Auftrag *auftrag = auftrag_finden(nummer);

            if (!auftrag)
            {
                maske_fehlermeldung_anzeigen("AUFTRAG NICHT GEFUNDEN");
                continue;
            }

            Ergebnis anzeige_ergebnis =
                maske_auftragsanzeige_anzeigen(auftrag);

            if (anzeige_ergebnis == ERG_AUSLIEFERN)
            {
                int abbuchen_ergebnis =
                    auftrag_bestand_abbuchen(auftrag);

                switch (abbuchen_ergebnis)
                {
                    case 0:
                        debug_log("Auftrag %d ausgeliefert (Kunde '%s')", auftrag->nummer, auftrag->kundennummer);
                        maske_meldung_anzeigen("AUFTRAG AUSGELIEFERT");
                        break;

                    case -5:
                        debug_log("Auslieferung Auftrag %d abgelehnt: bereits ausgeliefert", auftrag->nummer);
                        maske_fehlermeldung_anzeigen("AUFTRAG BEREITS AUSGELIEFERT");
                        break;

                    case -2:
                        debug_log("Auslieferung Auftrag %d abgelehnt: Bestand nicht ausreichend", auftrag->nummer);
                        maske_fehlermeldung_anzeigen("BESTAND NICHT AUSREICHEND");
                        break;

                    case -1:
                        debug_log("Auslieferung Auftrag %d abgelehnt: Artikel nicht gefunden", auftrag->nummer);
                        maske_fehlermeldung_anzeigen("ARTIKEL NICHT GEFUNDEN");
                        break;

                    default:
                        debug_log("Auslieferung Auftrag %d fehlgeschlagen: Code %d", auftrag->nummer, abbuchen_ergebnis);
                        maske_fehlermeldung_anzeigen("BUCHUNG FEHLGESCHLAGEN");
                        break;
                }
            }
        }
        else if (auftrag_auswahl == ERG_ZURUECK)
        {
            break;
        }
    }
}


void anwendung_init(void)
{
    terminal_init();
    bildschirm_init();
    eingabe_init();

    demo_daten_initialisieren();

    debug_log("Terminal/Bildschirm/Tastatur/Demodaten initialisiert");
}


void anwendung_sitzung(void)
{
    if (maske_start_anzeigen() != ERG_WEITER)
    {
        debug_log("Sitzung abgebrochen: Startbildschirm nicht bestaetigt");
        return;
    }

    if (maske_anmeldung_anzeigen() != ERG_ANGEMELDET)
    {
        debug_log("Sitzung abgebrochen: keine erfolgreiche Anmeldung");
        return;
    }

    for (;;)
    {
        Ergebnis auswahl = maske_hauptmenue_anzeigen();

        switch (auswahl)
        {
            case ERG_LAGER:
                lager_verarbeiten();
                break;

            case ERG_ARTIKEL:
                maske_artikelstamm_anzeigen();
                break;

            case ERG_KUNDE:
                kunde_verarbeiten();
                break;

            case ERG_DATUMZEIT:
                maske_datumzeit_anzeigen();
                break;

            case ERG_AUFTRAG:
                auftrag_bearbeiten();
                break;

            case ERG_ENDE:
                return;

            default:
                break;
        }
    }
}


void anwendung_start(void)
{
    anwendung_init();
    anwendung_sitzung();
}
