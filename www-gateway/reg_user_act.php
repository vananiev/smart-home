<?php
@session_start();	

include "DB.php";

//добавляем пользователя
if (isset($_POST['login']) && isset($_POST['password']))
	{
	$login = mysql_real_escape_string($_POST['login']);
	$pass=$_POST['password'];
	$password = md5($_POST['password']);
	//нет ли другого пользователя с таким логином
	$query = "SELECT login
            FROM user
            WHERE login='{$login}'
            LIMIT 1";
    	$sql = mysql_query($query,$msconnect) or die(mysql_error());

    // если такой пользователь не нашелся
    	if (mysql_num_rows($sql) > 0)
		echo "Этот логин занят. Введите другой и попробуйте еще раз.";
	else{
		mysql_query("INSERT INTO user (id,login,password) VALUES(id,'{$login}','{$password}')", $msconnect) or die("Ошибка. Попробуйте еще раз.<br>".mysql_error());
		echo "Вы зарегестрированы: <br>";
		echo "Логин: ".$login."<br>";
		echo "Пароль: ".$pass."<br>";}		
	}
else
	echo "Введите логин и пароль.";
	
	//закрываем БД
	mysql_close($msconnect);
echo "<br><a href=\"index.php?adr=reg_user.php\">[ok]</a>";
?>
