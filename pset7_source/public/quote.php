<?php
    /*
     * Controller for users to look up stocks.
     */

    // configuration
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $quote_results = lookup($_POST["symbol"]);

        // could not get results
        if (empty($quote_results["name"]) || empty($quote_results["symbol"]) || empty($quote_results["price"]))
        {
            apologize("Symbol not found");
        }
        // results found. print them
        else
        {
            render("quote_result.php", ["title" => "Quote Results", 
                "q_symbol" => $quote_results["symbol"],
                "q_name" => $quote_results["name"],
                "q_price" => $quote_results["price"] ]);
        }
    }
    else
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }

?>
