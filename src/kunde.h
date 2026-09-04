#ifndef D621_KUNDE_H
#define D621_KUNDE_H

#define MAX_KUNDEN 50

typedef struct
{
    char nummer[16];
    char name[40];
    char strasse[40];
    char plz[8];
    char ort[32];
    char telefon[24];
    char ansprechpartner[32];
} Kunde;


void kundenbestand_initialisieren(void);

Kunde *kunde_anlegen(
    const char *nummer,
    const char *name,
    const char *strasse,
    const char *plz,
    const char *ort,
    const char *telefon,
    const char *ansprechpartner
);

Kunde *kunde_finden(
    const char *nummer
);

int kunden_anzahl(void);

Kunde *kunde_at(
    int index
);

#endif
