<?php
session_start();

set_time_limit(0);  //������ ����������� ����������
ob_implicit_flush();   //������� echo  �� ���� ����������� ������, � �� � ����� ������ �������

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
	//������������ ������
	if (mysql_num_rows($sql) == 1){
		$row = mysql_fetch_assoc($sql);
        	$ip = $row['ip'];
		$port = $row['port'];
		$local_ip=$row['local_ip'];}
	else
		die('����� ����� � ������� �� ������� � ���� ������.'); 
}
	@$fp = fsockopen ($ip, $port, $errno, $errstr, 30);

	if (!$fp) {
		echo "������ � �������� ����������: �� ������� ������������ � �������.<br><br>";
		echo "�������� ������:<br>";
		echo "$errstr ($errno)<br>";
		} 
	else{
		if(trim($local_ip)!='')
			$cmd="to ".$local_ip." ".$_POST['key']." ".trim($_POST['cmd']);
		else
			$cmd=$_POST['key']." ".trim($_POST['cmd']);

		echo "�������� �������:  ".$_POST['cmd']."<br>";
		fputs ($fp, $cmd);
	
		//������ �������
		while(!feof($fp)){
			$ans = fgets ($fp,1024);
			$ans=trim($ans);
			if($ans == 'exit')
				break;
			echo "�����:  ".$ans."<br>";
			}
		fclose ($fp);
		}
//��������� ��
mysql_close($msconnect);

echo "<br><a href=\"index.php\">[ok]</a>";	
?>