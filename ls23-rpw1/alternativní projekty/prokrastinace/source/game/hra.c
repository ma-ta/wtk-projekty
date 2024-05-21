#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../globconf.h"
#include "./game_tui/game_tui.h"
#include "./hra.h"
#include "../libs/ansi_fmt.h"
#include "../tui/hlavicka.h"
#include "../help/napoveda.h"
#include "../stats/stats.h"


typedef enum {
  HRA_VOLBY
} ZVLASTNI_VOLBY;
static char *volby_seznam[] = { HRA_VOLBY_SZN };  /* popisky zvláštních voleb */
static int  volby_hodnoty[] = { HRA_VOLBY_HODNOTY };
static FILE *f_slova = NULL;  /* soubor se slovy k hádání */
static char *slova[HRA_POCETSLOV];  /* dynamické pole pro uložení slov ze souboru */
bool slova_nactena = false;

extern int hlaska_fmt;            /* slouží provizorně k resetování formátu hlášky v modulu tui_slov.c */

static int hra_probiha  = false;
static int pocet_kol    = 0;
static int kolo_hry     = 0;
static int celkem_bodu  = 0;
static int pocet_zivotu = 0;
static int zbyva_zivotu = 0;


/* hlavičky lokálních funkcí */
static int hra_kolo(void);
static bool nacti_slova(void);


/* veřejné funkce */

void hra_vysledek(int skore)
{
  int umisteni = 0;  /* pro uložení pozice z stats_zpracuj_body() */

  /* započítání herního času */
  stats_zpracuj_cas(true, (skore > 0) ? true : false);

  hlavicka_vykresli(TUI_HLAVICKA_TXT_L, TUI_HLAVICKA_TXT_P);
  puts("\n");

  fputs("   >   " HRA_HLASKA_FORMAT, stdout);
  /* výhra */
  if (skore > 0) {
    printf(HRA_HLASKA_VYHRA, skore);
    fputs(ansi_format(ANSI_RESET), stdout);
    /* hráč se umístil na jednom z TOP míst */
    if ((umisteni = stats_zpracuj_body(skore)) > 0) {
      fputs("\n       ", stdout);
      if (umisteni == 1)  puts("To je "
                               ansi_format(ANSI_BLICK)
                               ansi_format(ANSI_BOLD)
                               "nejlepsi"
                               ansi_format(ANSI_RESET)
                               " dosazeny vysledek !");
      else                printf("To je "
                                 ansi_format(ANSI_BOLD)
                                 "%d. nejlepsi"
                                 ansi_format(ANSI_RESET)
                                 " vysledek v poradi !\n", umisteni);
      puts("\n\n" HRA_OBR_VYHRA);
      fputs("\n\n       ", stdout);
      printf(ansi_format(ANSI_BOLD)
             "Uved sve jmeno do kroniky:  "
             ansi_format(ANSI_RESET));
      stats_zadej_jmeno(umisteni);
      vymaz_obr();
      stats_vypis(false);
      return;
    }
    /* dosažené skóre není významné */
    else {
      printf("\n       (Zatim nejvyssi dosazene skore je %d b...)\n", stats_zjisti_nte_nejbody(1));
      puts("\n\n" HRA_OBR_VYHRA);
    }
  }
  /* prohra */
  else {
    fputs(HRA_HLASKA_PROHRA, stdout);
    fputs(ansi_format(ANSI_RESET), stdout);
    puts("\n\n\n" HRA_OBR_PROHRA);
  }

  /* čekání na stisk klávesy Enter */
  fputs("\n\n   " HRA_PROPOKRACOVANI, stdout);
  cekej_enter();
  vymaz_obr();
}


void hra_vycisti(void)
{
  register int i = 0;

  for (i = 0; i < (int) (sizeof(slova) / sizeof(slova[0])); i++) {
    free((void *) slova[i]);
  }
}

void hra_nastav(int kol, int zivotu) {
  pocet_kol    = kol;
  kolo_hry     = 1;
  celkem_bodu  = 0;
  pocet_zivotu = zivotu;
  zbyva_zivotu = zivotu;
  hlaska_fmt   = -1;      /* reset (odbarvení) formátu hlášky před novou hrou */

  if (!nacti_slova()) {
    hra_probiha = false;
    fputs(ERR_SIGN "Hru nelze spustit.\n", stderr);
    fputs(ansi_format(ANSI_INVER) "\n(Enter pro ukonceni...)" ansi_format(ANSI_RESET), stdout);
    cekej_enter();
    vymaz_obr();
    konec();
    exit(1);
  }

  ukazatelsibenice_nastav(zbyva_zivotu, celkem_bodu);
  ukazatelkol_nastav(kolo_hry, pocet_kol, UKAZATELE_SIRKA_BUNKY);
  #if (DEBUG == 2)
    ukazatelslov_nastav(DEBUG_HADANE_SLOVO);
  #else
    ukazatelslov_nastav(slova[rand() % (sizeof(slova) / sizeof(slova[0]))]);
  #endif
  ukazatelpismen_nastav(pocet_kol, UKAZATELE_SIRKA_BUNKY);
  ukazatelpismen_nastav(pocet_kol, UKAZATELE_SIRKA_BUNKY);

  hra_probiha = true;
}

int hra_start(void) {
  int bodu_kolo = 0;

  /* začátek měření herního času */
  stats_zpracuj_cas(false, false);

  ukazatelslov_hlaska(UKAZATELSLOV_HLASKA);
  while (hra_probiha && kolo_hry <= pocet_kol) {
    bodu_kolo = hra_kolo();

    if (bodu_kolo < 1) {
      celkem_bodu = 0;
      ukazatelslov_odkryj();
      vymaz_obr();
      ukazatele_vykresli();
      #if (ZVUKY == 1)
        putchar('\a');
      #endif
      fputs(ansi_format(ANSI_INVER) HRA_HLASKA_NEUHODL ansi_format(ANSI_RESET) "  " HRA_PROPOKRACOVANI, stdout);
      cekej_enter();
      vymaz_obr();
      break;
    }
    else {
      celkem_bodu += bodu_kolo;
      zbyva_zivotu = pocet_zivotu;
      kolo_hry++;
      ukazatelslov_hlaska("");
      ukazatelsibenice_nastav(pocet_zivotu, celkem_bodu);
      ukazatelkol_nastav(kolo_hry, pocet_kol, UKAZATELE_SIRKA_BUNKY);
      #if (DEBUG == 2)
        ukazatelslov_nastav(DEBUG_HADANE_SLOVO);
      #else
        ukazatelslov_nastav(slova[rand() % (sizeof(slova) / sizeof(slova[0]))]);
      #endif
      ukazatelpismen_nastav(pocet_kol, UKAZATELE_SIRKA_BUNKY);
    }
  }

  if (celkem_bodu > 0) {
    vymaz_obr();
  }

  return celkem_bodu;
}


/* lokální funkce */


static bool nacti_slova(void)
{
  register int i = 0;
  char slovo[100] = "";
  char *p_char = NULL;

  /* ukončí funkci, pakliže jsou slova již načtena */
  if (slova_nactena)  return true;

  /* otevře soubor se slovy */
  if ((f_slova = fopen(HRA_SLOVA_SOUBOR, "r")) == NULL) {
    vymaz_obr();
    fprintf(stderr, "\n" ERR_SIGN ERR_SOUBOR "\n", HRA_SLOVA_SOUBOR);
    return false;
  }

  /* načte slova do paměti */
  for (i = 0; i < (int) (sizeof(slova) / sizeof(slova[0])); i++) {
    if (!feof(f_slova)) {
      /* načtení řádku */
      fgets(slovo, sizeof(slovo), f_slova);
      /* ukončení v případě prázdného řádku */
      if (strlen(slovo) < 1)  continue;
      /* odstranění znaku konce řádku */
      if ((p_char = strchr(slovo, '\r')) != NULL)  *p_char = '\0';
      if ((p_char = strchr(slovo, '\n')) != NULL)  *p_char = '\0';

      if ((slova[i] = (char *) malloc(strlen(slovo) + 1)) == NULL) {
        fputs(ERR_SIGN "Nedostatek volne pameti - slova nenactena...\n", stderr);
        slova_nactena = false;
        /* uzavře soubor se slovy */
        if (fclose(f_slova) == EOF) {
          fputs(ERR_SIGN "Nelze zavrit soubor se slovy...\n", stderr);
        }
        return false;
      }
      else {
        /* zkopírování načteného slova do pole slov */
        strcpy(slova[i], slovo);
      }
    }
    else {
      break;
    }

  }

  /* uzavře soubor se slovy */
  if (fclose(f_slova) == EOF) {
    fputs(ERR_SIGN "Nelze zavrit soubor se slovy...\n", stderr);
  }

  slova_nactena = true;
  return true;
}

static int hra_kolo(void) {

  int i           = 0;     /* univerzální iterátor */
  int hadany_znak = '\0';  /* uživatelem zadaný znak */


  while (hra_probiha) {

    vymaz_obr();
    ukazatele_vykresli();

    /* ukončení hry při nedostatku životů */
    if (zbyva_zivotu < 1) {
      hra_probiha = false;
      break;
    }
    else if (!ukazatelslov_hotovo()) {
      /* načtení znaku od uživatele */
      printf("Hadej pismeno (%c) > ", (char) VOLBA_VOLBY);
      hadany_znak = getchar();
      cekej_enter();  /* vyprázdnění vstupního bufferu */

      /* zjištění, zda nejde o vyhrazený znak (zvláštní volbu) */
      switch ((ZVLASTNI_VOLBY) hadany_znak) {

        /* ukončí probíhající hru */
        case VOLBA_KONEC:
          printf(ansi_format(ANSI_INVER) "%c%c%c Ukoncit probihajici hru?" ansi_format(ANSI_RESET) "  (a/n) >  "
                 , (int) HRA_VOLBY_ZAVLP[0]
                 , (char) VOLBA_KONEC
                 , (int) HRA_VOLBY_ZAVLP[1]);

           if (tolower(getchar()) == HRA_VOLBY_ANO) {
             while (getchar() != '\n')
               ;  /* vyprázdnění bufferu */
             return (zbyva_zivotu = 0);  /* ukončení hry */
           }
           else {
             while (getchar() != '\n')
               ;  /* vyprázdnění bufferu */
             continue;  /* pokračování hry při zamítnutí volby */
           }

        break;

        /* zobrazí dostupné volby */
        case VOLBA_VOLBY:
          fputs(">  " ansi_format(ANSI_INVER), stdout);
          for (i = 0; i < (int) (sizeof(volby_seznam) / sizeof(volby_seznam[0])); i++) {
            printf("%c%c%c %s%s"
                   , (int) HRA_VOLBY_ZAVLP[0], volby_hodnoty[i], (int) HRA_VOLBY_ZAVLP[1]
                   , volby_seznam[i]
                   , (i < (int) ((sizeof(volby_seznam) / sizeof(volby_seznam[0])) - 1)) ? HRA_VOLBY_SEP : "");
          }
          /* odstraní oddělovač položek na konci seznamu */
          /*
          for (i = 0; i < (int) strlen(HRA_VOLBY_SEP); i++) {
            putchar('\b');
          }
          */
          fputs(ansi_format(ANSI_RESET) "\n   " HRA_PROPOKRACOVANI, stdout);
          cekej_enter();
          continue;
        break;

        /* zobrazí velkou nápovědu */
        case VOLBA_NAPOVEDA:
          napoveda();
          continue;
        break;

        /* doplní písmeno za cenu určitého počtu bodů */
        case VOLBA_POMOC_ZN:
          /* zatím není implementováno */
          /*
          printf(ansi_format(ANSI_INVER) "%c%c%c Napovi znak za cenu %d b." ansi_format(ANSI_RESET) "  " HRA_PROPOKRACOVANI
                 , (int) HRA_VOLBY_ZAVLP[0]
                 , (char) VOLBA_POMOC_ZN
                 , (int) HRA_VOLBY_ZAVLP[1]
                 , HRA_POMOC_ZN_CENA);
          cekej_enter();
          continue;
          */
        break;

        default:
          break;

      }

      /* další zpracování hádaného znaku a vyhodnocení úspěšnosti */
      if (ukazatelpismen_vydej(hadany_znak)) {
        if (ukazatelslov_hadej(hadany_znak) < 1) {
          ukazatelsibenice_nastav(--zbyva_zivotu, celkem_bodu);
        }
      }
      else {
        ukazatelslov_hlaska("");
        fputs(ansi_format(ANSI_INVER) HRA_ZNAK_NEDOSTUPNY ansi_format(ANSI_RESET) "  " HRA_PROPOKRACOVANI, stdout);
        cekej_enter();  /* čekání na stisk klávesy enter */
      }
    }
    else {
      #if (ZVUKY == 1)
        putchar('\a');
      #endif
      fputs(ansi_format(ANSI_INVER) HRA_HLASKA_UHODL ansi_format(ANSI_RESET) "  " HRA_PROPOKRACOVANI, stdout);
      cekej_enter();  /* čekání na stisk klávesy enter */
      break;
    }

  }

  return zbyva_zivotu;
}
