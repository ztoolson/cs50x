CREATE TABLE IF NOT EXISTS `pset7`.`users_history` (
  `id` int(10) unsigned NOT NULL,
  `transaction` char(4) NOT NULL,
  `trans_time` datetime NOT NULL,
  `symbol` char(15) NOT NULL,
  `shares` int(30) NOT NULL,
  `price` decimal(65, 4) NOT NULL,
  PRIMARY KEY (`id`, `trans_time`, `symbol`)
)
