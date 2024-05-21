/*
 *  Modul herních statistik
 *
 *  Zajišťuje načítání, aktualizaci a ukládání herních statistik do souboru.
 *  Rovněž vypisuje obrazovku "Herní kronika" a poskytuje znednodušený
 *  výstup do terminálu pomocí přepínače -s.
 *
 */


#ifndef STATS_H
#define STATS_H


/* pokusí se načíst soubor se statistikami
   a inicializuje modul
   true  = statistiky načteny,
   false = statistiky nenačteny */
bool stats_nastav(void);

/* zjistí, zda je modul
   statistik nastaven */
bool stats_nastaveno(void);

/* zjistí, zda byla správně
   načtena data ze souboru */
bool stats_nacteno(void);

/* informuje, zda jsou již
   uložena nějaká data */
bool stats_data(void);

/* pokusí se zapsat statistiky
   do datového souboru */
bool stats_uloz(void);

/* aktualizuje statistiky bodů
   dle aktuálních dat
   -1 = statistiky nejsou nastaveny
    0 = není zajímavé
    n = n-té nejvyšší skóre */
int stats_zpracuj_body(int body);

/* načte a uloží jméno hráče
   do struktury se statistikami */
void stats_zadej_jmeno(int pozice);

/* aktualizuje statistiky bodů
   dle aktuálních dat
   konec:
     false: začátek měření
     true : konec měření
   uloz_nej:
     true:  porovná s nejkratším časem
   vrací:
     -1 = statistiky nejsou nastaveny
      0 = není zajímavé / začátek měření
      1 = zatím nejkratší herní čas */
int stats_zpracuj_cas(bool konec, bool uloz_nej);

/* vrátí čas poslední změny
   ve statistikách */
time_t stats_zjisti_poslednizmenu(void);

/* vrátí nejkratší herní čas
   prostřednictvím parametrů
   návratová hodnota 0 - žádná data */
time_t stats_zjisti_nejcas(int *h, int *min, int *s);

/* vrací celkový odehrátý čas
   prostřednictvím parametrů
   návratová hodnota 0 - žádná data */
time_t stats_zjisti_celkovycas(int *h, int *min, int *s);

/* vrátí výši skóre pro zadanou pozici
   0 = nejsou k dispozici žádná data */
int stats_zjisti_nte_nejbody(int nte_poradi);

/* vrátí jméno hráče na n-té pozici,
   případně prázdný řetězec */
const char *stats_zjisti_nte_nejjmeno(int nte_poradi);

/* vypíše aktuální herní statistiky */
bool stats_vypis(bool jednoduchy_vypis);

/* smaže uložené statistiky */
bool stats_vymaz(void);

/* uvolní dynamicky alokovanou
   paměť v rámci modulu statistik */
void stats_vycisti(void);


#endif
