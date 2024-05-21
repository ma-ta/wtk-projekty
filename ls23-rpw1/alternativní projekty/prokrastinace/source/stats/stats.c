#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../globconf.h"
#include "stats.h"
#include "../libs/ansi_fmt.h"


/* vynuluje stats_skore */
#define vynuluj_skore()  { int i = 0;  \
                           \
                           /* nastavení výchozího nejlepšího hráče */  \
                           strcpy(stats_skore.jmena[0], STATS_VYCHOZI_JMN);  \
                           stats_skore.skore[0] = STATS_VYCHOZI_B;  \
                           \
                           for (i = 1; i < STATS_POCET_HRACU; i++) {  \
                             stats_skore.jmena[i][0] = '\0';  \
                             stats_skore.skore[i]    = 0;  \
                           }  \
                         }
#define vynuluj_casy()  { stats_casy.nejkratsi_hra      = (time_t) 0;  \
                          stats_casy.celkovy_herni_cas = (time_t) 0;  \
                        }
#define stats_vynuluj()  { vynuluj_skore();  \
                           vynuluj_casy();  \
                           stats_poslednizmena = time(NULL);  \
                           data = false;  \
                         }
#define uzavri_fstats()  if (f_stats != NULL) {  \
                           if (fclose(f_stats) != EOF)  f_stats = NULL;  \
                           else fputs(ERR_SIGN "Soubor se statistikami nelze uzavrit...\n\n", stderr);  \
                         }


/* dynamické pole pro načtění šablony info obrazovky */
static char *stats_obr_sablona = NULL;
static size_t stats_obr_sablona_size = 0;
/* informuje, zda je modul inicializovaný */
static bool nastaveno = false;
/* informuje, zda se podařilo načíst statistiky ze souboru */
static bool nacteno = false;
/* informuje, zda je datová struktura statistik prázdná nebo ne */
static bool data = false;
/* datový soubor se statistikami */
static FILE *f_stats = NULL;
/* STRUKTURA BINÁRNÍHO SOUBORU SE STATISTIKAMI */
/*
 * *********************************************************************************
 *   OFFSET                                    |  POPIS
 * *********************************************************************************
 *
 *                                             |  ČAS POSLEDNÍ ZMĚNY
 * [ 0                                      ]  |  [ time_t stats_poslednizmena     ]
 *
 *                                             |  POLOŽKY STRUKTURY stats_skore
 *                                                ----------------------------------
 * [ + sizeof(stats_poslednizmena)          ]  |  [ int skore[STATS_POCET_HRACU]   ]
 * [ + sizeof(stats_skore.skore)            ]  |  [ JMENO jmena[STATS_POCET_HRACU] ]
 *
 *                                             |  POLOŽKY STRUKTURY stats_casy
 *                                                ----------------------------------
 * [ + sizeof(stats.skore.jmena)            ]  |  [ time_t nejkratsi_hra           ]
 * [ + sizeof(stats_casy.nejkratsi_hra)     ]  |  [ time_t celkovy_herni_cas       ]
 */
/* datové položky statistik */
typedef char JMENO[STATS_JMENO_STRLN + 1];
static time_t stats_poslednizmena = 0;
static struct stats_skore {
  int   skore[STATS_POCET_HRACU];
  JMENO jmena[STATS_POCET_HRACU];
} stats_skore;
static struct stats_casy {
  time_t nejkratsi_hra;
  time_t celkovy_herni_cas;
} stats_casy;


/* soukromé funkce modulu */


static bool nahraj_sablonu(void)
{
  /* textový soubor s šablonou obrazovky statistik */
  FILE   *f_sablona        = NULL;
  size_t potrebna_velikost = 0;
  int    zkopirovano_zn    = 0,
         c                 = '\0';

  /* otevření souboru */
  if ((f_sablona = fopen(STATISTIKY_OBRSAB_SOUBOR, "r")) == NULL) {
    fprintf(stderr,
            ERR_SIGN "Nelze otevrit sablonu obrazovky statistik:\n"
            "    %s\n\n"
            , STATISTIKY_OBRSAB_SOUBOR);
    return false;
  }

  /* zjištění potřebného místa k alokování */
  while (getc(f_sablona) != EOF)  potrebna_velikost++;
  stats_obr_sablona_size = (++potrebna_velikost);  /* ukončovací znak '\0' */
  fseek(f_sablona, 0, SEEK_SET);
  /* pokus o alokování paměti */
  if ((stats_obr_sablona = (char *) malloc(potrebna_velikost)) == NULL) {
    puts(ERR_SIGN "Nedostatek pameti pro sablonu obrazovky statistik...\n\n");
    fclose(f_sablona);  f_sablona = NULL;
    return false;
  }

  /* zkopírování obsahu souboru do paměti */
  while ((c = getc(f_sablona)) != EOF && (size_t) zkopirovano_zn < potrebna_velikost) {
    *(stats_obr_sablona + (zkopirovano_zn++)) = c;
  }
  stats_obr_sablona[zkopirovano_zn] = '\0';

  /* uzavření souboru */
  if (f_sablona != NULL) {
    fclose(f_sablona);  f_sablona = NULL;
  }

  return true;
}

/* zapíše ověřovací data do souboru
   a vrátí zapsaný kontrolní součet */
/*
static int zapis_pravost_f(void)
{
  #if STATS_PRAVOST_ZAP

  #else
    return 0;
  #endif
}
*/

/* ověří pravost souboru se statistikami
   pomocí otisku souboru a tajného čísla */
/*
static bool over_pravost_f(void)
{
  #if STATS_PRAVOST_ZAP

  #else
    return true;
  #endif
}
*/


/* veřejné funkce z stats.h */


bool stats_nastav(void)
{
  if (!nastaveno) {

    /* soubor se statistikami se nepodařilo otevřít */
    if ((f_stats = fopen(STATISTIKY_SOUBOR, "rb")) == NULL) {
      /* potlačení chybového výstupu (kvůli prvnímu spuštění programu) */
      #if DEBUG > 0
        fprintf(stderr,
                ERR_SIGN "Soubor se statistikami nenalezen...\n"
                "    (%s)\n\n",
                STATISTIKY_SOUBOR);
      #endif
      /* nastavení datových položek statistik na nulové hodnoty */
      stats_vynuluj();
      nastaveno = nahraj_sablonu();  /* pokud se nenačte šablona, nelze modul použít */
      return (nacteno = data = false);
    }
    /* soubor se statistikami otevřen - načtení dat */
    else {
      /* načtení času poslední změny */
      if (fread((void *) &stats_poslednizmena, sizeof(stats_poslednizmena), 1, f_stats) != 1) {
        /* chyba čtení dat */
        fprintf(stderr,
                ERR_SIGN "Chyba pri nacitani statistik ze souboru (posledni zmena)...\n\n");
        stats_vynuluj();
        uzavri_fstats();
        nastaveno = true;
        return (nacteno = data = false);
      }
      /* načtení skóre */
      if (fread(stats_skore.skore, sizeof(stats_skore.skore), 1, f_stats) != 1) {
        /* chyba čtení dat */
        fprintf(stderr,
                ERR_SIGN "Chyba pri nacitani statistik ze souboru (body)...\n\n");
        stats_vynuluj();
        uzavri_fstats();
        nastaveno = true;
        return (nacteno = data = false);
      }
      /* načtení jmen hráčů */
      if (fread(stats_skore.jmena, sizeof(stats_skore.jmena), 1, f_stats) != 1) {
        /* chyba čtení dat */
        fprintf(stderr,
                ERR_SIGN "Chyba pri nacitani statistik ze souboru (jmena)...\n\n");
        stats_vynuluj();
        uzavri_fstats();
        nastaveno = true;
        return (nacteno = data = false);
      }
      /* načtení času nejkratší hry */
      if (fread(&(stats_casy.nejkratsi_hra), sizeof(stats_casy.nejkratsi_hra), 1, f_stats) != 1) {
        fprintf(stderr,
                ERR_SIGN "Chyba pri nacitani statistik (nejdelsi hra)...\n\n");
        uzavri_fstats();
        return false;
      }
      /* načtení celkového odehrátého času */
      if (fread(&(stats_casy.celkovy_herni_cas), sizeof(stats_casy.celkovy_herni_cas), 1, f_stats) != 1) {
        fprintf(stderr,
                ERR_SIGN "Chyba pri nacitani statistik (celkovy herni cas)...\n\n");
        uzavri_fstats();
        return false;
      }
    }

    uzavri_fstats();

    nastaveno = nahraj_sablonu();  /* pokud se nenačte šablona, nelze modul použít */
    data = (stats_skore.skore[0] > 0 || stats_casy.celkovy_herni_cas > (time_t) 0) ? true : false;
    return (nacteno = true);
  }

  /* modul je již nastaven */
  else {
    return false;
  }
}

bool stats_nastaveno(void)  {  return nastaveno;  }
bool stats_nacteno(void)    {  return nacteno;    }
bool stats_data(void)       {  return data;       }

bool stats_uloz(void)
{
  if (nastaveno) {

    /* otevření souboru */
    if (f_stats != NULL)  fclose(f_stats);
    if ((f_stats = fopen(STATISTIKY_SOUBOR, "wb")) == NULL) {
      /* chyba zápisu dat */
      fprintf(stderr,
              ERR_SIGN "Nelze otevrit soubor pro zapis:\n"
              "    " STATISTIKY_SOUBOR "\n\n");
      return false;
    }

    /* uložení času změny */
    if (fwrite(&stats_poslednizmena, sizeof(stats_poslednizmena), 1, f_stats) != 1) {
      fprintf(stderr,
              ERR_SIGN "Chyba pri ukladani statistik (posledni zmena)...\n\n");
      uzavri_fstats();
      return false;
    }
    /* uložení bodů */
    if (fwrite(stats_skore.skore, sizeof(stats_skore.skore), 1, f_stats) != 1) {
      fprintf(stderr,
              ERR_SIGN "Chyba pri ukladani statistik (body)...\n\n");
      uzavri_fstats();
      return false;
    }
    /* uložení jmen hráčů */
    if (fwrite(stats_skore.jmena, sizeof(stats_skore.jmena), 1, f_stats) != 1) {
      fprintf(stderr,
              ERR_SIGN "Chyba pri ukladani statistik (jmena)...\n\n");
      uzavri_fstats();
      return false;
    }
    /* uložení času nejkratší hry */
    if (fwrite(&(stats_casy.nejkratsi_hra), sizeof(stats_casy.nejkratsi_hra), 1, f_stats) != 1) {
      fprintf(stderr,
              ERR_SIGN "Chyba pri ukladani statistik (nejdelsi hra)...\n\n");
      uzavri_fstats();
      return false;
    }
    /* uložení celkového odehrátého času */
    if (fwrite(&(stats_casy.celkovy_herni_cas), sizeof(stats_casy.celkovy_herni_cas), 1, f_stats) != 1) {
      fprintf(stderr,
              ERR_SIGN "Chyba pri ukladani statistik (celkovy herni cas)...\n\n");
      uzavri_fstats();
      return false;
    }

    uzavri_fstats();
    return true;
  }
  else {
    fputs(ERR_SIGN "Modul statistik neni nastaven...\n\n", stderr);
    return false;
  }
}

int stats_zpracuj_body(int body)
{
  int i, j;  /* iterátory */

  if (nastaveno) {
    data = true;
    for (i = 0; i < arrlen(stats_skore.skore); i++) {
      /* předané body jsou v rámci TOP n */
      stats_poslednizmena = time(NULL);
      if (stats_skore.skore[i] <= body) {
        /* posunutí stávajících bodů a jmen dolů a zápis aktuálního skóre */
        if (stats_skore.skore[i] < body) {
          for (j = arrlen(stats_skore.skore) - 1 ; j > i; j--) {
            stats_skore.skore[j] = stats_skore.skore[j - 1];
            strcpy(stats_skore.jmena[j], stats_skore.jmena[j - 1]);
          }
          stats_skore.skore[i] = body;
          stats_skore.jmena[i][0] = '\0';
        }

        return (i + 1);
      }
    }
    return 0;
  }

  return (-1);
}

void stats_zadej_jmeno(int pozice)
{
  char jmeno[STATS_JMENO_STRLN + 1] = "";
  int index = pozice - 1;
  char *p_char = NULL;

  if (nastaveno) {

    /* načtení jména od uživatele */
    fgets(jmeno, sizeof(jmeno), stdin);
    /* oříznutí znaků konce řádku */
    if ((p_char = strchr(jmeno, '\r')) != NULL)  *p_char = '\0';
    if ((p_char = strchr(jmeno, '\n')) != NULL)  *p_char = '\0';

    /* uložení jména do struktury */
    if (index < arrlen(stats_skore.jmena) && index >= 0) {
      strncpy(stats_skore.jmena[index], jmeno, sizeof(stats_skore.jmena[index]));
    }
    else {
      fprintf(stderr,
              ERR_SIGN STATS_DELKA_ERR
              , STATS_JMENO_STRLN);
    }
  }
  else {
    fputs(ERR_SIGN "Modul statistik neni nastaven...\n\n", stderr);
  }
}

int stats_zpracuj_cas(bool konec, bool uloz_nej)
{
  static bool mereni_probiha = false;
  static time_t start_mereni = (time_t) 0;
  static time_t konec_mereni = (time_t) 0;


  if (nastaveno) {

    if (!konec) {
      start_mereni = time(NULL);
      mereni_probiha = true;
      return 0;
    }
    else if (konec && mereni_probiha) {
      data = true;
      konec_mereni = time(NULL);
      stats_poslednizmena = konec_mereni;

      mereni_probiha = false;
      konec_mereni -= start_mereni;
      stats_casy.celkovy_herni_cas += konec_mereni;

      if ((konec_mereni <= stats_casy.nejkratsi_hra || stats_casy.nejkratsi_hra == (time_t) 0)
             && uloz_nej) {
        stats_casy.nejkratsi_hra = konec_mereni;
        return 1;
      }
      else {
        return 0;
      }
    }
    else {
      fputs(ERR_SIGN "Mereni jeste nezacalo.\n    (Spustte s argumentem false...)\n\n", stderr);
    }
  }
  else {
    fputs(ERR_SIGN "Modul statistik neni nastaven...\n\n", stderr);
  }

  return (-1);
}

time_t stats_zjisti_poslednizmenu(void)
{
  if (nastaveno && data) {
    return stats_poslednizmena;
  }
  else {
    fputs(ERR_SIGN "Modul statistik neni nastaven nebo nejsou data...\n\n", stderr);
  }

  return ((time_t) 0);
}

time_t stats_zjisti_nejcas(int *h, int *min, int *s)
{
  if (nastaveno && data) {
    time_t doba = stats_casy.nejkratsi_hra;

    *h   = doba / 3600;
    *min = (doba - (*h * 3600)) / 60;
    *s   = doba - (*h * 3600) - (*min * 60);

    return (stats_casy.nejkratsi_hra);
  }
  else {
    fputs(ERR_SIGN "Modul statistik neni nastaven nebo nejsou data...\n\n", stderr);
    *h = *min = *s = 0;
  }

  return ((time_t) 0);
}

time_t stats_zjisti_celkovycas(int *h, int *min, int *s)
{
  if (nastaveno && data) {
    time_t doba = stats_casy.celkovy_herni_cas;

    *h   = doba / 3600;
    *min = (doba - (*h * 3600)) / 60;
    *s   = doba - (*h * 3600) - (*min * 60);

    return (stats_casy.celkovy_herni_cas);
  }
  else {
    fputs(ERR_SIGN "Modul statistik neni nastaven nebo nejsou data...\n\n", stderr);
    *h = *min = *s = 0;
  }

  return ((time_t) 0);
}

int stats_zjisti_nte_nejbody(int nte_poradi)
{
  int index = nte_poradi - 1;

  if (nastaveno && data) {
    if (index < STATS_POCET_HRACU && index >= 0) {
      return (stats_skore.skore[index]);
    }
    else {
      fprintf(stderr,
              ERR_SIGN "Uklada se pouze 1. az %d. poradi...\n\n"
              , STATS_POCET_HRACU);
    }
  }
  else {
    fputs(ERR_SIGN "Modul statistik neni nastaven nebo nejsou data...\n\n", stderr);
  }

  return 0;
}

const char *stats_zjisti_nte_nejjmeno(int nte_poradi)
{
  int index = nte_poradi - 1;

  if (nastaveno && data) {
    if (index < STATS_POCET_HRACU && index >= 0) {
      return ((const char *) stats_skore.jmena[index]);
    }
    else {
      fprintf(stderr,
          ERR_SIGN "Uklada se pouze 1. az %d. poradi...\n\n"
          , STATS_POCET_HRACU);
    }
  }

  return "";
}

bool stats_vypis(bool jednoduchy_vypis)
{
  int i, j;
  bool jmeno_vyplneno = false;
  char vystup[1000] = "";
  char *odrazky[] = { STATS_OBR_ODRAZKY };
  int pocet_zn = 0;
  int h_nej, min_nej, s_nej,     /* čas nejdelší hry */
      h_celk, min_celk, s_celk;  /* celkový odehrátý čas */

  if (nastaveno && data) {
    (void) stats_zjisti_nejcas(&h_nej, &min_nej, &s_nej);
    (void) stats_zjisti_celkovycas(&h_celk, &min_celk, &s_celk);

    /* zjednodušený výpis */

    if (jednoduchy_vypis || stats_obr_sablona == NULL) {

      puts("Nejvyssi dosazena skore:\n");

      for (i = 1; i <= STATS_POCET_HRACU; i++) {
        jmeno_vyplneno = (strcmp(stats_zjisti_nte_nejjmeno(i), "") == 0) ? false : true;
        printf("%d.  %02d b.%s%s%s%s\n"
        , i
        , stats_zjisti_nte_nejbody(i)
        , (jmeno_vyplneno) ? "  " : ""
        , (jmeno_vyplneno) ? odrazky[i - 1] : ""
        , (jmeno_vyplneno) ? "  " : ""
        , stats_zjisti_nte_nejjmeno(i));
      }

      puts("\nHerni casy:\n");

      printf("Nejrychlejsi vyhra     :   %02d h  %02d min  %02d s\n"
             , h_nej, min_nej, s_nej);
      printf("Celkova odehrata doba  :  %03d h  %02d min  %02d s\n"
             , h_celk, min_celk, s_celk);
    }

    /* obrazovka se statistikami */

    else {
      vymaz_obr();

      /* sestavení řetězce pro výstup */
      for (i = 0; i < STATS_POCET_HRACU; i++) {
        pocet_zn += sprintf(vystup + pocet_zn,
                             "  %s%s%d.  %s%s"
                             , (i == 0) ? STATS_OBR_1_ODR "*" ansi_format(ANSI_RESET) " " : "  "
                             , (i == 0) ? STATS_OBR_1_TXT STATS_TOPNEJ_BARVA : ""
                             , i + 1
                             , (stats_skore.jmena[i][0] == '\0' && stats_skore.skore[i] > 0)
                                 ? STATS_OBR_NONAME
                                 : stats_skore.jmena[i]
                             , (stats_skore.jmena[i][0] == '\0' && stats_skore.skore[i] == 0)
                                  ? STATS_OBR_VODITKO STATS_OBR_VODITKO
                                  : "  ");
        for (j = 0; j < (int) (STATS_OBR_RADEK - 2 - ((stats_skore.jmena[i][0] == '\0' && stats_skore.skore[i] > 0)
                                                        ? strlen(STATS_OBR_NONAME)
                                                        : strlen(stats_skore.jmena[i]))); j++)
        {
          strncat(vystup + pocet_zn, STATS_OBR_VODITKO, sizeof(vystup) - pocet_zn);
          pocet_zn++;
        }
        pocet_zn += sprintf(vystup + pocet_zn,
                             "  %s  %2d b.%s\n"
                             , (i < arrlen(odrazky)) ? odrazky[i] : "           "
                             , stats_skore.skore[i]
                             , (i == 0) ? ansi_format(ANSI_RESET) : "");
      }

      /* výstup na obrazovku */
      puts(STATS_OBR_ZAHLAVI);
      printf((const char *) stats_obr_sablona
             , MAX_SKORE
             , vystup
             , h_nej, min_nej, s_nej
             , h_celk, min_celk, s_celk);

      fputs(ansi_cursor_off(), stdout);
      fputs(ansi_format(ANSI_INVER) "\n" PROMPT_ENTER_NAVRAT ansi_format(ANSI_RESET),
            stdout);
      cekej_enter();
      fputs(ansi_cursor_on(), stdout);
      vymaz_obr();

    }

    return true;
  }
  else if (nastaveno && !data) {
    if (!jednoduchy_vypis) {
      vymaz_obr();
      fputs(ansi_cursor_off(), stdout);
      puts(STATS_OBR_ZAHLAVI);
      puts(STATS_ZADNE_STATS);
      fputs(ansi_format(ANSI_INVER) "\n" PROMPT_ENTER_NAVRAT ansi_format(ANSI_RESET),
            stdout);
      cekej_enter();
      fputs(ansi_cursor_on(), stdout);
      vymaz_obr();
      return false;
    }
    else {
      puts(STATS_ZADNE_STATS);
      return false;
    }
  }
  else {
    fputs(ERR_SIGN "Modul statistik neni nastaven...\n\n", stderr);
    return false;
  }
}

bool stats_vymaz(void)
{
  if (nastaveno) {
    stats_vynuluj();
    return true;
  }
  else {
    fputs(ERR_SIGN "Modul statistik neni nastaven...\n\n", stderr);
    return false;
  }
}

void stats_vycisti(void)
{
  if (nastaveno) {
    (void) free((void *) stats_obr_sablona);
    stats_obr_sablona = NULL;
    stats_obr_sablona_size = 0;
  }
  else {
    fputs(ERR_SIGN "Modul statistik neni nastaven...\n\n", stderr);
  }
}
