CREATE TABLE IF NOT EXISTS `pset7`.`users_stocks` (
  `id` int(10) unsigned NOT NULL,
  `symbol` char(15) NOT NULL,
  `shares` int(30) NOT NULL,
  PRIMARY KEY (`id`, `symbol`)
)
