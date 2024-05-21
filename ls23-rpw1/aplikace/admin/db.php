<?php

/*************************/
/* K O N F I G U R A C E */
/*************************/

$host = "localhost";  // IP či doména DBMS serveru
$jmeno = "root";      // jméno pro přihlášení k DB
$heslo = "";          // heslo pro přihlášení k DB
$databaze = "rpw";    // název DB

/*************************/


// PDO(mysql:host=localhost;dbname=test;charset=utf8", $user, $pass)
try {
    $db = new PDO("mysql:host=".$host.";charset=utf8;dbname=".$databaze, $jmeno, $heslo);
    if ($db) {
        echo("<div class='status' style='background-color: #5cb85c; color: #fff; font-weight: bold;'>
            Připojeno k databázi.</div>");
    }
}
catch (PDOException $e) {
    echo("<div class='status' style='background-color: #8d0010; color: #fff; font-weight: bold;'>
        Chyba připojení k databázi:<br />(".$e->getMessage().").</div>");
    exit;
}

?>
