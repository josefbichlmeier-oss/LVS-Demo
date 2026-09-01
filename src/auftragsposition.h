#ifndef D621_AUFTRAGSPOSITION_H
#define D621_AUFTRAGSPOSITION_H

typedef struct
{
    char artikelnummer[16];
    int menge;
} Auftragsposition;


Auftragsposition auftragsposition_erstellen(
    const char *artikelnummer,
    int menge
);

#endif
