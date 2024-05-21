@echo off

::::::::::::::::::::::::::::::::::::::::
::                                    ::
::  SKRIPT NA SESTAVENI HRY SIBENICE  ::
::  (DOS/BATCH/DJGPP)                 ::
::                                    ::
::  autor:  Martin TABOR (Ma-TA)      ::
::  datum:  2024-05-05                ::
::                                    ::
::::::::::::::::::::::::::::::::::::::::


::::::::::::::::::::::::::::::::::::::::
:: KONFIGURACE:
::::::::::::::::::::::::::::::::::::::::


:: nazev spustitelneho souboru
   set bin_nazev=sibe_dos

:: parametry prekladace
   :: debug:    -Wall -Wextra -pedantic -g
   :: release:  -O2
   set cc_param=-O2

:: korenovy adresar se zdrojovymi kody
   set src_dir=.\source

:: korenovy adresar pro binarni soubory
   set out_dir=.\bin

:: oramovani
   set oramovani=----------------------------------


::::::::::::::::::::::::::::::::::::::::


cls

echo %oramovani%
echo SESTAVUJI - Vypis chyb a udalosti:
echo %oramovani%
echo.

:: zkopiruje slozku data do slozky bin
   mkdir %out_dir%\data
   xcopy %src_dir%\data %out_dir%\data /E /S

:: kompilace jednotlivych souboru

:: korenovy adresar
   cd %src_dir%
   gcc %cc_param% -c *.c
   cd ..
   move %src_dir%\*.o %out_dir%
:: slozka game
   cd %src_dir%\game
   gcc %cc_param% -c *.c
   cd ..\..
   move %src_dir%\game\*.o %out_dir%
:: slozka game\game_tui
   cd %src_dir%\game\game_tui
   gcc %cc_param% -c *.c
   cd ..\..\..
   move %src_dir%\game\game_tui\*.o %out_dir%
:: slozka help
   cd %src_dir%\help
   gcc %cc_param% -c *.c
   cd ..\..
   move %src_dir%\help\*.o %out_dir%
:: slozka menu
   cd %src_dir%\menu
   gcc %cc_param% -c *.c
   cd ..\..
   move %src_dir%\menu\*.o %out_dir%
:: složka stats
   cd %src_dir%\stats
   gcc %cc_param% -c *.c
   cd ..\..
   move %src_dir%\stats\*.o %out_dir%
:: slozka tui
   cd %src_dir%\tui
   gcc %cc_param% -c *.c
   cd ..\..
   move %src_dir%\tui\*.o %out_dir%

:: sestaveni spustitelneho souboru
   cd %out_dir%
   gcc %cc_param% -o %bin_nazev%.exe *.o
   del *.o
   cd ..

echo.
echo %oramovani%
echo.

:: spusteni sestaveneho programu
   %out_dir%\%bin_nazev%.exe -v

:: vyckani na stisk klavesy
   echo.
   echo %oramovani%
   echo.
   pause
