<?php
	set_time_limit(0);  //скрипт выполняется бесконечно
    	ob_implicit_flush();   //выводим echo  по мере поступления ответа, а не в конце работы скрипта

	@$fp = fsockopen ($_GET['ip'], $_GET['port'], $errno, $errstr, 1);

if (!$fp) {
	echo "Ошибка в процессе выполнения: не удалось подключиться к серверу.<br><br>";
	echo "Источник ошибки:<br>";
	echo "$errstr ($errno)<br>";
	} 
else{
	echo "Передача серверу:  ".$_GET['cmd']."<br>";
	fputs ($fp, $_GET['cmd']);
	
	//ответы сервера
	do{
		$d="";
		$ans="";
		do{
			$ans=$ans.$d;
			$d = fgets ($fp,2);
		}while($d != '#');		//завершение мысли
		echo "Ответ:  ".$ans."<br>";
	}while($ans != 'exit');
	
	fclose ($fp);
	
	echo "Комманда была успешно выполнена.";
	}
?>