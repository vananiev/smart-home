<?php
@session_start();	

include "DB.php";

//удаляем пользователя
if (isset($_SESSION['user_id']))
	{
	mysql_query("DELETE FROM user WHERE id='{$_SESSION['user_id']}'", $msconnect) or die("Ошибка. Попробуйте еще раз.<br>".mysql_error());
	echo "Ваша учетная запись удалена. <br>";
	unset($_SESSION['user_id']);
	session_unregister('user_id');
	}
else
	echo "Авторизуйтесь.";
	
	//закрываем БД
	mysql_close($msconnect);
echo "<br><a href=\"index.php\">[ok]</a>";
?>