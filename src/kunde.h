#ifndef D621_KUNDE_H
#define D621_KUNDE_H

#define MAX_KUNDEN 50

typedef struct
{
    char nummer[16];
    char name[64];
} Kunde;


void kundenbestand_initialisieren(void);

Kunde *kunde_anlegen(
    const char *nummer,
    const char *name
);

Kunde *kunde_finden(
    const char *nummer
);

int kunden_anzahl(void);

Kunde *kunde_at(
    int index
);

#endif
