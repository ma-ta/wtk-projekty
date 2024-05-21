#include <stdio.h>
#include <ctype.h>
#include "../../globconf.h"
#include "./game_tui.h"


void ukazatele_vykresli(void)
{
  ukazatelsibenice_vykresli();
  putchar('\n');
  ukazatele_oramuj((POCET_KOL < UKAZATELE_MINIMALNI_SIRKA) ? UKAZATELE_MINIMALNI_SIRKA : POCET_KOL, UKAZATELE_SIRKA_BUNKY);
  ukazatelkol_vykresli();
  ukazatele_oramuj((POCET_KOL < UKAZATELE_MINIMALNI_SIRKA) ? UKAZATELE_MINIMALNI_SIRKA : POCET_KOL, UKAZATELE_SIRKA_BUNKY);
  ukazatelslov_vykresli();
  ukazatelpismen_vykresli();
}
