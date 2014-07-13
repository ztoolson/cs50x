<!DOCTYPE html>

<html>

    <head>
        <meta charset="utf-8">

        <link href="/css/bootstrap.min.css" rel="stylesheet"/>
        <link href="/css/bootstrap-theme.min.css" rel="stylesheet"/>
        <link href="/css/styles.css" rel="stylesheet"/>

        <?php if (isset($title)): ?>
            <title>C$50 Finance: <?= htmlspecialchars($title) ?></title>
        <?php else: ?>
            <title>C$50 Finance</title>
        <?php endif ?>

        <script src="/js/jquery-1.10.2.min.js"></script> 
        <script src="/js/bootstrap.min.js"></script>
        <script src="/js/scripts.js"></script>

        <meta name="viewport" content="width=device-width, initial-scale=1">
    </head>

    <body>
        <nav class="navbar navbar-defualt navbar-static-top" role="navigation">
            <div class="container-fluid">
                <div class="navbar-header">
                    <a class="navbar-brand" href="/">Portfolio</a>
                    <a class="navbar-brand" href="quote.php">Quote</a>
                    <a class="navbar-brand" href="buy.php">Buy</a>
                    <a class="navbar-brand" href="sell.php">Sell</a>
                    <a class="navbar-brand" href="history.php">History</a>
                </div> 
            </div>
        </nav>

        <div class="container">

            <div id="top">
                <a href="/"><img alt="C$50 Finance" src="/img/logo.gif"/></a>
            </div>

            <div id="middle">
