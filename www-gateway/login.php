<?php
@session_start();

include "DB.php";

//поиск пользовател€
if (isset($_POST['login']) && isset($_POST['password']))
{
	$login = mysql_real_escape_string($_POST['login']);
  	$password = md5($_POST['password']);

    // делаем запрос к Ѕƒ
    // и ищем юзера с таким логином и паролем
    $query = "SELECT id
            FROM user
            WHERE login='{$login}' AND password='{$password}'
            LIMIT 1";
    $sql = mysql_query($query,$msconnect) or die(mysql_error());

    // если такой пользователь нашелс€ и он один
    if (mysql_num_rows($sql) == 1) {
        // то мы ставим об этом метку в сессии (допустим мы будем ставить ID пользовател€)
        $row = mysql_fetch_assoc($sql);
        $_SESSION['user_id'] = $row['id'];        // не забываем, что дл€ работы с сессионными данными, у нас в каждом скрипте должно присутствовать session_start();
    	echo "ƒобро пожаловать, $login!";
	echo "<a href=\"index.php\">[ok]</a>";
	}
    else {
	echo "“акой логин с паролем не найдены в базе данных.";
    }
}
	//закрываем Ѕƒ
	mysql_close($msconnect);
?>

