/*
 *  Modul ukazatele hádaného slova a výsledku tahu
 *
 *  Zobrazuje hádané slovo s již nalezenými písmeny.
 *  Na pravé straně dále políčko se stavovými hláškami dle
 *  toho, zda byl tah úspěšný nebo neúspěšný.
 *
 *  |                                         |           |
 *  |     >  si_e_ice                         |   ZASAH   |
 *  |                                         |           |
 *
 */


#ifndef UKAZATEL_SLOV_H
#define UKAZATEL_SLOV_H


/* nastaví nové slovo
   k hádání a vynuluje stav */
void ukazatelslov_nastav(char slovo[]);

/* nastaví text v pravém okénku */
void ukazatelslov_hlaska(char slovo[]);

/* hádání písmene ve slově
   vrací počet výskytů znaku */
int ukazatelslov_hadej(int znak);

/* odkryje zbývající písmena
   např. v případě prohry */
void ukazatelslov_odkryj(void);

/* vrátí délku hádaného
   slova ve znacích */
int ukazatelslov_delka(void);

/* vrátí počet zbývajících
   neuhádnutých písmen */
int ukazatelslov_zbyva(void);

/* vrátí true, pokud je celé slovo
   již uhádnuto, jinak false */
bool ukazatelslov_hotovo(void);

/* vykreslí ukazatel slov
   na standardní výstup */
void ukazatelslov_vykresli(void);


#endif
