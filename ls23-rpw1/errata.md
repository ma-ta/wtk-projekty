# Nedostatky

- aplikace by měla být koncipována jako cílová destinace pro přesměrování z mnoha různých domén
  (lze tak provozovat jednu instanci, na niž budou návštěvníci přesměrováni z různých domén provozovatele)
  - tzn. název domény získávat např. z HTTP hlavičky
  - přizpůsobit databázi a backend
- propojit DB tabulku zájemců (odesilatelů poptávkového formuláře) s anonymními návštěvami webu
  (využitelné např. pro statistiky, kolikrát zájemce web navštivil, než odeslal formulář)
- ideálně automatizovat prodej domény&nbsp;&ndash;&nbsp;např. propojení s platební bránou (po odsouhlasení částky majitelem může dojít ke stržení blokace
  na debetní kartě a automatizovanému přepisu DNS záznamu přesně dle informací vyplněných samotným zájemcem do zvláštního formuláře)
