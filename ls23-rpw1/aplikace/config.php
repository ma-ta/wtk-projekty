<?php
// konfigurace
define("ADRESA_WEBU", "//localhost/webprojekt");
define("JMENO_AUTORA", "Martin TÁBOR");
define("DOMENA", "DrahaDomena.com");
define("ADRESA_MAILU", "tym@" . strtolower(DOMENA));
define("NADPIS", DOMENA);
define("NAZEV_STRANKY", DOMENA);
define("COPYRIGHT", "&copy&nbsp;" . strftime("%Y", Time()) . "&nbsp;&nbsp;" . JMENO_AUTORA . "<br />" . NAZEV_STRANKY);
?>
