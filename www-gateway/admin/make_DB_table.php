<?php

include "DB.php";

//создаем тавлицу
mysql_query("CREATE TABLE user ( 
	id int(10) unsigned NOT NULL auto_increment,
	login varchar(50) NOT NULL default '',
	password varchar(32) NOT NULL default '',
	ip varchar(15)NOT NULL default '',
	port int(5),
	local_ip varchar(64)NOT NULL default '',
	mail varchar(50),
	fone int(11),
	a varchar(50),
	b int(10),
	c DATETIME,
	d DATETIME,
	e TEXT,
	PRIMARY KEY  (`ID`)
	)",$msconnect) or die(mysql_error()); 
echo "Make ok";
mysql_close($msconnect);
?>
