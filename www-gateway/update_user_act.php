<?php
session_start();	

include "DB.php";

//�������� ������
if (isset($_POST['login']) && isset($_POST['password']) && isset($_SESSION['user_id']))
	{
	$login = mysql_real_escape_string($_POST['login']);
	$pass=$_POST['password'];
	$password = md5($_POST['password']);
	mysql_query("UPDATE user SET login='{$login}',password='{$password}' WHERE id='{$_SESSION['user_id']}'", $msconnect) or die("������. ���������� ��� ���.<br>".mysql_error());
	echo "���� ������ ��������: <br>";
	echo "�����: ".$login."<br>";
	echo "������: ".$pass."<br>";
	}
else
	echo "�� ������� ����� � ������ ��� �� �� ����� � ������� ��� ����� ������.";
	
	//��������� ��
	mysql_close($msconnect);
echo "<br><a href=\"index.php\">[ok]</a>";
?>