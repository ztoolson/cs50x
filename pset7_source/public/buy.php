<?php
    /*
     * Controller for users to look up stocks.
     */

    // configuration
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate form
        if (empty($_POST["symbol"]))
        {
            apologize("You must specify a stock to buy.");
        }
        else if (empty($_POST["amount"]))
        {
            apologize("You must specify the number of shares.");
        }
        else if (!preg_match("/^\d+$/", $_POST["amount"]))
        {
            apologize("Enter a valid number of stocks to buy.");
        }
        
        $requested = intval($_POST["amount"]);
        $yhoo_results = lookup($_POST["symbol"]);
        
        // verify stock is valid
        if(empty($yhoo_results))
        {
            apologize("Please enter a valid stock symbol");
        }

        // can the user afford this transaction?
        $cash_needed = floatval( $requested * floatval($yhoo_results["price"]) );

        $user_row = query("SELECT username, cash FROM users WHERE id = ?", $_SESSION["id"]);
        if (empty($user_row))
        {
            apologize("Database error when calculating user cash");
        }

        if( $cash_needed > floatval($user_row[0]["cash"]))
        {
            apologize("You cannot afford this transaction.");
        }

        // perform transaction
        query("INSERT INTO users_stocks (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)",
                $_SESSION["id"],
                $yhoo_results["symbol"],
                $_POST["amount"]);

        // update cash
        query("UPDATE users SET cash = cash - ? WHERE id = ?", $cash_needed, $_SESSION["id"]);

        // save transaction in history
        query("INSERT INTO users_history (id, transaction, trans_time, symbol, shares, price) VALUES(?, ?, NOW(), ?, ?, ?)",
            $_SESSION["id"],
            "BUY",
            $yhoo_results["symbol"],
            $_POST["amount"],
            $yhoo_results["price"]);

        render("buy_result.php", 
            ["title" => "Buy Success",
             "shares" => $_POST["amount"],
             "symbol" => $yhoo_results["symbol"],
             "price" => $cash_needed]);

    }
    else
    {
        // else render form
        render("buy_form.php", ["title" => "Buy"]);
    }

?>
