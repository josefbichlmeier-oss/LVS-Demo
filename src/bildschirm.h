#ifndef D621_BILDSCHIRM_H
#define D621_BILDSCHIRM_H

#define BILDSCHIRMBREITE 74
#define BILDSCHIRMHOEHE 27

void bildschirm_loeschen(void);

void bildschirm_text(
    int x,
    int y,
    const char *text
);

void bildschirm_ausgeben(void);

#endif
