<?php
session_start();	

include "DB.php";

//просмотр
$sql=mysql_query("SELECT login FROM user WHERE id='{$_SESSION['user_id']}'",$msconnect);
$row = mysql_fetch_assoc($sql);
echo $_SESSION['user_id'].". ".$row['login']." (".mysql_num_rows($sql).")<br>";
if ($row['login']=='admin' && mysql_num_rows($sql) == 1)
	{
	$res=mysql_query("SELECT * FROM user",$msconnect);
	while($row=mysql_fetch_array($res))
		{
		$id=$row['id'];
		$login=$row['login'];
		$password=$row['password'];
		$ip=$row['ip'];
		$port=$row['port'];
		$local_ip =$row['local_ip'];

		echo $id.".  ".$login." :  ".$password."  ip = ".$ip."  port =  ".$port."  local name =  ".$local_ip."<br>";
		}
	}
else
	echo "У вас нет доступа.";
	
	//закрываем БД
	mysql_close($msconnect);
?>



<!-- Информер ТИЦ и PR -->
<a href="http://seo-monster.ru/" target="_blank"><img src="http://seo-monster.ru/img_cmd.my-data.ru_3_255,209,186.gif" border="0" width="88" height="15" alt="тИЦ и PR сайта " /></a><!-- / seo-monster.ru -->