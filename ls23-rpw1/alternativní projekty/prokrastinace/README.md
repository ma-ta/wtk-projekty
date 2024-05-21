# Hra Š I _ E _ I C E

*Původním záměrem bylo vytvoření multiplatformní "retro" hry pro platformy
od MS-DOS,  UN\*X,  WINDOWS až po webové prohlížeče za využití technologie
WebAssembly (resp. emscripten.org).
Bohužel, prozatím se mi nezdařilo adaptovat zejména vstupy uživatele tak,
aby hra běžela v browserech (JS) a chovala se podobně jako v terminálu.*


![Šibenice – ikona](/res/github.png)

### Popis a stručné instrukce
Známá slovní hra (alias Oběšenec, Hangman) založená na hádání jednotlivých písmen tajného slova.
Program je napsán v jazyce ANSI C a pro jeho spuštění by neměly být potřeba žádné nestandardní knihovny.

- **[Základní instrukce k sestavení](how_make.txt)**
- [Nápověda ke hře](/res/napoveda.txt)
- [Známé chyby a nápady na další vývoj](/res/poznamky.txt)


### Binárky ke stažení

- **[All-in-1 řešení ZIP](https://github.com/ma-ta/BTWA1/releases/download/v1.0.0/sibenice_1.0.0_bin.zip)**
- [Složka s binárkami](bin/)


#### Pro systémy typu MS-DOS
V případě zobrazení hlášky *"Load error: no DPMI - Get csdpmi\*.zip"* umístěte soubor [CWSDPMI.EXE](/bin/CWSDPMI.EXE) do stejného adresáře jako spustitelný soubor hry. Více o problematice např. [zde](//en.wikipedia.org/wiki/CWSDPMI) nebo [zde](https://sandmann.dotster.com/cwsdpmi/).


#### Testované platformy *(kompilátory)*:
- UN*X:
  - Ubuntu 24.04 LTS *(GNU GCC 13.2.0) – [x86_64]*
  - FreeBSD 14 *(LLVM/Clang 16.0.6) – [x86_64]*
- MS Windows:
  - Windows 11 *(MSVC 19.39.33523) – [x86][x86_64]*
- DOS:
  - FreeDOS 1.3 *(DJGPP 4.7.1)*
  - DOSBox 0.74-3
  - MS-DOS 6.22

### Snímky obrazovky

- [Všechny dostupné screenshoty zde](/res/screenshots)

Hlavní menu:

![Šibenice – Menu](/res/screenshots/menu.png)

Obrazovka hry:

![Šibenice – Hra](/res/screenshots/hra.png)

Herní statistiky:

![Šibenice – Statistiky](/res/screenshots/kronika.png)

Obrazovka hry (DOS – 25x80 znaků):

![Šibenice – MS-DOS](res/screenshots/hra-dos.png)

Informace o verzi (DOS):

![Šibenice – MS-DOS](res/screenshots/prepinace-dos.png)
