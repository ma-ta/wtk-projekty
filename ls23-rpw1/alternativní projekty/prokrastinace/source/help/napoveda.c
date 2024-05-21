#include <stdio.h>
#include <stdlib.h>
#include "../globconf.h"
#include "../libs/ansi_fmt.h"
#include "../tui/hlavicka.h"
#include "./napoveda.h"

#define napoveda_titulek(strana)  printf(ansi_format(ANSI_INVER)  \
                                         "\nNAPOVEDA  (strana %d/%d)\n\n"  \
                                         ansi_format(ANSI_RESET)  \
                                         , (strana)  \
                                         , NAPOVEDA_OBRAZOVEK);

static FILE *f_napoveda = NULL;

void napoveda(void)
{
  register int c = '\0';
  int cislo_strany = 1;
  bool byla_zarazka = false;

  vymaz_obr();

  /* otevře soubor s nápovědou */
  if ((f_napoveda = fopen(NAPOVEDA_SOUBOR, "r")) == NULL) {
    fprintf(stderr, ERR_SIGN ERR_SOUBOR "\n", NAPOVEDA_SOUBOR);
    printf("\n"
           ansi_format(ANSI_INVER)
           "(Enter pro navrat...)"
           ansi_format(ANSI_RESET));
    cekej_enter();
    vymaz_obr();
    return;
  }

  /* vypne zobrazení kurzoru */
  fputs(ansi_cursor_off(), stdout);

  /* vypíše číslo stránky s nápovědou */
  napoveda_titulek(cislo_strany);

  /* vykreslí záhlaví */
  puts(NAPOVEDA_ZAHLAVI);

  /* vypíše nápovědu na obrazovku */
  while ((c = getc(f_napoveda)) != EOF) {
    if (c == NAPOVEDA_ZARAZKA) {
      byla_zarazka = true;
      /* zobrazí výzvu ke stisknutí enteru */
      printf("\n"
             ansi_format(ANSI_INVER)
             PROMPT_ENTER_POKRAC
             ansi_format(ANSI_RESET));
      cekej_enter();
      cislo_strany++;
      vymaz_obr();
      /* vypíše číslo stránky s nápovědou */
      napoveda_titulek(cislo_strany);
      continue;
    }
    else {
      /* zajistí nezdvojení odřádkování po znaku zarážky */
      if (byla_zarazka && c == '\n') {
        byla_zarazka = false;
        continue;
      }

      putchar(c);
    }
  }

  /* uzavře soubor s nápovědou */
  if (fclose(f_napoveda) == EOF) {
    fprintf(stderr, ERR_SIGN "Soubor napovedy nelze zavrit...\n");
  }
  else {
    f_napoveda = NULL;
  }

  fputs(ansi_format(ANSI_INVER) "\n" PROMPT_ENTER_NAVRAT ansi_format(ANSI_RESET)
        , stdout);
  /* čekání na stisk klávesy enter */
  cekej_enter();
  /* zapne zobrazení kurzoru */
  fputs(ansi_cursor_on(), stdout);

  vymaz_obr();
}
