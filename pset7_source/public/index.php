<?php

    // configuration
    require("../includes/config.php");
    
    // get list of all stocks a user currently holds shares in 
    $rows = query("SELECT * FROM users_stocks WHERE id = ? ORDER BY symbol", $_SESSION["id"]);

    // for each purchased stock, get price and name from yahoo!
    $positions = [];
    foreach ($rows as $row)
    {
        // lookup yahoo reuslts using sybmol
        $stock = lookup($row["symbol"]);

        if ($stock !== false)
        {
            $positions[] = [
                "name"   => $stock["name"],
                "price"  => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
                ];
        }
    }

    // get users cash amount
    $q = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);

    // render portfolio
    render("portfolio.php", 
        ["title"    => "Portfolio",
        "positions" => $positions,
        "cash"      => floatval($q[0]["cash"])]
    );

?>
