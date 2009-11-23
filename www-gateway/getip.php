<?php
	@set_time_limit(0);  //скрипт выполняется бесконечно
    	ob_implicit_flush();   //выводим echo  по мере поступления ответа, а не в конце работы скрипта

	$ip=$_SERVER['REMOTE_ADDR'];  //определяем ip обратившегося
	echo "Ваш ip: ".$ip."<br>";

	if(!isset($_GET['port']))  //если порт не указан
		$port=12001;
	else
		$port=trim($_GET['port']);
	if(!isset($_GET['name']))  //если порт не указан
		$name=NULL;
	else
		$name=trim($_GET['name']);

	//соединяемся
	@$fp = fsockopen ($ip, $port, $errno, $errstr, 30);

if (!$fp) {
	echo "Ошибка в процессе выполнения: не удалось подключиться к серверу.<br><br>";
	echo "Источник ошибки:<br>";
	echo "$errstr ($errno).<br>";
	} 
else{
	//если ip совпал с "локальным адресом", то последний удаляем
	if($ip == trim($name))
		$name = NULL;
	
	echo "Передаем ваш ip программе.<br><br>";
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
	echo "Комманда была успешно выполнена.";
	}
?>
