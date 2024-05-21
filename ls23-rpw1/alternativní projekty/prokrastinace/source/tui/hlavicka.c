#include <stdio.h>
#include <string.h>
#include "../globconf.h"

static const char *hlavicka_obr = TUI_HLAVICKA_OBR;

void hlavicka_vykresli(const char *text1, const char *text2)  {

  char s_pom[] = { '\0', '\0' };  /* pomocný řetězec pro převod znaku na string */
  char oramovani[TUI_HLAVICKA_BUNKA_L + TUI_HLAVICKA_BUNKA_P + 3 + 1] = ""; /* (+3 = počet křížení, +1 = '\0') */
  char titulek_l[TUI_HLAVICKA_BUNKA_L + 1] = "";
  int  mezer_l = (TUI_HLAVICKA_BUNKA_L - (int) strlen(text1)) / 2;
  char titulek_p[TUI_HLAVICKA_BUNKA_P + 1] = "";
  int  mezer_p = (TUI_HLAVICKA_BUNKA_P - (int) strlen(text2)) / 2;
  int  i       = 0;


  /* ověření maximální délky textu */
  if (strlen(text1) > TUI_HLAVICKA_BUNKA_L) {
    fprintf(stderr,
            ERR_SIGN ERR_TUI_HLAVICKA_TXTMAX "\n"
            ,"(1.)"
            , TUI_HLAVICKA_BUNKA_L);
    return;
  }
  if (strlen(text2) > TUI_HLAVICKA_BUNKA_P) {
    fprintf(stderr,
            ERR_SIGN ERR_TUI_HLAVICKA_TXTMAX "\n"
            ,"(2.)"
            , TUI_HLAVICKA_BUNKA_P);
    return;
  }

  /* orámování */

  s_pom[0] = UKAZATELE_ORAMOVANI_KRIZENI_ZN;
  strncat(oramovani, s_pom, sizeof(oramovani) - sizeof(char));
  for (i = 0; i <= (int) (TUI_HLAVICKA_BUNKA_L + TUI_HLAVICKA_BUNKA_P); i++) {
    s_pom[0] = (i == TUI_HLAVICKA_BUNKA_L) ? UKAZATELE_ORAMOVANI_KRIZENI_ZN : UKAZATELE_ORAMOVANI_ZN;
    strncat(oramovani,
            s_pom,
            sizeof(oramovani) - sizeof(char));
  }
  strncat(oramovani, (s_pom[0] = UKAZATELE_ORAMOVANI_KRIZENI_ZN, s_pom), sizeof(oramovani) - sizeof(char));

  /* zpracování levé buňky */

  for (i = 0; i < mezer_l; i++) {
    strcat(titulek_l, " ");
  }
  strcat(titulek_l, text1);
  while (strlen(titulek_l) < (size_t) TUI_HLAVICKA_BUNKA_L) {
    strcat(titulek_l, " ");
  }

  /* ověření, zda šlo zarovnat titulek přesně na střed buňky */
  if ((strlen(text1) % 2 == 0) != (TUI_HLAVICKA_BUNKA_L % 2 == 0)) {
    fprintf(stderr,
            ERR_SIGN ERR_TUI_HLAVICKA_ZAROV "\n"
            "    strlen( \"%s\" ) == %ld zn.\n"
            , text1
            , strlen(text1));
  }

  /* zpracování pravé buňky */

  for (i = 0; i < mezer_p; i++) {
    strcat(titulek_p, " ");
  }
  strcat(titulek_p, text2);
  while (strlen(titulek_p) < (size_t) TUI_HLAVICKA_BUNKA_P) {
    strcat(titulek_p, " ");
  }

  /* ověření, zda šlo zarovnat titulek přesně na střed buňky */
  if ((strlen(text2) % 2 == 0) != (TUI_HLAVICKA_BUNKA_P % 2 == 0)) {
    fprintf(stderr,
            ERR_SIGN ERR_TUI_HLAVICKA_ZAROV "\n"
            "    strlen( \"%s\" ) == %ld zn.\n"
            , text2
            , strlen(text2));
  }

  /* vykreslení hlavičky */

  printf(hlavicka_obr
         , oramovani, titulek_l, titulek_p, oramovani);
}
