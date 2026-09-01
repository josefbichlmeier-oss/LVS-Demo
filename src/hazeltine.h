#ifndef D621_HAZELTINE_H
#define D621_HAZELTINE_H

int hazeltine_oeffnen(const char *geraet);
void hazeltine_schliessen(void);

void hazeltine_loeschen(void);
void hazeltine_position(int x, int y);

void hazeltine_hell(void);
void hazeltine_dunkel(void);

void hazeltine_schreiben(const char *text);

#endif
