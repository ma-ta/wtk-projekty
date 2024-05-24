<?php

/*************************/
/* K O N F I G U R A C E */
/*************************/

/* TODO: název získávat automatizovaně např. z HTTP hlavičky
   jedna instance aplikace (1 hosting) by měla podporovat mnoho domén (pomocí přesměrování) */
define("DOMENA",        "DrahaDomena.com");            // zobrazovaný název domény (k prodeji)

define("ADRESA_WEBU",   "//localhost/webprojekt");     // url adresa stránek
define("JMENO_AUTORA",  "Martin TÁBOR");               // jméno provozovatele stránek (resp. vlatníka) v patičce webu
define("ADRESA_MAILU",  "tym@" . strtolower(DOMENA));  // zobrazovaná e-mailová kontaktní adresa provozovatele (majitele)
define("NADPIS",        DOMENA);                       // nadpis home page
define("NAZEV_STRANKY", DOMENA);                       // title v hlavičce stránky
// copyrithg v patičce webu
define("COPYRIGHT",     "&copy&nbsp;" . strftime("%Y", Time()) . "&nbsp;&nbsp;" . JMENO_AUTORA . "<br />" . NAZEV_STRANKY);

/*************************/

?>
