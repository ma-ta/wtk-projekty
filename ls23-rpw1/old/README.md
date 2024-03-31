### Koncept projektu: Výuka psaní na klávesnici

#### 1. rešerše:
   - konkurence (kvantita, kvalita &ndash; výukové a technické metodologie)
   - vhodný název (tzn. registrace domény)
   - zámýšlení uživatelé (zákazníci) &ndash; jednotlivci / firmy / školy
     - prostudovat fungování Seznamu registrovaného výukového sw MŠMT (!)
       - https://www.msmt.cz/file/7895_1_1/download/
       - https://ondrej.neumajer.cz/jak-se-vybira-software-do-skol/
       - atd.
   - nastudovat odbornou problematiku domény (výuky psaní):
     - výukové metody, cíle, hodnocení postupu studenta, &hellip; (tzn. rešerše dostupné literatury)
     - technická specifika periferií (normy klávesnic, velikost bufferu, přenos do PC (latence...), zpracování vstupu v prostředí browseru/JS, &hellip;)

#### 2. technická realizace:
   - zvolit rozsah (modularitu, rozšiřitelnost) projektu - zřejmě co nejflexibilnější
   - HTML5 & CSS3 & JavaScript (frameworky ?) + Java (backend) + DBMS (PostgreSQL ?)
     / příp. Electron pro možnost instalace na desktop (při zachování multiplatformity a kompatibility s www)

- umožnit opis z obrazovky i přepis mluveného slova (tzn. strojové čtení - existuje volný sw s vhodnou licencí ?)
  - pakliže se podaří zajistit startovní podmínky pro implementaci přepisu mluveného slova, zvážit přípravu celého produktu
    pro potřeby disabilních studentů (rozhraní pro slabozraké) = KONKURENČNÍ VÝHODA (?!?)
