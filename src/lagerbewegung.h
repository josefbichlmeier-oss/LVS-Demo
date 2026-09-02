#ifndef D621_LAGERBEWEGUNG_H
#define D621_LAGERBEWEGUNG_H


typedef enum
{
    LAGER_EINGANG,
    LAGER_AUSGANG

} Lagerbewegungstyp;


typedef struct
{
    char artikelnummer[16];
    int menge;
    Lagerbewegungstyp typ;

} Lagerbewegung;


Lagerbewegung lagerbewegung_erstellen(
    const char *artikelnummer,
    int menge,
    Lagerbewegungstyp typ
);


#endif
