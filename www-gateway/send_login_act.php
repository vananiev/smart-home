<?php
session_start();

set_time_limit(0);  //скрипт выполняется бесконечно
ob_implicit_flush();   //выводим echo  по мере поступления ответа, а не в конце работы скрипта

include "DB.php";

if(isset($_SESSION['user_id'])){
	$query = "SELECT *
            FROM user
            WHERE id='{$_SESSION['user_id']}'";
    	$sql = mysql_query($query,$msconnect) or die(mysql_error());
	$row = mysql_fetch_assoc($sql);
        $ip = $row['ip'];
	$port = $row['port'];
	$local_ip=$row['local_ip'];
}else{
	$login = mysql_real_escape_string($_POST['login']);
  	$password = md5($_POST['password']);
	$query = "SELECT *
            FROM user
            WHERE login='{$login}' AND password='{$password}'";
    	$sql = mysql_query($query,$msconnect) or die(mysql_error());
	//пользователь найден
	if (mysql_num_rows($sql) == 1){
		$row = mysql_fetch_assoc($sql);
        	$ip = $row['ip'];
		$port = $row['port'];
		$local_ip=$row['local_ip'];}
	else
		die('Такой логин с паролем не найдены в базе данных.'); 
}
	@$fp = fsockopen ($ip, $port, $errno, $errstr, 30);

	if (!$fp) {
		echo "Ошибка в процессе выполнения: не удалось подключиться к серверу.<br><br>";
		echo "Источник ошибки:<br>";
		echo "$errstr ($errno)<br>";
		} 
	else{
		if(trim($local_ip)!='')
			$cmd="to ".$local_ip." ".$_POST['key']." ".trim($_POST['cmd']);
		else
			$cmd=$_POST['key']." ".trim($_POST['cmd']);

		echo "Передача серверу:  ".$_POST['cmd']."<br>";
		fputs ($fp, $cmd);
	
		//ответы сервера
		while(!feof($fp)){
			$ans = fgets ($fp,1024);
			$ans=trim($ans);
			if($ans == 'exit')
				break;
			echo "Ответ:  ".$ans."<br>";
			}
		fclose ($fp);
		}
//закрываем БД
mysql_close($msconnect);

echo "<br><a href=\"index.php\">[ok]</a>";	
?>