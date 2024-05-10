<?php
    define("DOMENA", "Název domény");
?>

<!DOCTYPE html>
<html lang="cs">
<head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <link href="https://fonts.googleapis.com/css?family=Sanchez&amp;subset=latin-ext" rel="stylesheet" />
    <link rel="stylesheet" type="text/css" href="style.css" />
    <script src="script.js"></script>
    <title><?php echo(DOMENA); ?></title>
</head>
<body>

<div id="content">
    <form action="#" method="post" name="kontaktni-form" id="kontaktniForm">
        <input type="email" title="Zadejte Vaši e-mailovou adresu" onfocus="vpis()" autocomplete="off" required placeholder="Váš e-mail" name="kontakt" id="kontakt" />
        <br />
        <input type="submit" value="Odeslat" id="odeslat" name="odeslat" />
    </form>

</div>

</body>
</html>
