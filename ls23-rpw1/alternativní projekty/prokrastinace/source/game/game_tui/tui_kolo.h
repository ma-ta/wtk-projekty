/*
 *  Ukazatel aktuálně probíhajícího kola hry
 *
 *  Vykresluje následující ukazatel
 *  | >1< |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |
 *
 */


#ifndef UKAZATEL_KOL_H
#define UKAZATEL_KOL_H


/* nastaví aktuální kolo
   a celkový počet kol */
void ukazatelkol_nastav
(int kolo, int pocet_kol, int sirka_bunky);

/* vrátí aktuálně probíhající
   kolo hry */
int  ukazatelkol_zjisti_kolo(void);

/* vrátí celkový počet
   kol hry */
int  ukazatelkol_zjisti_pocet(void);

/* vykreslí ukazatel
   probíhajícího kola hry */
void ukazatelkol_vykresli(void);


#endif
