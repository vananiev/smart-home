<?php
$mshost = "localhost"; // Хост
$msuser = "---"; 	// Имя пользователя
$mspassword = "---"; 	// Пароль
$msname = "---"; 	// Имя базы данных

//подключение к серверу БД
$msconnect = mysql_connect($mshost, $msuser, $mspassword) or die(mysql_error());

//если нет БД то создаем ее
mysql_query("CREATE DATABASE IF NOT EXISTS $msname CHARACTER SET utf8",$msconnect) or die(mysql_error());

//выбор БД
mysql_select_db($msname,$msconnect) or die(mysql_error());
?>