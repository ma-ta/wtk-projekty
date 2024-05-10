<?php

include("config.php");

$user_agent = "";
if(isset($_SERVER['HTTP_USER_AGENT']))
    $user_agent = $_SERVER['HTTP_USER_AGENT'];

// funkce vrátí IP adresu klienta
function zjistiIP() {
    $ipaddress = "";

    if (isset($_SERVER["HTTP_CLIENT_IP"]))
        $ipaddress = htmlspecialchars($_SERVER["HTTP_CLIENT_IP"]);
    else if (isset($_SERVER["HTTP_X_FORWARDED_FOR"]))
        $ipaddress = htmlspecialchars($_SERVER["HTTP_X_FORWARDED_FOR"]);
    else if (isset($_SERVER["HTTP_X_FORWARDED"]))
        $ipaddress = htmlspecialchars($_SERVER["HTTP_X_FORWARDED"]);
    else if (isset($_SERVER["HTTP_FORWARDED_FOR"]))
        $ipaddress = htmlspecialchars($_SERVER["HTTP_FORWARDED_FOR"]);
    else if (isset($_SERVER["HTTP_FORWARDED"]))
        $ipaddress = htmlspecialchars($_SERVER["HTTP_FORWARDED"]);
    else if (isset($_SERVER["REMOTE_ADDR"]))
        $ipaddress = htmlspecialchars($_SERVER["REMOTE_ADDR"]);
    else
        $ipaddress = "NEZNÁMÁ";

    return $ipaddress;
}

function navstevnik() {
    
    global $user_agent;

    function getOS() {

        global $user_agent;

        $os_platform = "Neznámý OS";
        $os_array = array(
            '/windows nt 10/i' => 'Windows 10/11',
            '/windows nt 6.3/i' => 'Windows 8.1',
            '/windows nt 6.2/i' => 'Windows 8',
            '/windows nt 6.1/i' => 'Windows 7',
            '/windows nt 6.0/i' => 'Windows Vista',
            '/windows nt 5.2/i' => 'Windows Server 2003/XP x64',
            '/windows nt 5.1/i' => 'Windows XP',
            '/windows xp/i' => 'Windows XP',
            '/windows nt 5.0/i' => 'Windows 2000',
            '/windows me/i' => 'Windows ME',
            '/win98/i' => 'Windows 98',
            '/win95/i' => 'Windows 95',
            '/win16/i' => 'Windows 3.11',
            '/macintosh|mac os x/i' => 'Mac OS X',
            '/mac_powerpc/i' => 'Mac OS 9',
            '/linux/i' => 'Linux',
            '/ubuntu/i' => 'Ubuntu',
            '/iphone/i' => 'iPhone',
            '/ipod/i' => 'iPod',
            '/ipad/i' => 'iPad',
            '/android/i' => 'Android',
            '/blackberry/i' => 'BlackBerry',
            '/webos/i' => 'Mobile'
        );

        foreach ($os_array as $regex => $value) {

            if (preg_match($regex, $user_agent)) {
                $os_platform = $value;
            }
        }

        return $os_platform;
    }

    function getBrowser() {

        global $user_agent;

        $browser = "Neznámý prohlížeč";
        $browser_array = array(
            '/chrome/i' => 'Chrome',
            '/edge/i' => 'Edge',
            '/safari/i' => 'Safari',
            '/firefox/i' => 'Firefox',
            '/opera/i' => 'Opera',
            '/mobile/i' => 'Handheld Browser',
            '/msie/i' => 'Internet Explorer'
        );

        foreach ($browser_array as $regex => $value) {

            if (preg_match($regex, $user_agent)) {
                $browser = $value;
            }
        }

        return $browser;
    }

    $user_os = getOS();
    $user_browser = getBrowser();

    return array(htmlspecialchars($user_os), htmlspecialchars($user_browser), htmlspecialchars($user_agent));
}

function nahodnyRetezec($delka_hesla) {
    $vystup = "";
    $mozne_znaky = "#";
    $pocet_moznych_znaku = mb_strlen($mozne_znaky) - 1;
    for ($i = 0; $i <= $delka_hesla-1; $i++) {
        $vystup .= $mozne_znaky[mt_rand(0, $pocet_moznych_znaku)];
    }
    return $vystup;
}
function generujHeslo($min_delka) {
    $vystup = "";

    try {
        $lines = file("slovnik.txt");

        while ((mb_strlen($vystup)) < $min_delka) {
            $cislo_radku = mt_rand(1, count($lines));
            $pole = explode("/", $lines[$cislo_radku]);
            $vystup = mb_strtolower($pole[0]);
            $vystup = trim(chop($vystup));
            $vystup .= nahodnyRetezec(1);
            for ($i = 0; $i < 2; $i++) {
                $vystup .= mt_rand(0,9);
            }
        }
    }
    catch(Exception $e) {
        include("formular-chyba.php");
        exit;
    }

    return $vystup;
}

function nahodneCislo() {

    $cislovky = array(
        0  => "nula",
        1  => "jedna",
        2  => "dva",
        3  => "tři",
        4  => "čtyři",
        5  => "pět",
        6  => "šest",
        7  => "sedm",
        8  => "osm",
        9  => "devět",
        10 => "deset"
    );

    $cislo = mt_rand(0, 10);
    $slovo = $cislovky[$cislo];

    return (array($slovo, $cislo));
}

// odeslání potvrzujícího mailu
function posli_potvrzeni($jmeno, $email, $telefon, $profil, $heslo, $castka, $zprava) {

    define("KOPIE_1", "");

    $predmet = "Potvrzení poptávky o doménu (" . DOMENA . ")";

    $hr = "<hr style='color: #194166'; />";

    try {
        $text = file_get_contents("mail.html");

        $text .= "<p style='font-size: 110%;'>Dobrý den,</p>";
        $text .= "\n<p style='font-size: 110%;'>potvrzujeme úspěšné odeslání formuláře na stránkách ";
        $text .= "<a style='color: #194166' target='_blank' title='náš web' href='http:" . strtolower(DOMENA) . "'>" . strtolower(DOMENA) . "</a>.";
        $text .= " Budeme Vás kontaktovat v nejkratší možné době.</p><br />";

        $text .= "\n<p style='font-size: 110%;'>Vaše heslo pro komunikaci: <span style='color: #194166;'><strong>" . $heslo . "</strong></span></p>";
        $text .= "\n<br />" . $hr;
        $text .= "\n<h3 style='color: #194166;'>Poskytnuté údaje:</h3>";

        $text .= "\n<table style='font-family: Georgia, Verdana, sans-serif; font-size: 110%;' class='tab-udaje' border='0'><tr><td>Identifikace: </td><td style='padding-left: 20px; color: #8d0010;'>" . $jmeno . "</td></tr>";
        $text .= "\n<tr><td>E-mail: </td><td style='padding-left: 20px; color: #8d0010;'>" . $email . "</td></tr>";
        $text .= "\n<tr><td>Telefon: </td><td style='padding-left: 20px; color: #8d0010;'>" . $telefon . "</td></tr>";
        $text .= "\n<tr><td>Web: </td><td style='padding-left: 20px; color: #8d0010;'>" . $profil . "</td></tr>";
        $text .= "\n<tr><td>Nabídka: </td><td style='padding-left: 20px; color: #8d0010;'>" . $castka . " Kč</td></tr>";
        $text .= "\n<tr><td>&nbsp;</td><td>&nbsp;</td></tr>";
        $text .= "\n<tr><td valign='top'>Zpráva: </td><td style='padding-left: 20px; color: #8d0010;'>" . nl2br($zprava) . "</td></tr></table><br />";
        $text .= "\n" . $hr . "<br />";
        $text .= "\n--\n<p>S přáním pěkného dne<br />Tým webu " . DOMENA . "</p>";
        $text .= "\n<br><p><em>Pro odvolání souhlasu se zpracováním osobních údajů nás kontaktujte přes tento e-mail (" . ADRESA_MAILU . ").</em></p>";
        $text .= "\n</body>\n</html>";


        // zájemce
        $headers = "Content-Type: text/html; charset=UTF-8" . "\r\n";
        $headers .= "From: <" . ADRESA_MAILU . ">" . "\r\n";
        mail($email, "=?UTF-8?B?" . base64_encode($predmet) . "?=", $text, $headers);
    } catch (Exception $ex) {

    }
}


?>
