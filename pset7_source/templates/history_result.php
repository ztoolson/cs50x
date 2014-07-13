<div class = "table-responsive">
    <table class="table tablesorter table-striped table-bordered table-condensed" id="myTable">
        <thead>
            <tr>
                <th>Transaction</td>
                <th>Date/Time</td>
                <th>Symbol</td>
                <th>Shares</td>
                <th>Price</td>
            </tr>
        </thead>
        <tbody>
            <?php
                foreach ($positions as $stock)
                {
                    print("<tr>");
                    print("<td>" . $stock["transaction"] . "</td>");
                    print("<td>" . date_format(date_create($stock["trans_time"]), 'n/j/Y, g:ia') . "</td>");
                    print("<td>" . $stock["symbol"] . "</td>");
                    print("<td>" . $stock["shares"] . "</td>");
                    print("<td> $" . number_format($stock["price"], 2) . "</td>");
                    print("</tr>");
                }
            ?>
        </tbody>
    </table>
</div>
