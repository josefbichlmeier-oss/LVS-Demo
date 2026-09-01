#ifndef D621_BILDSCHIRM_H
#define D621_BILDSCHIRM_H

void bildschirm_initialisieren(void);
void bildschirm_loeschen(void);

void bildschirm_schreiben(
    int x,
    int y,
    const char *text
);

void bildschirm_cursor(
    int x,
    int y
);

void bildschirm_ausgeben(void);

#endif
