<?php
@session_start();	

include "DB.php";

//��������� ������������
if (isset($_POST['login']) && isset($_POST['password']))
	{
	$login = mysql_real_escape_string($_POST['login']);
	$pass=$_POST['password'];
	$password = md5($_POST['password']);
	//��� �� ������� ������������ � ����� �������
	$query = "SELECT login
            FROM user
            WHERE login='{$login}'
            LIMIT 1";
    	$sql = mysql_query($query,$msconnect) or die(mysql_error());

    // ���� ����� ������������ �� �������
    	if (mysql_num_rows($sql) > 0)
		echo "���� ����� �����. ������� ������ � ���������� ��� ���.";
	else{
		mysql_query("INSERT INTO user (id,login,password) VALUES(id,'{$login}','{$password}')", $msconnect) or die("������. ���������� ��� ���.<br>".mysql_error());
		echo "�� ����������������: <br>";
		echo "�����: ".$login."<br>";
		echo "������: ".$pass."<br>";}		
	}
else
	echo "������� ����� � ������.";
	
	//��������� ��
	mysql_close($msconnect);
echo "<br><a href=\"index.php?adr=reg_user.php\">[ok]</a>";
?>
