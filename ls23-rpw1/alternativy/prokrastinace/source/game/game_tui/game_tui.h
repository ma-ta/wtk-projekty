/*
 *  Zajišťuje vykreslení uživatelského rozhraní hry
 *  (kompletuje ukazatele z nižších modulů game_tui)
 *
 */


#ifndef UKAZATELE_H
#define UKAZATELE_H

#include "tui_kolo.h"
#include "tui_pism.h"
#include "tui_sibe.h"
#include "tui_slov.h"

#define ukazatele_oramuj(pocet_bunek, sirka_bunky)  {  \
                                                       int i, c = 0;  \
                                                       int znaku = (pocet_bunek) * (sirka_bunky + 1);  \
                                                       \
                                                       putchar('+');  \
                                                       for (i = 1; i <= znaku; i++) {  \
                                                         c = (i % ((sirka_bunky) + 1) == 0 || i == znaku)  \
                                                               ? UKAZATELE_ORAMOVANI_KRIZENI_ZN  \
                                                               : UKAZATELE_ORAMOVANI_ZN;  \
                                                         putchar(c);  \
                                                       }  \
                                                       putchar('\n');  \
                                                    }



/* vykreslí panel z ukazateli
   na standardní výstup */
void ukazatele_vykresli(void);



#endif
