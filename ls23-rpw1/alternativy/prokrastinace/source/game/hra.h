/*
 *  Spouští hru, řídí její průběh a vykresluje herní
 *  obrazovku pomocí modulů ve složce game_tui.
 *  Vrací dosažené skóre a v případě výhry zajišťuje
 *  zápis hráče do databáze se statistikami.
 *
 */

#ifndef HRA_H
#define HRA_H

/* inicializuje modul hra */
void hra_nastav(int kol, int zivotu);

/* spustí hru a vrátí
   dosažené skóre */
int hra_start(void);

/* uvolní dynamicky alokovanou paměť */
void hra_vycisti(void);

/* zobrazí výsledek hry a případně
   zapíše skóre do databáze */
void hra_vysledek(int skore);

#endif
