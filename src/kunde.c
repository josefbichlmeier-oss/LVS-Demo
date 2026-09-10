#include <stddef.h>
#include <string.h>

#include "kunde.h"


static Kunde kundenbestand[MAX_KUNDEN];

static int kunden_anzahl_wert = 0;


static void feld_setzen(char *ziel, size_t ziel_groesse, const char *quelle)
{
    strncpy(ziel, quelle, ziel_groesse - 1);
    ziel[ziel_groesse - 1] = '\0';
}


void kundenbestand_initialisieren(void)
{
    kunden_anzahl_wert = 0;

    kunde_anlegen(
        "1000", "COMPUTEUM",
        "DONAUGASSE 8", "94474", "VILSHOFEN",
        "08541 / 96 84 777", "JOSEF BICHLMEIER"
    );

    kunde_anlegen(
        "1001", "SCHMIDT MASCHINENBAU",
        "WERKSTRASSE 15", "80331", "MUENCHEN",
        "089 / 123456", "HERR MUELLER"
    );

    kunde_anlegen(
        "1002", "MUSTER GMBH",
        "INDUSTRIESTRASSE 7", "94032", "PASSAU",
        "0851 / 12345", "FRAU WEBER"
    );

    kunde_anlegen(
        "1003", "ELCODATA GMBH",
        "BAHNHOFSTRASSE 8", "94469", "DEGGENDRF",
        "0991 / 32168", "FRAU VOGL"
    );

    kunde_anlegen(
        "1004", "HUBER OHG",
        "PASSAUERSTRASSE 23", "94474", "VILSHOFEN",
        "08541 / 984711", "HERR KUMPFMUELLER"
    );
}


Kunde *kunde_anlegen(
    const char *nummer,
    const char *name,
    const char *strasse,
    const char *plz,
    const char *ort,
    const char *telefon,
    const char *ansprechpartner
)
{
    if (kunden_anzahl_wert >= MAX_KUNDEN)
        return NULL;


    Kunde *kunde =
        &kundenbestand[kunden_anzahl_wert];

    feld_setzen(kunde->nummer,          sizeof(kunde->nummer),          nummer);
    feld_setzen(kunde->name,            sizeof(kunde->name),            name);
    feld_setzen(kunde->strasse,         sizeof(kunde->strasse),         strasse);
    feld_setzen(kunde->plz,             sizeof(kunde->plz),             plz);
    feld_setzen(kunde->ort,             sizeof(kunde->ort),             ort);
    feld_setzen(kunde->telefon,         sizeof(kunde->telefon),         telefon);
    feld_setzen(kunde->ansprechpartner, sizeof(kunde->ansprechpartner), ansprechpartner);

    kunden_anzahl_wert++;

    return kunde;
}


Kunde *kunde_finden(
    const char *nummer
)
{
    for (int i = 0; i < kunden_anzahl_wert; i++)
    {
        if (strcmp(kundenbestand[i].nummer, nummer) == 0)
        {
            return &kundenbestand[i];
        }
    }

    return NULL;
}


int kunden_anzahl(void)
{
    return kunden_anzahl_wert;
}


Kunde *kunde_at(
    int index
)
{
    if (index < 0 || index >= kunden_anzahl_wert)
        return NULL;

    return &kundenbestand[index];
}
