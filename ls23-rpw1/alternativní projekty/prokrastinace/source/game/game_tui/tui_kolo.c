#include <stdio.h>
#include <string.h>
#include "../../globconf.h"
#include "../../libs/ansi_fmt.h"
#include "./tui_kolo.h"


/* určuje, zda byl modul inicializován */
static bool nastaveno       = false;
/* aktuálně probíhající kolo */
static int probihajici_kolo = 0;
/* celkový počet kol */
static int celkem_kol       = 0;
/* šířka jedné buňky - počet znaků */
static int sirka_bunka      = 0;

void ukazatelkol_nastav(int kolo, int pocet_kol, int sirka_bunky) {

  if (pocet_kol > 0 && kolo > 0 && kolo <= pocet_kol) {
    nastaveno = true;
    probihajici_kolo = kolo;
    celkem_kol       = pocet_kol;
    sirka_bunka      = sirka_bunky;

    nastaveno = (sirka_bunka < (int) (strlen(UKAZATELKOL_SYM_VLEVO) + strlen(UKAZATELKOL_SYM_VPRAVO) + 1))
                  ? false
                  : nastaveno;
  }
  else {
    nastaveno = false;
  }
}


int ukazatelkol_zjisti_kolo(void) {
  return probihajici_kolo;
}


int ukazatelkol_zjisti_pocet(void) {
  return celkem_kol;
}


void ukazatelkol_vykresli(void) {
  /*
   * | >1< |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |
   */

  int i, j;  /* iterátory */

  if (nastaveno == true) {
    putchar('|');

    for (i = 1; i <= celkem_kol; i++) {

      if (i == probihajici_kolo) {
        for (j = 0; j < (int) (sirka_bunka - 1 - strlen(UKAZATELKOL_SYM_VLEVO) - strlen(UKAZATELKOL_SYM_VPRAVO)) / 2; j++) {
          putchar(' ');
        }
        printf(UKAZATELKOL_FORMAT
               #if UKAZATELKOL_BLIKAT == 1
                 ansi_format(ANSI_BLICK)
               #endif
               UKAZATELKOL_SYM_VLEVO
               ansi_format(ANSI_BLICK_OFF));
      }
      else {
        for (j = 0; j < (int) (sirka_bunka - 1) / 2; j++) {
          putchar(' ');
        }
      }

      printf("%d", i);

      if (i == probihajici_kolo) {
        printf(""
               #if UKAZATELKOL_BLIKAT == 1
                 ansi_format(ANSI_BLICK)
               #endif
               UKAZATELKOL_SYM_VPRAVO
               ansi_format(ANSI_RESET));
        for (j = 0; j < (int) (sirka_bunka - 1 - strlen(UKAZATELKOL_SYM_VLEVO) - strlen(UKAZATELKOL_SYM_VPRAVO)) / 2; j++) {
          putchar(' ');
        }
      }
      else {
        for (j = 0; j < (int) (sirka_bunka - 1) / 2; j++) {
          putchar(' ');
        }
      }

      putchar('|');

    }

    /* když je počet kol menší než minimální šířka TUI prvků, je třeba přidat pravé orámování */
    if (celkem_kol < UKAZATELE_MINIMALNI_SIRKA) {
      for (i = ((celkem_kol - 1) * sirka_bunka) - 1; i <= (UKAZATELE_MINIMALNI_SIRKA * sirka_bunka) - celkem_kol + 1; i++) {
        putchar(' ');
      }
      putchar('|');
    }

    putchar('\n');
  }
  else {
    fputs(ERR_SIGN "Modul ukazatele kol neni spravne inicializovan...\n", stderr);
  }
}
