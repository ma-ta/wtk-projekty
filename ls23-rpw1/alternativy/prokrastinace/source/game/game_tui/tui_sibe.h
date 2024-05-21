/*
 *  Modul ukazatele (obrázku) šibenice s tabulkou
 *  zbývajících životů a celkovým skóre
 *
 *  Vykresluje šibenici se stavovou tabulkou hry.
 *  V režimu DOS je zobrazena zjednodušená (prostorově úspornější)
 *  tabulka a šibenice se vykreslí na samostatné obrazovce.
 *
 */


#ifndef UKAZATEL_SIBENICE_H
#define UKAZATEL_SIBENICE_H


void
ukazatelsibenice_nastav(int zivoty, int body);

void
ukazatelsibenice_vycisti(void);


int
ukazatelsibenice_zjisti_zivoty(void);

int
ukazatelsibenice_zjisti_body(void);

void
ukazatelsibenice_vykresli(void);


#endif
