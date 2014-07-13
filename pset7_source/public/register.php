<?php

    //configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must confirm your password.");
        }
        else if ($_POST["password"] !== $_POST["confirmation"])
        {
            apologize("Passwords did not match.");
        }

        // insert user into the database. will return false if query does not execute
        $query_result = query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)",
                              $_POST["username"], 
                              crypt($_POST["password"]));
        
        // check if error registering new user. 
        if ($query_result === false)
        {
            apologize("Username has been taken. Please login or register with a different username");
        }

        // get id from the database
        $rows = query("SELECT LAST_INSERT_ID() as id");
        $id = $rows[0]["id"];

        // if registration suceeds, log in the user
        $_SESSION["id"] = $id;

        // redirect to portfolio
        redirect("/");


    }
    else
    {
        //else render form
        render("register_form.php", ["title" => "Register"]);
    }

?>
