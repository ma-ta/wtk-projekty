/*
 *  Hlavní globální konfigurační soubor obsahující
 *  symbolické konstanty a makra používané napříč
 *  všemi moduly
 *
 */


#ifndef KONFIGURACE_H
#define KONFIGURACE_H

/* stringifikace maker */
#define str(a)   #a
#define xstr(a)  str(a)
/* vrátí počet prvků pole */
#define arrlen(arr)  ((int) (sizeof(arr) / sizeof(arr[0])))

#include <stdbool.h>

/* detekce operačního systému */
#ifndef OSNAME
  #if defined(__MSDOS__)
    #define OSNAME  "DOS"
    #define OS_DOS
  #elif defined(_WIN32) || defined(_WIN64)
    #define OSNAME  "Windows"
    #define OS_WIN
  #elif defined(__APPLE__)
    #define OSNAME  "macOS"
    #define OS_UNIX
  #elif defined(__linux__)
    #define OSNAME  "Linux"
    #define OS_UNIX
  #elif defined(__FreeBSD__)
    #define OSNAME  "FreeBSD"
    #define OS_UNIX
  #elif defined(__unix__)
    #define OSNAME  "UN*X"
    #define OS_UNIX
  #else
    #define OSNAME  "?"
  #endif
#endif

/* detekce překladače */
#ifndef CCNAME
  #if defined(_MSC_VER)
    #define CCNAME  "MSVC"
    #define CCVER   _MSC_VER
  #elif defined(__WATCOMC__)
    #define CCNAME  "Watcom"
    #define CCVER   (-1)
  #elif defined(__clang__)
    #define CCNAME   "Clang"
    #define CCVER    __clang_major__
    #define CCMINOR  __clang_minor__
  #elif defined(__GNUC__)
    #if defined(__DJGPP__)
      #define CCNAME  "DJGPP"
    #else
      #define CCNAME  "GCC"
    #endif
    #define CCVER    __GNUC__
    #define CCMINOR  __GNUC_MINOR__
  #else
    #define CCNAME  "?"
    #define CCVER   (-1)
  #endif
  #ifndef CCMINOR
    #define CCMINOR  (-1)
  #endif
#else
  #ifndef CCVER
    #define CCVER  (-1)
  #endif
#endif


/* GLOBÁLNÍ NASTAVENÍ */


/* úroveň ladění:
     0 - vypnuto
     1 - obrazovka není mazána
     2 - hádá se jedno přednastavené slovo */
#define DEBUG               0
#define DEBUG_HADANE_SLOVO  "Ah hoc Chrochrohcroch..."

#define NAZEV    "Hra Sibenice"
#define VERZE    "1.0.0"
#define WEB      "moodle.upce.cz"
#define AUTOR    "Martin TABOR"
#define LICENCE  "(GPLv3+)"

/* externí soubory */
#define HRA_SLOVA_SOUBOR          "./data/game_cs.dat"  /* seznam slov k hádání        (textový) */
#define UKAZATELSIBENICE_SOUBOR   "./data/game.dat"     /* šablona s obrázky šibenice  (textový) */
#define NAPOVEDA_SOUBOR           "./data/help.dat"     /* šablona české nápovědy      (textový) */
#define STATISTIKY_OBRSAB_SOUBOR  "./data/stats.dat"    /* šablona obrazovky statistik (textový) */
#define STATISTIKY_SOUBOR         "./data/stats.sav"    /* uložené herní statistiky    (binární) */

#define ERR_SOUBOR  "Nelze nacist externi soubor \"%s\"..."  /* informace o chybějícím souboru */

#define ANSI_FORMAT    1   /* zapne formátování ESC sekvencemi */
#ifdef OS_DOS
  #undef  ANSI_FORMAT
  #define ANSI_FORMAT  0
#endif
#define ZVUKY          1   /* zapne vkládání znaku '\a' */

#define POCET_KOL      9   /* celkový počet kol hry (hádaných slov) */
#define POCET_ZIVOTU   11  /* počet životů v jednom kole */
#define MAX_SKORE      ((POCET_KOL) * (POCET_ZIVOTU))

#define ERR_SIGN       "(!) "  /* vypysuje se před chybovou zprávou */

#define PROMPT_ENTER_NAVRAT  "(Enter pro navrat...)"
#define PROMPT_ENTER_POKRAC  "(Enter pro pokracovani...)"
#define PROMPT_ENTER_KONEC   "(Enter pro ukonceni...)"

/* argumenty příkazové řádky */

/* definice uvozovacích znaků */
#define ARG_SIGN_1  "-"
#define ARG_SIGN_2  "--"
#define ARG_SIGN_3  "/"
/* definice krátkých a dlouhých přepínačů */
#define ARG_HLP_SIGN_1  "?"       /* zobrazí seznam přepínačů */
#define ARG_HLP_SIGN_2  "help"
#define ARG_MAN_SIGN_1  "m"       /* zobrazí hlavní nápovědu hry */
#define ARG_MAN_SIGN_2  "manual"
#define ARG_STA_SIGN_1  "s"       /* zobrazí herní statistiky */
#define ARG_STA_SIGN_2  "stats"
#define ARG_VER_SIGN_1  "v"       /* zobarzí informace o sestavení */
#define ARG_VER_SIGN_2  "version"
#define ARG_DOS_SIGN_1  "c"       /* vynutí spuštení v režimu CLI s max. 25 řádky (DOS) */
#define ARG_DOS_SIGN_2  "cli"

#define ARG_VER_TEXT  "%s\n"  \
                      "Verze:   %s  (%s/%s %s%s, %s)\n"  \
                      "Web:     %s\n"  \
                      "Napsal:  %s  %s\n"  \
                      , NAZEV  \
                      , VERZE, OSNAME, CCNAME  \
                      , (CCVER == (-1)) ? "" : xstr(CCVER)  \
                      , (CCVER == (-1) || CCMINOR == (-1)) ? "" : "." xstr(CCMINOR)  \
                      , __DATE__  \
                      , WEB  \
                      , AUTOR, LICENCE
#define ARG_HLP_TEXT  "Seznam dostupnych prepinacu:\n"  \
                      "  -" ARG_HLP_SIGN_1 ", --" ARG_HLP_SIGN_2 "\tzobrazi (tento) seznam prepinacu\n"  \
                      "  -" ARG_MAN_SIGN_1 ", --" ARG_MAN_SIGN_2 "\tzobrazi hlavni napovedu hry\n"  \
                      "  -" ARG_STA_SIGN_1 ", --" ARG_STA_SIGN_2 "\tzobrazi herni statistiky\n"  \
                      "  -" ARG_VER_SIGN_1 ", --" ARG_VER_SIGN_2 "\tzobrazi informace o sestaveni\n"  \
                      "  -" ARG_DOS_SIGN_1 ", --" ARG_DOS_SIGN_2 "\tvynuti spusteni v rezimu 25 x 80 znaku"
#define ERR_ARGUMENTY  "Chybne argumenty prikazove radky...\n" \
                       "    Pro napovedu spustte s prepinacem \"-?\" (resp. \"/?\")."

#define arg_hlp_text()  printf("Pouziti: %s [PREPINAC]\n" ARG_HLP_TEXT "\n", argv[0])


/**********************/


/* detekce OS pro příkaz vymazání obrazovky */
#if (DEBUG == 0)
  #if (defined(_WIN32) || defined(_WIN64) || defined(__MSDOS__))
    #define vymaz_obr()  system("cls")
  #else
    #define vymaz_obr()  system("clear")
  #endif
#else
  #define vymaz_obr()
#endif


#define cekej_enter()  while (getchar() != '\n')  ;

#define konec()  { hlavicka_vykresli(TUI_HLAVICKA_TXT_L, TUI_HLAVICKA_TXT_KONEC);  \
                   printf("\n\n" ARG_VER_TEXT "\n\n");  \
                   \
                   hra_vycisti();  \
                   ukazatelsibenice_vycisti();  \
                   stats_vycisti(); }


/* tui - hlavička */

#define TUI_HLAVICKA_TXT_L       "(c) 2024  Freeware"  /* text v levé dolní buňce */
#define TUI_HLAVICKA_TXT_P       "v" VERZE             /* text v pravé dolní buňce */
#define TUI_HLAVICKA_TXT_KONEC   "Na shledanou"  /* (sudý počet zn. pro zarovnání na střed) */
#define TUI_HLAVICKA_BUNKA_L     26  /* šířka levé dolní buňky */
#define TUI_HLAVICKA_BUNKA_P     26  /* šířka pravé dolní buňky */
#define ERR_TUI_HLAVICKA_ZAROV   "Text v hlavicce nelze zarovnat na stred (+/- zn.)..."
#define ERR_TUI_HLAVICKA_TXTMAX  "Text v hlavicce je delsi nez %s bunka... (max. %d zn.)"
#define TUI_HLAVICKA_OBR  \
"+-----------------------------------------------------+\n"  \
"|                                                     |\n"  \
"|         Ma-TA {}       H R A                        |\n"  \
"|            games            S I _ E _ I C E         |\n"  \
"|                                                     |\n"  \
"%s\n"  \
"|%s|%s|\n"  \
"%s\n"  \

/* hlavní menu */

#define MENU_SIRKA              55
#define ERR_MENU_NADPIS_TXTMAX  "Nadpis je delsi nez bunka..."
#define ERR_MENU_NADPIS_ZAROV   "Nadpis nelze zarovnat na stred (+/- zn.)..."
#define MENU_NADPIS             "M E N U"
#define MENU_NADPIS_L           ">>>----->"  /* kvůli zarovnání musí být lichý počet zn. */
#define MENU_NADPIS_P           "<-----<<<"
#define MENU_ENUM               MENU_MENU, MENU_HRA, MENU_STATS, MENU_NAPOVEDA, MENU_KONEC
#define MENU_POLOZKY_CAPS       1  /* vypsání položek menu velkými písmeny */
#define MENU_POLOZKY            "Nova hra", "Herni kronika", "Napoveda", "Konec"
#define MENU_ZADEJ              "Zadej cislo polozky"
#define MENU_ZADEJ_ERR          "Pouze cisla mezi %d a %d!"

/* (strlen(DOBA_INFO) == MENU_SIRKA == šířka hlavičky == 55 zn.) */
#define DOBA_INFO  ">>>>----->  Jsi starsi o:  %02d h %02d min %02d s  <-----<<<<"  \
                   , p_tmcas->tm_hour, p_tmcas->tm_min, p_tmcas->tm_sec

/* ukazatele */

#define UKAZATELE_BARVY                 1    /* určuje, zda obarvit vybrané prvky TUI v průběhu hry */
#define UKAZATELE_ORAMOVANI_ZN          '-'
#define UKAZATELE_ORAMOVANI_KRIZENI_ZN  '+'
#define UKAZATELE_SIRKA_BUNKY           5
#define UKAZATELE_MINIMALNI_SIRKA       9    /* minimální počet buněk na řádku */

/* ukazatel šibenice */

#define UKAZATELSIBENICE_ZARAZKA        '#'

#if UKAZATELE_BARVY == 1
  #define UKAZATELSIBE_ZIVOT_FMT        ansi_format(ANSI_ULINE)
  #define UKAZATELSIBE_ZIVOT_LOW_FMT    ansi_frcolor(ANSI_RED) ansi_format(ANSI_BLICK)
  /* počet životů, pod nímž se zvolí formát ZIVOT_LOW_FMT namísto ZIVOT_FMT */
  #define UKAZATELSIBE_ZIVOT_LOW        3
  #define UKAZATELSIBE_BODY_FMT         ""
#else
  #define UKAZATELSIBE_ZIVOT_FMT        ansi_format(ANSI_ULINE)
  #define UKAZATELSIBE_ZIVOT_LOW_FMT    ansi_format(ANSI_ULINE) ansi_format(ANSI_BLICK)
  /* počet životů, pod nímž se zvolí formát ZIVOT_LOW_FMT namísto ZIVOT_FMT */
  #define UKAZATELSIBE_ZIVOT_LOW        3
  #define UKAZATELSIBE_BODY_FMT         ""
#endif

/* ukazatel kol */

#define UKAZATELKOL_BARVA       ANSI_BLUE
#define UKAZATELKOL_BLIKAT      1
#define UKAZATELKOL_FORMAT      ansi_format(ANSI_BOLD)  /* ansi_frcolor(UKAZATEL_BARVA) */  ansi_format(ANSI_INVER)
#define UKAZATELKOL_SYM_VLEVO   ">"
#define UKAZATELKOL_SYM_VPRAVO  "<"

/* ukazatel slov */

#define UKAZATELSLOV_PROMPT          ">  "  /* znak před hádaným slovem */
#define UKAZATELSLOV_VELKA           0      /* vypysuje vše velkými písmeny */
#define UKAZATELSLOV_PISMENO_CH      1      /* určuje, zda brát CH jako jedno písmeno */
#define UKAZATELSLOV_DELKA_MAX       31
#define UKAZATELSLOV_MASKA           '_'
#define UKAZATELSLOV_PRESKOCIT       " "  ","  "."  "?"  "!"  "-"  ";"  "%%"  "'"  "\""
#define UKAZATELSLOV_HLASKA_MAX      (UKAZATELE_SIRKA_BUNKY * 2)
/* zapne či vypne formátování hlášky pomocí sekvencí v ansi_fmt.h */
#define UKAZATELSLOV_HLASKA_FMT_ANO  ansi_frcolor(ANSI_GREEN)
#define UKAZATELSLOV_HLASKA_FMT_NE   ansi_frcolor(ANSI_RED)
/* hlášky do pravého okénka (lichý počet znaků pro správné zarovnání!) */
#define UKAZATELSLOV_HLASKA          "* Vitej *"
#define UKAZATELSLOV_HLASKY_ANO      "VYBORNE", "BRAVO", "HEJ RUP", "TREFA", "ZASAH"
#define UKAZATELSLOV_HLASKY_NE       "TUDY NE", "NE NE", "AU!", "TO BOLELO", "VEDLE"

/* ukazatel písmen */

#define UKAZATELPISMEN_NIC  '\0'  /* v poli dostupných znaků nahradí použitou položku */
#define UKAZATELPISMEN_DOSTUPNA_PISMENA_SIZE  ('Z' - 'A' + 1)
#define ukazatelpismen_dostupna_pismena_napln(pole)  {  int znak;  \
                                                        for (znak = 'A'; znak < 'A' + UKAZATELPISMEN_DOSTUPNA_PISMENA_SIZE; znak++) {  \
                                                          *((pole) + (znak - 'A')) = (char) znak;  \
                                                        }  \
                                                     }

/* hra */

#define HRA_POCETSLOV       1000  /* počet slov načítaných ze slovníku */
#define HRA_POMOC_ZN_CENA   10    /* počet bodů za pomoc - doplnění písmene */
#define HRA_HLASKA_FORMAT   ansi_format(ANSI_INVER) ansi_format(ANSI_BLICK)
#define HRA_PROPOKRACOVANI  "(stiskni Enter...)"

/* VOLBA_KONEC    - ukončí probíhající hru
   VOLBA_VOLBY    - zobrazí dostupné volby
   VOLBA_NAPOVEDA - zobrazí velkou nápovědu
   VOLBA_POMOC_ZN - doplní písmeno za cenu určitého počtu bodů */
#define HRA_VOLBY           VOLBA_VOLBY    = '*',  \
                            VOLBA_KONEC    = '0',  \
                            VOLBA_NAPOVEDA = '1',  \
                            VOLBA_POMOC_ZN = '2'
/* seznam voleb */
#define HRA_VOLBY_SZN       "Ukoncit", "Manual", /* "Napovez znak (za " xstr(HRA_POMOC_ZN_CENA) " b.)" */
/* počet položek musí být shodný (ne menší!) s HRA_VOLBY_SZN */
#define HRA_VOLBY_HODNOTY   VOLBA_KONEC, VOLBA_NAPOVEDA, VOLBA_POMOC_ZN
#define HRA_VOLBY_ZAVLP     "[]"  /* musí být 2 znaky! (strlen(HRA_VOLBY_ZN) >= 2, [0]=levý [1]=pravý */
#define HRA_VOLBY_SEP       "  "  /* oddělovač jednotlivých položek ve výpisu */
#define HRA_VOLBY_ANO       'a'

#define HRA_OBR_PROHRA  \
"          |\n"  \
"       ---+---\n"  \
"          |\n"  \
"          |\n"  \
"        R I P\n"
#define HRA_OBR_VYHRA  \
"          ooooooooo\n"  \
"        oo   O o   oo\n"  \
"       ooo    |    ooo\n"  \
"       oo  ~~ O ~~  oo  ->  \" Uff... OK. \"\n"  \
"        ooooooooooooo\n"

#define HRA_ZNAK_NEDOSTUPNY  "Tento znak neni k dispozici."
#if UKAZATELE_BARVY == 1
  #define HRA_HLASKA_UHODL     ansi_frcolor(ANSI_GREEN) "Slovo jsi UHODL!"   ansi_format(ANSI_RESET)
  #define HRA_HLASKA_NEUHODL   ansi_frcolor(ANSI_RED)   "Slovo jsi NEUHODL!" ansi_format(ANSI_RESET)
#else
  #define HRA_HLASKA_UHODL     "Slovo jsi UHODL!"
  #define HRA_HLASKA_NEUHODL   "Slovo jsi NEUHODL!"
#endif
#define HRA_HLASKA_VYHRA     "VYHRAL JSI S CELKOVYM SKORE "  \
                             ansi_format(ANSI_BOLD) "%d BODU" ansi_format(ANSI_RESET) HRA_HLASKA_FORMAT " !"
#define HRA_HLASKA_PROHRA    "TENTOKRAT TO NEVYSLO! Ziskavas 0 bodu."

/* nápověda */

#define NAPOVEDA_ZARAZKA    '#'
#define NAPOVEDA_OBRAZOVEK  4
#define NAPOVEDA_ZAHLAVI    \
"+-------------------+-------------------------------+-------------------+\n"  \
"|                   |                               |                   |\n"  \
"|     ooooooooo     | +---+---+---+---+             |     ooooooooo     |\n"  \
"|   oo   o o   oo   | | N | A | P | O |             |   oo   O o   oo   |\n"  \
"|  ooo    |    ooo  | +---+---+---+---+---+---+---+ |  ooo    |    ooo  |\n"  \
"|  oo  ~~ - ~~  oo  |             | V | E | D | A | |  oo  ~~ O ~~  oo  |\n"  \
"|   ooooooooooooo   |             +---+---+---+---+ |   ooooooooooooo   |\n"  \
"|                   |                               |                   |\n"  \
"+-------------------+-------------------------------+-------------------+\n"

/* statistiky */

#define STATS_TAJNE_HESLO   "TajneHeslo"  /* konstanta pro editaci statistik a ověření souboru */
#define STATS_VYCHOZI_JMN   "Ma-TA"  /* výchozí nejlepší hráč */
#define STATS_TOPNEJ_BARVA  ansi_frcolor(ANSI_YELLOW)  /* obarvení NEJ záznamů */
#define STATS_VYCHOZI_B     50  /* výchozí nejlepší skóre */
#define STATS_JMENO_STRLN   43  /* maximální délka jména */
#define STATS_POCET_HRACU   5  /* počet uchovávaných pořadí */
#define STATS_PRAVOST_ZAP   0  /* zapíná a vypíná kontrolní součet */
#define STATS_OBR_RADEK     43  /* délka řádku se jménem */
#define STATS_OBR_VODITKO   "."  /* znaky oddělující jméno a body na řádku */
#define STATS_OBR_NONAME    "(?)"  /* zobrazí se v herní kronice, pokud výherce nezadal jméno */
#define STATS_OBR_1_ODR     ansi_format(ANSI_BOLD) ansi_format(ANSI_BLICK)  /* formát odrážky nej řádku */
#define STATS_OBR_1_TXT     ansi_format(ANSI_BOLD)  /* formát nej řádku */
#define STATS_OBR_ODRAZKY   ">>>>------>",  \
                            "  >>>----->",  \
                            "    >>---->",  \
                            "      >--->",  \
                            "        -->"
#define STATS_DELKA_ERR     ERR_SIGN "Delka jmena smi byt max. %d znaku."
#define STATS_ZADNE_STATS   "Zatim nejsou ulozeny zadne statistiky."
#define STATS_OBR_ZAHLAVI  \
"+-------------------+-------------------------------+-------------------+\n"  \
"|                   |                               |                   |\n"  \
"|     ooooooooo     |     +---+---+---+---+---+     |     ooooooooo     |\n"  \
"|   oo   o o   oo   |     | H | E | R | N | I |     |   oo   O o   oo   |\n"  \
"|  ooo    |    ooo  | +---+---+---+---+---+---+---+ |  ooo    |    ooo  |\n"  \
"|  oo  ~~ - ~~  oo  | | K | R | O | N | I | K | A | |  oo  ~~ O ~~  oo  |\n"  \
"|   ooooooooooooo   | +---+---+---+---+---+---+---+ |   ooooooooooooo   |\n"  \
"|                   |                               |                   |\n"  \
"+-------------------+-------------------------------+-------------------+\n"

#endif
