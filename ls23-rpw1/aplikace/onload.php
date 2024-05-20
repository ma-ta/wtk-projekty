<?php
if (isset($_SESSION["jablko"])) {
    $jablko = $_SESSION["jablko"];
    $jablko_val = $_SESSION["jablko_val"];
    $nahodneCislo = nahodneCislo();
    $_SESSION["jablko"] = $nahodneCislo[0];
    $_SESSION["jablko_val"] = $nahodneCislo[1];
} else {
    $nahodneCislo = nahodneCislo();
    $_SESSION["jablko"] = $nahodneCislo[0];
    $_SESSION["jablko_val"] = $nahodneCislo[1];

    // zjištění, z které stránky uživatel poprvé přišel
    if ((isset($_SERVER["HTTP_REFERER"])) && (!empty($_SERVER["HTTP_REFERER"])))
        $_SESSION["referer"] = htmlspecialchars($_SERVER["HTTP_REFERER"]);
    else
        $_SESSION["referer"] = "";
    // zaznamenání první návštěvy
    $sql_dotaz = "INSERT INTO navstevnici (ip, os, browser, useragent) "
            . "VALUES (:ip, :os, :browser, :useragent)";
    $sql_vysledek = $db->prepare($sql_dotaz);
    $navstevnik = navstevnik(); // array(os, browser, user-agent)
    $sql_vysledek->execute(array(":ip" => zjistiIP(), 
        ":os" => $navstevnik[0], ":browser" => $navstevnik[1], ":useragent" => $navstevnik[2]));
}

if (isset($_SESSION["hruska"])) {
    $hruska = $_SESSION["hruska"];
    $hruska_val = $_SESSION["hruska_val"];
    $nahodneCislo = nahodneCislo();
    $_SESSION["hruska"] = $nahodneCislo[0];
    $_SESSION["hruska_val"] = $nahodneCislo[1];
} else {
    $nahodneCislo = nahodneCislo();
    $_SESSION["hruska"] = $nahodneCislo[0];
    $_SESSION["hruska_val"] = $nahodneCislo[1];
}

// zpracování formuláře
if (isset($_POST["potvrdit"])) {
    if ((!empty($_POST["jmeno"])) && (!empty($_POST["email"])) && (isset($_POST["souhlas"])) && (!empty($_POST["jablkohruska"]))) {
        if ((isset($_POST["jablkohruska"]) && (isset($jablko_val))) && (($_POST["jablkohruska"]) == ($jablko_val + $hruska_val))) {
            //deklarace
            $jmeno = "";
            $email = "";
            $telefon = "";
            $profil = "";
            $heslo = generujHeslo(6);
            $castka = null;
            $zprava = "";
            $souhlas = "";
            $ip = zjistiIP();

            $jmeno = htmlspecialchars(trim(chop($_POST["jmeno"])));
            $email = strtolower(htmlspecialchars(trim(chop($_POST["email"]))));

            if (isset($_POST["telefon"]))
                $telefon = htmlspecialchars(str_replace(" ", "", $_POST["telefon"]));

            if (isset($_POST["profil"]))
                $profil = strtolower(htmlspecialchars(trim(chop($_POST["profil"]))));

            if (isset($_POST["castka"]))
                $castka = htmlspecialchars($_POST["castka"]);

            if (isset($_POST["zprava"]))
                $zprava = htmlspecialchars(trim(chop($_POST["zprava"])));

            if (isset($_POST["souhlas"]))
                $souhlas = $_POST["souhlas"];

            switch ($souhlas) {
                case "on":
                    $souhlas = 1;
                    break;
                default:
                    $souhlas = 0;
            }

            $hashHesla = $heslo; //hash("sha256", $heslo);

            include("db.php");
            if (!isset($db)) {
                include("formular-chyba.php");
                exit;
            }

            $sql_dotaz = "INSERT INTO zajemci (jmeno, email, telefon, profil, heslo, castka, zprava, domena, ip, os, browser, useragent) 
                VALUES (:jmeno, :email, :telefon, :profil, :heslo, :castka, :zprava, :domena, :ip, :os, :browser, :useragent)";

            $sql_vysledek = $db->prepare($sql_dotaz);
            $navstevnik = navstevnik();
            $sql_vysledek->execute(array(
                ":jmeno" => $jmeno,
                ":email" => $email,
                ":telefon" => $telefon,
                ":profil" => $profil,
                ":heslo" => $hashHesla,
                ":castka" => $castka,
                ":zprava" => $zprava,
                ":domena" => DOMENA,
                ":ip" => $ip,
                ":os" => $navstevnik[0],
                ":browser" => $navstevnik[1],
                ":useragent" => $navstevnik[2]));

            posli_potvrzeni($jmeno, $email, $telefon, $profil, $heslo, $castka, $zprava);
            echo("<div id='stav' style='color: #449d44; background-color: #DDFFDD'><p><strong>HOTOVO</strong>
                <br />Opište si prosím své heslo:&nbsp;<span style='font-weight: bold; text-decoration: underline; font-family: Courier New, monospace; background-color: #FFF; padding: 5px; color: #00AA00; margin-left: 3px; margin-right: 3px;'>" . $heslo . "</span>!</p>"
            . "<p style='margin-top: 10px; border-radius: 8px; padding: 10px; background-color: #BBEEBB;'>Budeme Vás kontaktovat, a to buď pomocí e-mailu nebo uvedeného telefonního čísla.</p></div>");

        } else {
            echo("<div id='stav' style='color: #8d0010; background-color: #FFDDDD''><p><strong>Bohužel jste chybně vyplnili bezpečnostní prvek.</strong></p></div>");
        }
    } else {
        echo("<div id='stav' style='color: #8d0010; background-color: #FFDDDD''><p><strong>Nevyplnili jste všechny potřebné údaje.</strong></p></div>");
    }
}
?>
