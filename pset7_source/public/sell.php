<?php
    /*
     * Controller for users to look up stocks.
     */

    // configuration
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate form
        $requested = intval($_POST["amount"]);
        if ($_POST["symbol"] === "")
        {
            apologize("Please select a stock to sell");
        }
        else if (!is_numeric($_POST["amount"]) || $requested < 0)
        {
            apologize("Please enter a valid number of stocks to sell");
        }

        // query db for shares owned 
        $shares_query = query("SELECT shares FROM users_stocks WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]); 
        
        if (empty($shares_query))
        {
            apologize("Error accessing stock. Please try again");
        }

        // save number of shares as an integer
        $shares_owned = intval($shares_query[0]["shares"]);

        // check number of shares requested is less than or equal to amount owned.
        if ($shares_owned < $requested)
        {
            apologize("Requesting to sell more shares than you own");
        } 

        $updated_shares = $shares_owned - $requested;

        // sell the shares
        // get price from yahoo
        $yhoo_results = lookup($_POST["symbol"]);
        $price = floatval($yhoo_results["price"]);

        // calculate the price for the shares.
        $profit = $requested * $price;
        
        // update share amount in db
        query("UPDATE users_stocks SET shares = ? WHERE id = ? AND symbol = ?", $updated_shares, $_SESSION["id"], $_POST["symbol"]); 

        // update users cash amount
        query("UPDATE users SET cash = cash + ? WHERE id = ?", $profit, $_SESSION["id"]);

        // save transaction in history
        query("INSERT INTO users_history (id, transaction, trans_time, symbol, shares, price) VALUES(?, ?, NOW(), ?, ?, ?)",
            $_SESSION["id"],
            "SELL",
            $yhoo_results["symbol"],
            $requested,
            $yhoo_results["price"]);

        render("sell_result.php", 
            ["title" => "Successful Sale",
            "profit" => $profit,
            "symbol" => $_POST["symbol"],
            "shares" => $updated_shares,
            "requested" => $requested]);

    }
    else
    {
        // before rendering, get list of all stocks to be sold.
        $rows = query("SELECT symbol FROM users_stocks WHERE id = ?", $_SESSION["id"]);

        $symbols = [];
        foreach ($rows as $row)
        {
            array_push($symbols, $row["symbol"]);
        }

        // render form
        render("sell_form.php", 
            ["title" => "Sell",
             "symbols" => $symbols]);
    }

?>
