<?php

    // open connection to Yahoo
    $handle = @fopen("http://download.finance.yahoo.com/d/quotes.csv?f=snl1&s={$_GET["symbol"]}", "r");
    if ($handle === false)
    {
        // trigger (big, orange) error
        trigger_error("Could not connect to Yahoo!", E_USER_ERROR);
        exit;
    }

    // download first line of CSV file
    $data = fgetcsv($handle);
    if ($data === false || count($data) == 1)
    {
        return false;
    }

    // close connection to Yahoo
    fclose($handle);

    // ensure symbol was found
    if ($data[2] === "0.00")
    {
        return false;
    }

    // prepare stock as an associative array
    $stock = [
        "symbol" => $data[0],
        "name" => $data[1],
        "price" => $data[2],
    ];

    // output stock as JSON
    header("Content-Type: application/json");
    print(json_encode($stock));

?>
