<?php

    //configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["current_password"]))
        {
            apologize("You must provide your current password.");
        }
        else if (empty($_POST["new_password"]))
        {
            apologize("You must provide your new password.");
        }
        else if (empty($_POST["new_confirmation"]))
        {
            apologize("You must confirm your new password.");
        }
        
        // check current_password is correct
        $row = query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"]);
        $current_hash = $row[0]["hash"];

        if (crypt($_POST["current_password"], $current_hash) !== $current_hash)
        {
            apologize("Current password entered is incorrect");
        }
        
        // confirm new_password and confirmation are the same
        if ($_POST["new_password"] !== $_POST["new_confirmation"])
        {
            apologize("New password and confirmation did not match.");
        }

        // enter new password into the database
        query("UPDATE users SET hash = ? WHERE id = ?", crypt($_POST["new_password"]), $_SESSION["id"]); 
         
        // redirect to portfolio
        render("change_password_result.php", ["title" => "Success"]);
    }
    else
    {
        // render form
        render("change_password_form.php", ["title" => "Change Password"]);
    }

?>
