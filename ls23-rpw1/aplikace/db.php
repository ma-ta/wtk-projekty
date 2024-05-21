<?php

/*************************/
/* K O N F I G U R A C E */
/*************************/

$db_host = "localhost";  // IP či doména DBMS serveru
$db_jmeno = "root";      // jméno pro přihlášení k DB
$db_heslo = "";          // heslo pro přihlášení k DB
$db_databaze = "rpw";    // název DB

/*************************/


// PDO(mysql:host=localhost;dbname=test;charset=utf8", $user, $pass)
try {
    $db = new PDO("mysql:host=" . $db_host . ";charset=utf8;dbname=" . $db_databaze, $db_jmeno, $db_heslo);
}
catch (PDOException $e) {
    echo("Chyba připojení k databázi: " . $e);
}
?>
