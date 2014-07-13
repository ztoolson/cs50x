<div class = "table-responsive">
    <table class="table tablesorter table-striped table-bordered table-condensed" id="myTable">
        <thead>
            <tr>
                <th>Symbol</td>
                <th>Name</td>
                <th>Shares</td>
                <th>Current Price</td>
                <th>Total</td>
            </tr>
        </thead>
        <tbody>
            <?php
                foreach ($positions as $stock)
                {
                    print("<tr>");
                    print("<td>" . $stock["symbol"] . "</td>");
                    print("<td>" . $stock["name"] . "</td>");
                    print("<td>" . $stock["shares"] . "</td>");
                    print("<td> $" . $stock["price"] . "</td>");
                    print("<td> $" . number_format( floatval($stock["price"]) * intval($stock["shares"]), 2) . "</td>");
                    print("</tr>");
                }
            ?>

            <tr>
                <td>CASH</td>
                <td></td>
                <td></td>
                <td></td>
                <td>$<?= number_format($cash, 2) ?></td>
            </tr>
        </tbody>
    </table>
</div>
