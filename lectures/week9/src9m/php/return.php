<?php

    /**
     * return.php
     *
     * David J. Malan
     * malan@harvard.edu
     *
     * Cubes a variable.
     *
     * Demonstrates use of parameter and return value.
     */

    $x = 2;
    printf("x is now %d\n", $x);
    printf("Cubing...\n");
    $x = cube($x);
    printf("Cubed!\n");
    printf("x is now %d\n", $x);

    /**
     * Cubes argument.
     */
    function cube($n)
    {
        return $n * $n * $n;
    }

?>
