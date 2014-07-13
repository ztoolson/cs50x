<?php

    // configuration
    require("../includes/config.php");
    
    // get list of all stocks a user currently holds shares in 
    $rows = query("SELECT transaction, trans_time, symbol, shares, price  FROM users_history WHERE id = ? ORDER BY trans_time", $_SESSION["id"]);

    // render transaction history
    render("history_result.php", 
        ["title"    => "History",
        "positions" => $rows]
    );

?>
