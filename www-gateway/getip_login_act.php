<?php

@set_time_limit(0);  //������ ����������� ����������
ob_implicit_flush();   //������� echo  �� ���� ����������� ������, � �� � ����� ������ �������

	
include "DB.php";

//����� ������������
if (isset($_POST['login']) && isset($_POST['password']))
{
	$login = mysql_real_escape_string($_POST['login']);
  	$password = md5($_POST['password']);

    // ������ ������ � ��
    // � ���� ����� � ����� ������� � �������
    $query = "SELECT id
            FROM user
            WHERE login='{$login}' AND password='{$password}'
            LIMIT 1";
    $sql = mysql_query($query,$msconnect) or die(mysql_error());

    // ���� ����� ������������ ������� � �� ����
    if (mysql_num_rows($sql) == 1) {
	//���������
	$ip=$_SERVER['REMOTE_ADDR'];  //���������� ip �������������
	echo "��� ip: ".$ip."<br>";

	if(trim($_GET['port']) == NULL)  //���� ���� �� ������
		$port=12001;
	else
		$port=trim($_GET['port']);
	//�����������
	@$fp = fsockopen ($ip, $port, $errno, $errstr, 30);

	if (!$fp) {
		echo "������ � �������� ����������: �� ������� ������������ � �������.<br><br>";
		echo "�������� ������:<br>";
		echo "$errstr ($errno)<br>";} 
	else{
		//���� ip ������ � "��������� �������", �� ��������� �������
		if($ip == trim($name))
			$name = NULL;
		
		echo "�������� ��� ip ���������.<br><br>";
		$name=$_GET['name'];
		if(trim($name)==NULL)
			fputs ($fp, $ip);
		else
			fputs ($fp, "to ".$name." ".$ip);
	
		//������ �������
		while(!feof($fp)){
			$ans = fgets ($fp,1024);
			$ans=trim($ans);
			echo "�����:  ".$ans."<br>";
			if($ans == 'exit')
				break;
			}
		fclose ($fp);
		
		//������� � ��
		mysql_query("UPDATE user SET ip='{$ip}',local_ip='{$name}',port='{$port}'
            		WHERE login='{$login}' AND password='{$password}'
            		LIMIT 1",$msconnect);
		echo "�������� ���� ������� ���������.";
		}
	}
    	else{ 
        	echo "����� ����� � ������� �� ������� � ���� ������.<br>";
		//��������� ������ ������
		$ip=$_SERVER['REMOTE_ADDR'];  //���������� ip �������������

		if(trim($_Get['port']) == NULL)  //���� ���� �� ������
			$port=12001;
		else
			$port=trim($_Get['port']);
		//�����������
		@$fp = fsockopen ($ip, $port, $errno, $errstr, 30);

		if (!$fp) {
			echo "������ � �������� ����������: �� ������� ������������ � �������.<br><br>";
			echo "�������� ������:<br>";
			echo "$errstr ($errno)<br>";} 
		else{
			if(trim($name)==NULL)
				fputs ($fp, "�������� ������.");
			else
				fputs ($fp, "to ".$name." "."�������� ������.");
	
			//������ �������
			while(!feof($fp)){
				$ans = fgets ($fp,1024);
				$ans=trim($ans);
				echo "�����:  ".$ans."<br>";
				if($ans == 'exit')
					break;}
			}
		fclose ($fp);}
}else
	echo "������� ������.";

//��������� ��
	mysql_close($msconnect);
?>
