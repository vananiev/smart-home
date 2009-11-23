<?php
session_start();	

include "DB.php";

//изменяем данные
if (isset($_POST['login']) && isset($_POST['password']) && isset($_SESSION['user_id']))
	{
	$login = mysql_real_escape_string($_POST['login']);
	$pass=$_POST['password'];
	$password = md5($_POST['password']);
	mysql_query("UPDATE user SET login='{$login}',password='{$password}' WHERE id='{$_SESSION['user_id']}'", $msconnect) or die("Ошибка. Попробуйте еще раз.<br>".mysql_error());
	echo "Ваши данные изменены: <br>";
	echo "Логин: ".$login."<br>";
	echo "Пароль: ".$pass."<br>";
	}
else
	echo "Не введены логин и пароль или вы не вошли в систему под своим именем.";
	
	//закрываем БД
	mysql_close($msconnect);
echo "<br><a href=\"index.php\">[ok]</a>";
?>