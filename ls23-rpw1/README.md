# Ročníkový projekt I. (KRPW1)

> Microsite s formulářem, databází s registrem zájemců a automaticky generovaným e-mailem

### Požadavky (testovaná konfigurace)

#### Server (backend)
 - Apache HTTP Server 2.4.59,
 - PHP 8.3.7,
 - MariaDB 10.11.6.

#### Browser (frontend)
- Google Chrome 125,
- Microsoft Edge 125,
- Mozilla Firefox 126.

### Použité knihovny (závislosti)
- Bootstrap 5.3.3
- jQuery 3.7.1

### Nasazení aplikace
1. Importujte soubor __/k projektu/databaze.sql__ (obsahuje připravené tabulky) do své databáze,
2. editujte __db.php__ dle nastavení konkrétního serveru,
3. v souboru __config.php__ upravte konstanty s názvem stránek, domény, e-mail a copyright (zápatí),
4. jakmile stránky zpřístupníte na localhostu, můžete zkusit experimentovat &ndash; editovat text, vyměnit pozadí etc.
