#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../globconf.h"
#include "../../libs/ansi_fmt.h"
#include "./game_tui.h"

/* určuje způsob zobrazovani skóre */
extern int nastaveni_tabskore;

/* zbývající životy */
static int zbyvajici_zivoty = 0;
/* počet získaných bodů */
static int celkove_body     = 0;
/* pole s obrázky šibenice */
static char *sibenice_obr[POCET_ZIVOTU + 1];
/* informuje, zda je modul inicializován */
static bool nastaveno       = false;
/* stavová proměnná pro fci vykresli_tabskore() */
static bool tabskore_obr = false;


/* soukromé funkce */

static bool ukazatelsibenice_nahrajobr(void)
{
  FILE *f_sibenice = NULL;
  char nactena_cast[10000] = "";
  int cislo_obrazku = POCET_ZIVOTU;
  int c = 0;
  char s_c[2] = "";

  if ((f_sibenice = fopen(UKAZATELSIBENICE_SOUBOR, "r")) == NULL) {
    fprintf(stderr, ERR_SIGN ERR_SOUBOR "\n", UKAZATELSIBENICE_SOUBOR);
    return false;
  }

  while ((c = getc(f_sibenice)) != EOF && cislo_obrazku < (int) (sizeof(sibenice_obr) / sizeof(sibenice_obr[0]))) {
    if (c == UKAZATELSIBENICE_ZARAZKA) {
      if ((sibenice_obr[cislo_obrazku] = (char *) malloc(strlen(nactena_cast) + 1)) == NULL) {
        fputs(ERR_SIGN "Nedostatek pameti pro obrazky...\n", stderr);
        return false;
      }
      strcpy(sibenice_obr[cislo_obrazku], nactena_cast);
      cislo_obrazku--;
      *nactena_cast = '\0';

      while ((c = getc(f_sibenice)) != '\n' && c != EOF)
        ;
    }
    else {
      *s_c = c;
      strcat(nactena_cast, s_c);
    }
  }

  if (fclose(f_sibenice) == EOF) {
    fputs(ERR_SIGN "Soubor s obrazky sibenice nelze zavrit...\n", stderr);
  }


  return true;
}


/* veřejné funkce */


/* vykreslí obrázek s šibenicí
   a hodnotami skóre */
void vykresli_sibenici(void)
{
   printf((const char *) sibenice_obr[zbyvajici_zivoty]

          #if ANSI_FORMAT == 1
            , (zbyvajici_zivoty > UKAZATELSIBE_ZIVOT_LOW)
                ? UKAZATELSIBE_ZIVOT_FMT
                : UKAZATELSIBE_ZIVOT_LOW_FMT
            , ansi_format(ANSI_RESET)
            , UKAZATELSIBE_BODY_FMT
            , ansi_format(ANSI_RESET)
            , (zbyvajici_zivoty > UKAZATELSIBE_ZIVOT_LOW)
                ? UKAZATELSIBE_ZIVOT_FMT
                : UKAZATELSIBE_ZIVOT_LOW_FMT
          #else
            , ""
            , ""
            , ""
            , ""
            , ""
          #endif

          , zbyvajici_zivoty

          #if ANSI_FORMAT == 1
            , ansi_format(ANSI_RESET)
            , UKAZATELSIBE_BODY_FMT
          #else
            , ""
            , ""
          #endif

          , celkove_body

          #if ANSI_FORMAT == 1
            , ansi_format(ANSI_RESET)
          #else
            , ""
          #endif
  );
}

/* vykreslí tabulku
   s hodnotami skóre */
void vykresli_tabskore(bool vykreslit_obr)
{
  /* nové řešení */
  /*
  +--------+
  | ZIVOTY |
  | / BODY |
  |--------|    <------<<<<   S * K * O * R * E
  | 11 /   |
  |   / 00 |
  +--------+
  */

  /* vykreslí samostatnou obrazovku s šibenicí při ztrátě života */
  if (vykreslit_obr) {
    vykresli_sibenici();
    fputs(ansi_cursor_off(), stdout);
    fputs("\n\n" ansi_format(ANSI_INVER) "Prisel jsi o zivot!" ansi_format(ANSI_RESET)
          "  " HRA_PROPOKRACOVANI
          , stdout);
    cekej_enter();
    fputs(ansi_cursor_on(), stdout);
    vymaz_obr();
  }

  /* vykreslí ukazatel - tabulku se skóre */
  ukazatele_oramuj(1, 8);
  printf(
    "| %sZIVOTY%s |\n"
    "| / BODY |\n"
    "|--------|    <------<<<<   S * K * O * R * E\n"
    "| %s%02d%s /   |\n"
    "|   / %02d |\n"

#if ANSI_FORMAT == 1
    , (zbyvajici_zivoty > UKAZATELSIBE_ZIVOT_LOW)
        ? UKAZATELSIBE_ZIVOT_FMT
        : UKAZATELSIBE_ZIVOT_LOW_FMT
    , ansi_format(ANSI_RESET)
#else
    , ""
    , ""
#endif
#if ANSI_FORMAT == 1
    , (zbyvajici_zivoty > UKAZATELSIBE_ZIVOT_LOW)
        ? UKAZATELSIBE_ZIVOT_FMT
        : UKAZATELSIBE_ZIVOT_LOW_FMT
#else
    , ""
#endif
    , zbyvajici_zivoty
#if ANSI_FORMAT == 1
    , ansi_format(ANSI_RESET)
#else
    , ""
#endif
    , celkove_body
  );
  ukazatele_oramuj(1, 8);

}


/* veřejné funkce */

void ukazatelsibenice_vycisti(void)
{
  register int i = 0;

  for (i = 0; i < (int) (sizeof(sibenice_obr) / sizeof(sibenice_obr[0])); i++) {
    free((void *) sibenice_obr[i]);
  }
}

void ukazatelsibenice_nastav(int zivoty, int body)
{
  tabskore_obr = (zivoty < zbyvajici_zivoty) ? true : false;
  zbyvajici_zivoty = zivoty;
  celkove_body     = body;
  

  if (!nastaveno) {
    if (!ukazatelsibenice_nahrajobr()) {
      nastaveno = false;
      return;
    }
  }

  nastaveno = true;
}

int ukazatelsibenice_zjisti_zivoty(void) {
  return zbyvajici_zivoty;
}

int ukazatelsibenice_zjisti_body(void) {
  return celkove_body;
}


/* vykreslování hodnot skóre na obrazovku
   pomocí šibenice nebo tabulky */
void ukazatelsibenice_vykresli(void) {
  
  if (nastaveno) {
    if (!nastaveni_tabskore) {
      vykresli_sibenici();
    }
    else {
      vykresli_tabskore(tabskore_obr);
      tabskore_obr = false;
    }
  }
  else {
    fputs(ERR_SIGN "Modul sibenice neni spravne inicializovan...\n\n", stderr);
    vykresli_tabskore(false);
  }
}
