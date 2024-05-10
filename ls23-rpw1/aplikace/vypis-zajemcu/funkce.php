<?php

// funkce vrátí IP adresu klienta
function zjistiIP() {
    $ipaddress = "";

    if (isset($_SERVER["HTTP_CLIENT_IP"]))
        $ipaddress = htmlspecialchars($_SERVER["HTTP_CLIENT_IP"]);
    else if(isset($_SERVER["HTTP_X_FORWARDED_FOR"]))
        $ipaddress = htmlspecialchars($_SERVER["HTTP_X_FORWARDED_FOR"]);
    else if(isset($_SERVER["HTTP_X_FORWARDED"]))
        $ipaddress = htmlspecialchars($_SERVER["HTTP_X_FORWARDED"]);
    else if(isset($_SERVER["HTTP_FORWARDED_FOR"]))
        $ipaddress = htmlspecialchars($_SERVER["HTTP_FORWARDED_FOR"]);
    else if(isset($_SERVER["HTTP_FORWARDED"]))
        $ipaddress = htmlspecialchars($_SERVER["HTTP_FORWARDED"]);
    else if(isset($_SERVER["REMOTE_ADDR"]))
        $ipaddress = htmlspecialchars($_SERVER["REMOTE_ADDR"]);
    else
        $ipaddress = "NEZNÁMÁ";

    return $ipaddress;
}

function nahodnyRetezec($delka_hesla)
{
    $vystup = "";
    $mozne_znaky = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    $pocet_moznych_znaku = mb_strlen($mozne_znaky)-1;
    for($i=0;$i<=$delka_hesla;$i++)
    {
        $vystup .= $mozne_znaky[mt_rand(0,$pocet_moznych_znaku)];
    }
    return $vystup;
}

?>
