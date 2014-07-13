<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select class="form-control" name="symbol">
                <option value=""></option>
                <?php
                    foreach($symbols as $symbol)
                    {
                        print("<option value='{$symbol}'>{$symbol}</option>");
                    }
                ?>
            </select>
        </div>

        <div class="form-group">
            <input class="form-control" name="amount" placeholder="# of stocks" type="text"/>
        </div>

        <div class="form-group">
            <button type="submit" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
</form>
