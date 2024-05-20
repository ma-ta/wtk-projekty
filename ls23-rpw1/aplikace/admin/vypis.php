<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <link rel="stylesheet" type="text/css" href="normalize.css" />
    <!-- licence: Apache License, Version 2.0 | https://fonts.google.com/specimen/Roboto+Slab/about?query=roboto+slab -->
    <link href='https://fonts.googleapis.com/css?family=Roboto+Slab:400,700&subset=latin,latin-ext' rel='stylesheet' type='text/css' />
    <link rel="stylesheet" type="text/css" href="style-vypis.css" />
    <link rel="icon" type="image/x-icon" href="../res/logo.svg">
    <title>Výpis databáze zájemců</title>
</head>
<body>
    <?php
        include('db.php');
        define("TABULKA", "zajemci");
    ?>
    
    <br />
    <div id="obsah">
        
    <button onclick="location.reload()">Obnovit</button>
    <br />
    
    <h1><span style="color: #194166;">Výpis databáze</span><?php echo(" <em style='color: #8d0010;'>" . $databaze . "</em>"); ?></h1>
    <table>
        <caption><?php echo("<em>tabulka: " . TABULKA . "</em>"); ?></caption>
        <tr>
            <th id="th1">ID</th>
            <th id="th2">Datum registrace</th>
            <th id="th3">Jméno</th>
            <th id="th4">E-mail</th>
            <th id="th5">Telefon</th>
            <th id="th6">Web/Profil</th>
            <th id="th7"><span style="text-decoration: underline;">Částka</span>&nbsp;&nbsp;&#x2193;</th>
            <th id="th8">Zpráva</th>
            <th id="th9">Doména</th>
            <th id="th10">IP</th>
            <th id="th11">OS</th>
            <th id="th12">Prohlížeč</th>
            <th id="th13">User-Agent</th>
            <th id="th14">Heslo ke komunikaci</th>
        </tr>

        <?php
            $sql_dotaz = "SELECT * FROM ". TABULKA . " ORDER BY castka DESC";
            $sql_vysledek = $db->prepare($sql_dotaz);
            $sql_vysledek->execute();

            foreach (($sql_vysledek->fetchAll(PDO::FETCH_ASSOC)) as $radek) {
                echo("<tr>");
                $i = 0;
                foreach ($radek as $sloupecek) {
                    echo('<td id="td' . (++$i) . '">' . nl2br(htmlspecialchars($sloupecek)) . "</td>");
                }
                echo("</tr>");
            }
        ?>
    </table>

    </div>
</body>
</html>
