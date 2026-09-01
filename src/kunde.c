#include <stddef.h>
#include <string.h>

#include "kunde.h"


static Kunde kundenbestand[MAX_KUNDEN];

static int kunden_anzahl_wert = 0;


void kundenbestand_initialisieren(void)
{
    kunden_anzahl_wert = 0;

    kunde_anlegen(
        "1001",
        "COMPUTEUM"
    );

    kunde_anlegen(
        "1002",
        "MUSTER GMBH"
    );

    kunde_anlegen(
        "1003",
        "TECHNIK AG"
    );
}


Kunde *kunde_anlegen(
    const char *nummer,
    const char *name
)
{
    if (kunden_anzahl_wert >= MAX_KUNDEN)
        return NULL;


    Kunde *kunde =
        &kundenbestand[kunden_anzahl_wert];


    strncpy(
        kunde->nummer,
        nummer,
        sizeof(kunde->nummer) - 1
    );

    kunde->nummer[
        sizeof(kunde->nummer) - 1
    ] = '\0';


    strncpy(
        kunde->name,
        name,
        sizeof(kunde->name) - 1
    );

    kunde->name[
        sizeof(kunde->name) - 1
    ] = '\0';


    kunden_anzahl_wert++;

    return kunde;
}


Kunde *kunde_finden(
    const char *nummer
)
{
    for (int i = 0; i < kunden_anzahl_wert; i++)
    {
        if (strcmp(
                kundenbestand[i].nummer,
                nummer
            ) == 0)
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
    if (index < 0 ||
        index >= kunden_anzahl_wert)
    {
        return NULL;
    }

    return &kundenbestand[index];
}
