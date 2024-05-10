<?php session_start(); ?>
<?php include("funkce.php"); ?>

<div class="jumbotron" style="padding-left: 20%; background-color: #F0F0F0;">
    <div style="width: 80%;">
        <h4>Zadejte svoji poptávku</h4>
    </div>

    <form action="#" method="post" id="registrace" name="registrace" style="width: 80%; text-align: left;">
        <fieldset class="form-group">
            <label for="jmeno">Jméno a příjmení (firma)<span class="poznamka">*</span>:</label>
            <input class="form-control povinne-pole" type="text" name="jmeno" id="jmeno" maxlength="200" required placeholder="Jméno PŘÍJMENÍ" autofocus />

            <label for="email">Kontaktní e-mail<span class="poznamka">*</span>:</label>
            <div class="input-group">
                <div title="Vložit zavináč" class="input-group-addon btn-success" style="cursor: pointer;" onclick="vepisZnak('@', 'email')">@</div>
                <input class="form-control povinne-pole" type="email" name="email" id="email" placeholder="@" maxlength="200" required />
            </div>

            <label for="telefon">Telefon (vč. předvolby):</label>
            <input class="form-control" type="tel" name="telefon" id="telefon" placeholder="+420" maxlength="18" />


            <label for="profil">Váš web/profil:</label>
            <input class="form-control" type="text" placeholder="www" name="profil" id="profil" maxlength="200" />


            <label for="castka">Rámcová nabídka:</label>
            <div class="input-group">

                <input placeholder="Částka v korunách" class="form-control" type="number" name="castka" id="castka" min="0" step="1" />
                <div class="input-group-addon">CZK</div>
            </div>
            <a tabindex="-1" style="background-color: transparent; cursor: pointer; color: #194166" title="Aktuální devizové kurzy dle ČNB" href="//www.cnb.cz" target="_blank">Kurzy měn ČNB</a>
            |
            <a tabindex="-1" style="background-color: transparent; cursor: pointer; color: #194166" title="Aktuální kurz Bitcoinu (CoinMarketCap.com)" href="//coinmarketcap.com" target="_blank">Kurz Bitcoinu<span id="kurzBTC"></span></a>
            <br /><br />


            <label for="zprava">Zpráva:</label>
            <textarea placeholder="Dobrý den," style="height: 10rem"class="form-control" name="zprava" id="zprava"></textarea>

        </fieldset>
        <fieldset class="form-group">
            <label for="souhlas">Souhlasím s <a style="background-color: transparent; cursor: pointer; color: #194166" title="Pravidla a informace" onclick="navigace('info', true)">podmínkami</a><span class="poznamka">*</span>:</label>
            <input class="povinne-pole" style="width: 20px; height: 20px;" type="checkbox" name="souhlas" id="souhlas" required />
            <br /><br />

            <p>Bezpečnostní prvek<span class="poznamka">*</span>:</p>

            <div class="form-group form-inline">


                <input style="width: 25%; min-width: 70px;" class="form-control" tabindex="-1" value="<?php
                if (isset($_SESSION['jablko']))
                    echo($_SESSION['jablko']);
                else
                    echo('Chyba');
                ?>" type="text" id="jablko" name="jablko" readonly />
                <span style="width: 10%;">&nbsp;&nbsp;a&nbsp;&nbsp;</span>
                <input style="width: 25%; min-width: 70px;" class="form-control" tabindex="-1" value="<?php
                if (isset($_SESSION['hruska']))
                    echo($_SESSION['hruska']);
                else
                    echo('Chyba');
                ?>" type="text" id="hruska" name="hruska" readonly />
                <span style="width: 10%;">&nbsp;&nbsp;je&nbsp;&nbsp;</span>
                <input style="width: 30%; min-width: 70px;" class="form-control povinne-pole" placeholder="(&bdquo;arabsky&ldquo;)" type="text" id="jablkohruska" name="jablkohruska" autocomplete="off" required />
            </div>
        </fieldset>


        <input class="form-control btn btn-lg btn-success" type="submit" name="potvrdit" value="Potvrdit" id="btn-potvrdit" />
        </fieldset>
        <br /><br />
        <span class="poznamka">*<span style="font-weight: normal;"> Značí povinnou položku</span></span>

    </form>

</div>

<script>

    function escapeHtml(text) {
        return text
         .replace(/&/g, "&amp;")
         .replace(/</g, "&lt;")
         .replace(/>/g, "&gt;")
         .replace(/"/g, "&quot;")
         .replace(/'/g, "&#039;");
    }

</script>
