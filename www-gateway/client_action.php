<?php
	set_time_limit(0);  //скрипт выполняется бесконечно
    	ob_implicit_flush();   //выводим echo  по мере поступления ответа, а не в конце работы скрипта

	@$fp = fsockopen ($_POST['ip'], $_POST['port'], $errno, $errstr, 30);

if (!$fp) {
	echo "Ошибка в процессе выполнения: не удалось подключиться к серверу.<br><br>";
	echo "Источник ошибки:<br>";
	echo "$errstr ($errno)<br>";
	} 
else{
	echo "Передача серверу:  ".$_POST['cmd']."<br>";
	$cmd = trim($_POST['cmd']);
	if(substr($cmd,0,2) == 'на' || substr($cmd,0,2) == 'to'){	//если отсылаем команду по лс
		$c = substr($cmd,0,2); //выделяем эту комманду
		$cmd=substr($cmd,3); //отсекаем эту команду
		$cmd=trim($cmd);
		$arg=substr($cmd,0,strpos($cmd," "));  //выделяем аргумент
		$cmd=stristr($cmd,' '); //отсекаем аргумент
		$cmd=trim($cmd);
		fputs ($fp, $c." ".$arg." ".$_POST['key']." ".$cmd);
	}else
		fputs ($fp, $_POST['key']." ".$cmd);
	
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
echo "<br><a href=\"index.php\">[ok]</a>";
?>