<?php if ($requested  == 1) : ?>
    Successfully sold <?= $requested ?>  share of <?= $symbol ?> for $<?= $profit ?>.
<?php else : ?>
    Successfully sold <?= $requested ?>  shares of <?= $symbol ?> for $<?= $profit ?>.
<?php endif; ?>
<br/>
You have <?= $shares ?> shares left.
<div>
    <br/>
    make another <a href="sell.php">sale</a>.
    <br/>
    return to <a href="/">portfolio</a>.
</div>
