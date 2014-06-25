<?php

    /**
     * conditions-1.php
     *
     * David J. Malan
     * malan@harvard.edu
     *
     * Tells user if his or her input is positive, zero, or negative.
     *
     * Demonstrates use of if-else construct.
     */

    // ask user for an integer
    $n = readline("I'd like an integer please: ");

    // analyze user's input
    if ($n > 0)
    {
        printf("You picked a positive number!\n");
    }
    else if ($n == 0)
    {
        printf("You picked zero!\n");
    }
    else
    {
        printf("You picked a negative number!\n");
    }

?>
