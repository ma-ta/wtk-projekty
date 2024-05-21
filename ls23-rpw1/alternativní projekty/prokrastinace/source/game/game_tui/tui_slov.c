#include "../../globconf.h"
#include "./tui_slov.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "../../libs/ansi_fmt.h"

static int  i, j      = 0;  /* pomocný iterátor */
static bool nastaveno = false;  /* určuje, zda je modul inicializován */

typedef struct {
  char slovo[UKAZATELSLOV_DELKA_MAX + 1];
  bool odkryto[UKAZATELSLOV_DELKA_MAX + 1];
  int  delka;
  int  zbyva;
} HADANE_SLOVO;
static HADANE_SLOVO hadane_slovo = { .slovo[0] = '\0', .odkryto[0] = '\0', .delka = 0, .zbyva = 0 };


static char *hlasky_ano[] = { UKAZATELSLOV_HLASKY_ANO };
static char *hlasky_ne [] = { UKAZATELSLOV_HLASKY_NE  };
static char hlaska[UKAZATELSLOV_HLASKA_MAX] = "";
       int  hlaska_fmt        = (-1);  /* -1: neformátováno, 0: ne, 1: ano */
static int  pocet_hlasek_ano  = 0;
static int  pocet_hlasek_ne   = 0;
static int  stav_nalezeno     = (-1);


void ukazatelslov_nastav(char slovo[])
{
  if (strlen(slovo) > 0 && strlen(slovo) <= UKAZATELSLOV_DELKA_MAX) {

    pocet_hlasek_ano = sizeof(hlasky_ano) / sizeof(hlasky_ano[0]);
    pocet_hlasek_ne  = sizeof(hlasky_ne) / sizeof(hlasky_ne[0]);

    strcpy(hadane_slovo.slovo, slovo);
    for (i = 0; i < (int) (sizeof(hadane_slovo.odkryto) / sizeof(hadane_slovo.odkryto[0])); i++) {
      hadane_slovo.odkryto[i] = false;
    }
    hadane_slovo.delka = strlen(slovo);
    hadane_slovo.zbyva = hadane_slovo.delka;

    for (i = 0; i < hadane_slovo.delka; i++) {
      for (j = 0; j < (int) strlen(UKAZATELSLOV_PRESKOCIT); j++) {
        if (hadane_slovo.slovo[i] == UKAZATELSLOV_PRESKOCIT[j]) {
          hadane_slovo.odkryto[i] = true;
          hadane_slovo.zbyva--;
          break;
        }
      }
    }

    nastaveno = true;
  }
  else {
    nastaveno = false;
    fputs(ERR_SIGN "Modul ukazatele slov nebyl inicializovan...\n", stderr);
  }
}


int ukazatelslov_hadej(int znak)
{
  if (nastaveno) {

    int i        = 0;
    int nalezeno = 0;
    int odecist  = 0;
    char slovo_tolower[UKAZATELSLOV_DELKA_MAX + 1];
    char *p_ch = slovo_tolower;

    /* zkopírování hádaného slova s malými písmeny */
    for (i = 0; i < (int) strlen(hadane_slovo.slovo); i++) {
      slovo_tolower[i] = tolower(hadane_slovo.slovo[i]);
    }
    slovo_tolower[i] = '\0';


    /* hledání vyskytů písmene 'CH' při zadání znaku 'C' */
    #if UKAZATELSLOV_PISMENO_CH == 1
      if (tolower(znak) == 'c') {
        while ((p_ch = strstr(p_ch, "ch")) != NULL) {
          i = p_ch - slovo_tolower;
          if (   hadane_slovo.odkryto[i]     == false 
              && hadane_slovo.odkryto[i + 1] == false)
          {
            nalezeno++;
            odecist += 2;
            hadane_slovo.odkryto[i]     = true;
            hadane_slovo.odkryto[i + 1] = true;
          }
          p_ch++;
        }
      }
    #endif

    /* hledání vyskytů znaku ve slově */
    for (i = 0; i < hadane_slovo.delka; i++) {
      if (   hadane_slovo.odkryto[i]        == false
          && toupper(hadane_slovo.slovo[i]) == toupper(znak))
      {
        #if UKAZATELSLOV_PISMENO_CH == 1
          /* zajistí přeskočení 'H' v rámci písmene 'CH' */
          if (i > 0 && toupper(znak) == 'H') {
            if (toupper(hadane_slovo.slovo[i - 1]) == 'C') {
              continue;
            }
          }
        #endif
        hadane_slovo.odkryto[i] = true;
        nalezeno++;
        odecist++;

      }
    }

    hadane_slovo.zbyva -= (hadane_slovo.zbyva > 0) ? odecist : 0;
    stav_nalezeno       = (nalezeno > 0) ? 1 : 0;

    return nalezeno;

  }
  else {
    fputs(ERR_SIGN "Modul ukazatele slov nebyl inicializovan...\n", stderr);
    stav_nalezeno = (-1);
    return (-1);
  }
}

void ukazatelslov_hlaska(char *retezec)
{
  if (strlen(retezec) < UKAZATELSLOV_HLASKA_MAX) {
    strncpy(hlaska, (strlen(retezec) < 1) ? " " : retezec, sizeof(hlaska));
  }
  else {
    fputs(ERR_SIGN "Hlaska je prilis dlouha...\n", stderr);
  }

  /* (???) z neznámé příčiny dříve uvedeno zde
     u v1.0.0 přesunuto na konec ukazatelslov_vykresli() */
  /*stav_nalezeno = -1;*/
}

void ukazatelslov_vykresli(void)
{
  int pocet_mezer = ((UKAZATELE_SIRKA_BUNKY + 1) * ((POCET_KOL < UKAZATELE_MINIMALNI_SIRKA) ? UKAZATELE_MINIMALNI_SIRKA : POCET_KOL)) - 1;

  if (nastaveno) {

    /* přednastavení náhodné hlášky */
    if (stav_nalezeno == 1) {
      ukazatelslov_hlaska(hlasky_ano[rand() % pocet_hlasek_ano]);
      hlaska_fmt = 1;
    }
    else if (stav_nalezeno == 0) {
      ukazatelslov_hlaska(hlasky_ne[rand() % pocet_hlasek_ne]);
      hlaska_fmt = 0;
    }

    /* první řádek */

    putchar('|');
    for (i = 0; i < pocet_mezer; i++) {
      if (i == pocet_mezer - (UKAZATELE_SIRKA_BUNKY * 2) - 2)
        putchar('|');
      else
        putchar(' ');
    }
    puts("|");

    /* druhý řádek */

    fputs("|     " UKAZATELSLOV_PROMPT, stdout);
    /* vypíše hádanku */
    for (i = 0; i < hadane_slovo.delka; i++) {
      if (hadane_slovo.odkryto[i])
        putchar((UKAZATELSLOV_VELKA) ? toupper(hadane_slovo.slovo[i]) : hadane_slovo.slovo[i]);
      else
        putchar(UKAZATELSLOV_MASKA);
    }
    /* vypíše rámeček s hláškou */
    for (i = 0; i < (int) (pocet_mezer - 5 - strlen(UKAZATELSLOV_PROMPT) - hadane_slovo.delka); i++) {
      if ((int) (i + 5 + strlen(UKAZATELSLOV_PROMPT) + hadane_slovo.delka) == pocet_mezer - (UKAZATELE_SIRKA_BUNKY * 2) - 2) {
        putchar('|');
        for (j = 0; j < (int) ((((UKAZATELE_SIRKA_BUNKY * 2) - strlen(hlaska)) / 2) + 1); j++) {
          putchar(' ');
        }

/* slouží k obarvení hlášky
   TODO: přendat do fce. ukazatelslov_hlaska() a tu rozšířit o parametr fmt */
#if UKAZATELE_BARVY == 1
        if (hlaska_fmt == (-1))
          ;  /* prázdný příkaz - např. při začátku hry */
        else if (hlaska_fmt == 0)
          fputs(UKAZATELSLOV_HLASKA_FMT_NE, stdout);
        else
          fputs(UKAZATELSLOV_HLASKA_FMT_ANO, stdout);
#endif

        fputs(hlaska, stdout);

#if UKAZATELE_BARVY == 1
        if (hlaska_fmt != (-1))
          fputs(ansi_format(ANSI_RESET), stdout);
#endif

        for (j = 0; j < (int) ((((UKAZATELE_SIRKA_BUNKY * 2) - strlen(hlaska)) / 2) + 1); j++) {
          putchar(' ');
        }
        break;
      }
      else
        putchar(' ');
    }
    puts("|");

    /* třetí řádek */

    putchar('|');
    for (i = 0; i < pocet_mezer; i++) {
      if (i == pocet_mezer - (UKAZATELE_SIRKA_BUNKY * 2) - 2)
        putchar('|');
      else
        putchar(' ');
    }
    puts("|");
  }
  else {
    fputs(ERR_SIGN "Modul ukazatele slov nebyl inicializovan...\n", stderr);
  }

  stav_nalezeno = -1;
}


int ukazatelslov_delka(void)
{
  if (nastaveno) {
    return hadane_slovo.delka;
  }
  else {
    fputs(ERR_SIGN "Modul ukazatele slov nebyl inicializovan...\n", stderr);
    return 0;
  }
}


int ukazatelslov_zbyva(void)
{
  if (nastaveno) {
    return hadane_slovo.zbyva;
  }
  else {
    fputs(ERR_SIGN "Modul ukazatele slov nebyl inicializovan...\n", stderr);
    return 0;
  }
}

void ukazatelslov_odkryj(void)
{
  register int i = 0;

  if (nastaveno) {
    for (i = 0; i < hadane_slovo.delka; i++) {
      hadane_slovo.odkryto[i] = true;
    }
    for (i = 0; i < hadane_slovo.delka; i++) {
      hadane_slovo.slovo[i] = toupper(hadane_slovo.slovo[i]);
    }
  }
}

bool ukazatelslov_hotovo(void) {
  if (nastaveno) {
    if (hadane_slovo.zbyva <= 0) {
      return true;
    }
    else {
      return false;
    }
  }
  else {
    fputs(ERR_SIGN "Modul ukazatele slov nebyl inicializovan...\n", stderr);
    return false;
  }
}
