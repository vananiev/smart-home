<?php

@set_time_limit(0);  //скрипт выполняется бесконечно
ob_implicit_flush();   //выводим echo  по мере поступления ответа, а не в конце работы скрипта

	
include "DB.php";

//поиск пользователя
if (isset($_POST['login']) && isset($_POST['password']))
{
	$login = mysql_real_escape_string($_POST['login']);
  	$password = md5($_POST['password']);

    // делаем запрос к БД
    // и ищем юзера с таким логином и паролем
    $query = "SELECT id
            FROM user
            WHERE login='{$login}' AND password='{$password}'
            LIMIT 1";
    $sql = mysql_query($query,$msconnect) or die(mysql_error());

    // если такой пользователь нашелся и он один
    if (mysql_num_rows($sql) == 1) {
	//обработка
	$ip=$_SERVER['REMOTE_ADDR'];  //определяем ip обратившегося
	echo "Ваш ip: ".$ip."<br>";

	if(trim($_GET['port']) == NULL)  //если порт не указан
		$port=12001;
	else
		$port=trim($_GET['port']);
	//соединяемся
	@$fp = fsockopen ($ip, $port, $errno, $errstr, 30);

	if (!$fp) {
		echo "Ошибка в процессе выполнения: не удалось подключиться к серверу.<br><br>";
		echo "Источник ошибки:<br>";
		echo "$errstr ($errno)<br>";} 
	else{
		//если ip совпал с "локальным адресом", то последний удаляем
		if($ip == trim($name))
			$name = NULL;
		
		echo "Передаем ваш ip программе.<br><br>";
		$name=$_GET['name'];
		if(trim($name)==NULL)
			fputs ($fp, $ip);
		else
			fputs ($fp, "to ".$name." ".$ip);
	
		//ответы сервера
		while(!feof($fp)){
			$ans = fgets ($fp,1024);
			$ans=trim($ans);
			echo "Ответ:  ".$ans."<br>";
			if($ans == 'exit')
				break;
			}
		fclose ($fp);
		
		//заносим в БД
		mysql_query("UPDATE user SET ip='{$ip}',local_ip='{$name}',port='{$port}'
            		WHERE login='{$login}' AND password='{$password}'
            		LIMIT 1",$msconnect);
		echo "Комманда была успешно выполнена.";
		}
	}
    	else{ 
        	echo "Такой логин с паролем не найдены в базе данных.<br>";
		//обработка ошибки пароля
		$ip=$_SERVER['REMOTE_ADDR'];  //определяем ip обратившегося

		if(trim($_Get['port']) == NULL)  //если порт не указан
			$port=12001;
		else
			$port=trim($_Get['port']);
		//соединяемся
		@$fp = fsockopen ($ip, $port, $errno, $errstr, 30);

		if (!$fp) {
			echo "Ошибка в процессе выполнения: не удалось подключиться к серверу.<br><br>";
			echo "Источник ошибки:<br>";
			echo "$errstr ($errno)<br>";} 
		else{
			if(trim($name)==NULL)
				fputs ($fp, "Неверный пароль.");
			else
				fputs ($fp, "to ".$name." "."Неверный пароль.");
	
			//ответы сервера
			while(!feof($fp)){
				$ans = fgets ($fp,1024);
				$ans=trim($ans);
				echo "Ответ:  ".$ans."<br>";
				if($ans == 'exit')
					break;}
			}
		fclose ($fp);}
}else
	echo "Введите пароль.";

//закрываем БД
	mysql_close($msconnect);
?>
