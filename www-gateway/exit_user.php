<?php
	@session_start();	
	unset($_SESSION['user_id']);
	session_unregister('user_id') or die("Ошибка попытайтесь еще раз.");
	echo "Выход успешно выполнен.";
	echo "<a href=\"index.php\">[ok]</a>";
?> 	