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
#include "maske_fehlermeldung.h"
#include "maske_meldung.h"


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
                maske_meldung_anzeigen("BUCHUNG DURCHGEFUEHRT");
            }
            else if (buchung == ERG_NICHT_GEFUNDEN)
            {
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
                maske_meldung_anzeigen("BUCHUNG DURCHGEFUEHRT");
            }
            else if (buchung == ERG_NICHT_GEFUNDEN)
            {
                maske_fehlermeldung_anzeigen("ARTIKEL NICHT GEFUNDEN");
            }
            else if (buchung == ERG_BESTAND_UNZUREICHEND)
            {
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
                        maske_meldung_anzeigen("AUFTRAG AUSGELIEFERT");
                        break;

                    case -5:
                        maske_fehlermeldung_anzeigen("AUFTRAG BEREITS AUSGELIEFERT");
                        break;

                    case -2:
                        maske_fehlermeldung_anzeigen("BESTAND NICHT AUSREICHEND");
                        break;

                    case -1:
                        maske_fehlermeldung_anzeigen("ARTIKEL NICHT GEFUNDEN");
                        break;

                    default:
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
}


void anwendung_sitzung(void)
{
    if (maske_start_anzeigen() != ERG_WEITER)
    {
        return;
    }

    if (maske_anmeldung_anzeigen() != ERG_ANGEMELDET)
    {
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
