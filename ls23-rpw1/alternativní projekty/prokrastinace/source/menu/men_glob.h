/*
 *  Zajišťuje vykreslení a obsluhu hlavního menu
 *
 */


#ifndef MENU_H
#define MENU_H

typedef enum {
  MENU_ENUM
} VOLBY_MENU;

#define menu_oramuj(zn_okraj, zn_cara, sirka)  {  register int i = 0;  \
                                                  \
                                                  putchar(zn_okraj);  \
                                                  for (i = 2; i < (sirka); i++) {  \
                                                    putchar(zn_cara);  \
                                                  }  \
                                                  putchar(zn_okraj);  \
                                                  putchar('\n');  \
                                               }
#define menu_polozka(cislo, nazev, caps)  {  const int mezer = 3;  \
                                             register int i1 = 0;  \
                                             register char *p_znak = nazev;  \
                                             \
                                             putchar('|');  \
                                             for (i1 = 0; i1 < mezer; i1++)  putchar(' ');  \
                                             printf("[ %d ]", cislo);  \
                                             for (i1 = 0; i1 < mezer; i1++)  putchar(' ');  \
                                             while (*p_znak != '\0') {  \
                                               putchar((caps) ? toupper(*p_znak) : *p_znak);  \
                                               putchar(' ');  \
                                               p_znak++;  \
                                             }  \
                                             putchar('\b');  \
                                             for (i1 = 0; i1 < (int) (MENU_SIRKA - ((strlen(nazev) * 2) + (mezer * 2) + 5) - 1); i1++)  {  \
                                               putchar(' ');  \
                                             }  \
                                             puts("|");  \
                                          }


VOLBY_MENU menu(void);


#endif
