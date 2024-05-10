<?php include("funkce.php"); ?>

<div class="jumbotron">
    <div style="width: 80%; margin: auto; color: #000; text-align: left;">
        <h3>Tento web provozuje:</h3>
        <p class="lead" style="text-align: center;">Naše огромная firma s.r.o.<br>
        registrovaná na Daňových ostrovech</p>
        <span style="text-align: center;"><?php include("tlacitko.php"); ?></span>
        <div class="row marketing">
            <div class="col-lg-6">
                <h4>E-mail</h4>
                <p><a style="padding: 10px;" href="<?php echo("mailto:".ADRESA_MAILU); ?>" title="Zaslat e-mail"><?php echo(ADRESA_MAILU); ?></a></p>
            </div>
        </div>
    </div>
</div>
