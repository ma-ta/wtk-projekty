/*
 *  ANSI ESCAPE KÓDY PRO TERMINÁL
 *
 *  V terminálových emulátorech s podporou ANSI sekvencí
 *  umožňuje formátování textu, navigaci kurzoru apod.
 *
 */


#ifndef ANSI_FMT_H
#define ANSI_FMT_H


#define CSI  "\033["  /* ANSI escape kód */
#define SGR  "m"      /* pro nastavení SGR parametrů */

/* vlastnosti */

#define ANSI_RESET      "0"   /* RESET */
#define ANSI_BOLD       "1"   /* tučný text */
#define ANSI_ULINE      "4"   /* jednoduché podtržení */
#define ANSI_BLICK      "5"   /* blikající text */
#define ANSI_BLICK_OFF  "25"
#define ANSI_INVER      "7"   /* prohodí barvy pozadí a popředí */
#define ANSI_INVER_OFF  "27"


/* barvy */

#define ANSI_FRCOLOR  "3"  /* prefix pro barvu textu */
#define ANSI_BGCOLOR  "4"  /* prefix pro barvu pozadí */

#define ANSI_RED      "1"  /* červená */
#define ANSI_GREEN    "2"  /* zelená */
#define ANSI_YELLOW   "3"  /* žlutá */
#define ANSI_BLUE     "4"  /* modrá */
#define ANSI_MAGENTA  "5"  /* purpurová */
#define ANSI_CYAN     "6"  /* tyrkysová */
#define ANSI_WHITE    "7"  /* bílá */
#define ANSI_BLACK    "0"  /* černá */

#define ANSI_LIGHT     ";1"  /* světlejší varianta barvy */
#define ANSI_COLOR_OFF  "9"  /* implicitní barva */

/* kurzor */

#define ANSI_UP     "A"
#define ANSI_DOWN   "B"
#define ANSI_LEFT   "D"
#define ANSI_RIGHT  "C"
#define ANSI_UPBGN  "F"
#define ANSI_DWBGN  "E"

#define ANSI_SCROLLUP  "S"
#define ANSI_SCROLLDW  "T"

#define ANSI_ERASE_TOEND  "0"
#define ANSI_ERASE_TOBGN  "1"
#define ANSI_ERASE_ALL    "2"

/* makra */

#if ANSI_FORMAT == 1
  #define ansi_format(format)       CSI format SGR
  /* použije se např. jako parametr ansi_frcolor() nebo ansi_bgcolor() */
  #define ansi_light(color)         color ANSI_LIGHT
  #define ansi_frcolor(color)       CSI ANSI_FRCOLOR color SGR
  #define ansi_bgcolor(color)       CSI ANSI_BGCOLOR color SGR
  #define ansi_cursor_off()         CSI "?25l"
  #define ansi_cursor_on()          CSI "?25h"
#else
  #define ansi_format(format)       ""
  #define ansi_light(color)         ""
  #define ansi_frcolor(color)       ""
  #define ansi_bgcolor(color)       ""
  #define ansi_cursor_off()         ""
  #define ansi_cursor_on()          ""
#endif

#define ansi_scroll(mode, count)  CSI #count mode
#define ansi_cursor(mode, count)  CSI #count mode
#define anxi_x(col)               CSI #col "G"
#define ansi_position(row, col)   CSI #row ";" #col "H"
#define ansi_save_pos()           CSI "s"
#define ansi_load_pos()           CSI "u"
#define ansi_erase_ln(mode)       CSI mode "K"
#define ansi_erase_scr(mode)      CSI mode "J"


#endif
/* konec souboru ansi_fmt.h */
