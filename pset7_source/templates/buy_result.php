<?php if ($shares  == 1) : ?>
    Successfully bought <?= $shares ?>  share of <?= $symbol ?> for $<?= number_format($price, 2) ?>.
<?php else : ?>
    Successfully bought <?= $shares ?>  shares of <?= $symbol ?> for $<?= number_format($price, 2) ?>.
<?php endif; ?>
