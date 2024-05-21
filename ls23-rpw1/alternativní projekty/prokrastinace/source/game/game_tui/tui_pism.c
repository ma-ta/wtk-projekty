#include <stdio.h>
#include <ctype.h>
#include "../../globconf.h"
#include "./game_tui.h"


/* určuje, zda byl modul inicializován */
static bool nastaveno = false;
/* počet písmen na řádku před zalomením */
static int delka_radek = 0;
/* šířka jedné buňky - počet znaků */
static int sirka_bunka = 0;
/* slouží k označení již použitých písmen */
static char dostupna_pismena[UKAZATELPISMEN_DOSTUPNA_PISMENA_SIZE];
static int  pocet_pismen = UKAZATELPISMEN_DOSTUPNA_PISMENA_SIZE;


void ukazatelpismen_nastav
(int delka_radku, int sirka_bunky)
{
  delka_radek = (delka_radku < UKAZATELE_MINIMALNI_SIRKA) ? UKAZATELE_MINIMALNI_SIRKA : delka_radku;
  sirka_bunka = sirka_bunky;

  /* naplnění pole nepoužitých znaků */
  ukazatelpismen_dostupna_pismena_napln(dostupna_pismena);

  nastaveno = true;
}

bool ukazatelpismen_vydej
(int znak)
{
  int zn = toupper(znak);
  int i;

  for (i = 0; i < UKAZATELPISMEN_DOSTUPNA_PISMENA_SIZE; i++) {
    if (toupper((int) dostupna_pismena[i]) == zn) {
      dostupna_pismena[i] = UKAZATELPISMEN_NIC;  /* označí znak jako použitý */
      return true;
    }
  }

  return false;
}

void ukazatelpismen_vykresli(void)
{
  if (nastaveno) {
    int i, j,
        mezery = (sirka_bunka - 1) / 2;


    ukazatele_oramuj(delka_radek, sirka_bunka);
    for (i = 0; i < pocet_pismen; i++) {
      if (i != 0 && i % delka_radek == 0) {
        puts("|");
        ukazatele_oramuj(delka_radek, sirka_bunka);
      }
      putchar('|');
      for (j = 0; j < mezery; j++)  putchar(' ');

      /* vypíše znak nebo prázdné místo */
      putchar((dostupna_pismena[i] != UKAZATELPISMEN_NIC)
                ? dostupna_pismena[i]
                : ' ');

      for (j = 0; j < mezery; j++)  putchar(' ');
    }
    puts("|");
    ukazatele_oramuj((pocet_pismen % delka_radek)
                      ? pocet_pismen % delka_radek
                      : delka_radek, sirka_bunka);
  }
  else {
    fputs(ERR_SIGN "Modul ukazatele slov neni spravne inicializovan...\n", stderr);
  }
}
