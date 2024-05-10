<?php
session_start();
include("db.php");
include("funkce.php");
include("onload.php");
?>

<!DOCTYPE html>
<html lang="cs">
    <head>
        <meta charset="utf-8" />
        <meta name="viewport" content="width=device-width, initial-scale=1" />

        <!-- styly -->
        <link rel="stylesheet" href="libs/bootstrap/bootstrap.css" />
        <link rel="stylesheet" href="style.css" />
        <!-- licence: Apache License, Version 2.0 | https://fonts.google.com/specimen/Roboto+Slab/about?query=roboto+slab -->
        <link href='https://fonts.googleapis.com/css?family=Roboto+Slab:400,700&subset=latin,latin-ext' rel='stylesheet' type='text/css' />

        <!-- skripty -->
        <script src="libs/jquery-3.7.1.min.js"></script>
        <script src="libs/bootstrap/bootstrap.min.js"></script>

        <title><?php echo(NAZEV_STRANKY); ?></title>
    </head>

    <body>

        <div class="container" id="container">

            <div class="header clearfix">
                <nav>

                    <ul class="nav nav-pills pull-xs-right">
                        <li id="navTlacitko-domu" class="nav-item">
                            <a class="nav-link btn" onclick="navigace('domu')">Domů</a>
                        </li>
                        <li id="navTlacitko-info" class="nav-item">
                            <a class="nav-link btn" onclick="navigace('info')">Pravidla a informace</a>
                        </li>
                        <li id="navTlacitko-kontakt" class="nav-item">
                            <a class="nav-link btn" onclick="navigace('kontakt')">Kontakt</a>
                        </li>
                    </ul>
                </nav>
                <h3><?php echo(NADPIS); ?></h3>
            </div>

            <div id="ajax">
                <!-- include -->
            </div>
            <footer class="footer" style="color: #194166; text-align: center;">
                <p><?php echo(COPYRIGHT); ?></p>
            </footer>

        </div> <!-- /container -->

        <script>
            // JS funkce

            navigace();
            function navigace(obsah, blank) {
                if (!obsah) {
                    $("#ajax").load("domu.php");
                    $("#navTlacitko-domu").addClass("active");
                } else {
                    if (!blank) {

                        $("#ajax").load(obsah+".php");
                        $("[id^='navTlacitko-']").removeClass("active");
                        $("#navTlacitko-"+obsah).addClass("active");

                        $("#stav").fadeOut(5000, function() {
                            $(this).remove();
                        });

                    } else if (blank == true) {
                        window.open(obsah + ".php");
                    }
                }
            }

            function vepisZnak(znak, element) {
                $('#' + element).val(($('#' + element).val()) + znak);
                $('#' + element).focus();
            }

        </script>
    </body>
</html>
