<?php if ($requested  == 1) : ?>
    Successfully sold <?= $requested ?>  share of <?= $symbol ?> for $<?= $profit ?>.
<?php else : ?>
    Successfully sold <?= $requested ?>  shares of <?= $symbol ?> for $<?= $profit ?>.
<?php endif; ?>
<br/>
You have <?= $shares ?> shares left.
