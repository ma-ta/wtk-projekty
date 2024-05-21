#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../globconf.h"
#include "./men_glob.h"
#include "../tui/hlavicka.h"
#include "../libs/ansi_fmt.h"

static char *polozky_menu[] = { MENU_POLOZKY };
static int i;  /* pomocné iterátory */

VOLBY_MENU menu(void)
{
  const char *menu_nadpis = MENU_NADPIS;
  VOLBY_MENU volba  = -1;
  char volba_s[3]   = "";
  int pocet_voleb   = sizeof(polozky_menu) / sizeof(polozky_menu[0]);
  int pocet_mezer_l = (MENU_SIRKA - strlen(menu_nadpis) - strlen(MENU_NADPIS_L)
                       - strlen(MENU_NADPIS_L) - 1) / 2;
  int pocet_mezer_p = (MENU_SIRKA - strlen(menu_nadpis) - strlen(MENU_NADPIS_P)
                       - strlen(MENU_NADPIS_P) - 1) / 2;


  hlavicka_vykresli(TUI_HLAVICKA_TXT_L, TUI_HLAVICKA_TXT_P);
  putchar('\n');

  /* vypíše položky menu */

  /* první řádek */
  menu_oramuj(UKAZATELE_ORAMOVANI_KRIZENI_ZN, UKAZATELE_ORAMOVANI_ZN, MENU_SIRKA);
  putchar('|');
  if ((strlen(menu_nadpis) + strlen(MENU_NADPIS_L) + strlen(MENU_NADPIS_P)) > MENU_SIRKA - 2) {
    fputs("   ", stdout);  fflush(stdout);
    fputs(ERR_SIGN ERR_MENU_NADPIS_TXTMAX, stderr);
    for (i = 0; i < (int) (MENU_SIRKA - 2 - strlen(ERR_MENU_NADPIS_TXTMAX) - 7); i++)  putchar(' ');
  }
  else if (((MENU_SIRKA - 2) % 2 == 0) != ((strlen(menu_nadpis) + strlen(MENU_NADPIS_L) + strlen(MENU_NADPIS_P)) % 2 == 0)) {
    fputs("   ", stdout);  fflush(stdout);
    fputs(ERR_SIGN ERR_MENU_NADPIS_ZAROV, stderr);
    for (i = 0; i < (int) (MENU_SIRKA - 2 - strlen(ERR_MENU_NADPIS_ZAROV) - 7); i++)  putchar(' ');
  }
  else {
    for (i = 0; i < pocet_mezer_l / 2; i++)  putchar(' ');
    fputs(MENU_NADPIS_L, stdout);
    for (i = 0; i < pocet_mezer_l / 2; i++)  putchar(' ');
    fputs(menu_nadpis, stdout);
    for (i = 0; i < pocet_mezer_p / 2; i++)  putchar(' ');
    fputs(MENU_NADPIS_P, stdout);
    for (i = 0; i < pocet_mezer_p / 2; i++)  putchar(' ');
  }
  puts("|");
  menu_oramuj(UKAZATELE_ORAMOVANI_KRIZENI_ZN, UKAZATELE_ORAMOVANI_ZN, MENU_SIRKA);
  /* vypsání položek */
  for (i = 0; i < pocet_voleb; i++) {
    menu_oramuj('|', ' ', MENU_SIRKA);
    menu_polozka(i + 1, polozky_menu[i], MENU_POLOZKY_CAPS);
  }
  /* poslední dva řádky tabulky s položkami menu */
  menu_oramuj('|', ' ', MENU_SIRKA);
  menu_oramuj('+', '-', MENU_SIRKA);

  /* načtení volby od uživatele */

  /* while (volba < (VOLBY_MENU) 1 || volba > (VOLBY_MENU) pocet_voleb) { */
    fputs("    [   ]   <  " MENU_ZADEJ, stdout);
    for (i = 0; i < (int) (strlen(MENU_ZADEJ) + 9); i++)  putchar('\b');
    scanf("%2s", volba_s);
    cekej_enter();  /* vymazání vstupního bufferu */
    volba = (VOLBY_MENU) atoi(volba_s);
    if (volba < (VOLBY_MENU) 1 || volba > (VOLBY_MENU) pocet_voleb) {
      printf("      |\n      +--> "
            ansi_format(ANSI_INVER) MENU_ZADEJ_ERR ansi_format(ANSI_RESET)
            "  " HRA_PROPOKRACOVANI
            , 1, pocet_voleb);
      cekej_enter();
    }
  /* } */


  return ((volba < (VOLBY_MENU) 0 || volba > (VOLBY_MENU) pocet_voleb) ? 0 : volba);
}
