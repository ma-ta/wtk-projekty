<?php session_start();?>

<?php
$regJmeno = "admin";
$regHeslo = "abc";

function zobrazFormular() {
    echo('
        <form action="#" method="post">
            <label for="jmeno">Jméno:</label><input id="jmeno" name="jmeno" type="text" placeholder="uživatel" required autofocus />
            <label for="heslo">Heslo:</label><input id="heslo" name="heslo" type="password" placeholder="heslo" required />
            <input type="submit" name="submit" value="Potvrdit" />
        </form>
    ');
}


if (isset($_POST["submit"])) {
    if((isset($_POST["jmeno"])) && (isset($_POST["heslo"]))) {
        $_SESSION["jmeno"] = htmlspecialchars($_POST["jmeno"]);
        $heslo = htmlspecialchars($_POST["heslo"]);

        if(($_SESSION["jmeno"] == $regJmeno) && ($heslo == $regHeslo)) {
            unset($heslo);
            session_regenerate_id();
            $_SESSION["prihlasen"] = true;
        }
        else {
            echo("<p class='status-chyba'>Zadal jste špatné přihlašovací údaje!</p>");
        }
    }
}

if(isset($_POST["odhlasit"])) {
    session_regenerate_id();
    $_SESSION["prihlasen"] = false;
    session_destroy();
}

if((isset($_SESSION["prihlasen"])) && ($_SESSION["prihlasen"] == true)) {
    echo("<p class='status-ok'>Jste přihlášen jako <strong>".$_SESSION["jmeno"]."</strong>!</p>");
}

?>

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <title>Výpis databáze zájemců</title>
    <link rel="stylesheet" type="text/css" href="style.css" />
</head>
<body>
    <div id="obsah">
        <h1>Přihlášení</h1>
        <?php
        if(!isset($_SESSION["prihlasen"])) {
            zobrazFormular();
        }
        else {
            if($_SESSION["prihlasen"] == true) {
                session_destroy();
                header('Location: vypis.php');
            }
            else {
                zobrazFormular();
            }
        }
        ?>
    </div>
</body>
</html>
