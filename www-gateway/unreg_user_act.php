<?php
@session_start();	

include "DB.php";

//������� ������������
if (isset($_SESSION['user_id']))
	{
	mysql_query("DELETE FROM user WHERE id='{$_SESSION['user_id']}'", $msconnect) or die("������. ���������� ��� ���.<br>".mysql_error());
	echo "���� ������� ������ �������. <br>";
	unset($_SESSION['user_id']);
	session_unregister('user_id');
	}
else
	echo "�������������.";
	
	//��������� ��
	mysql_close($msconnect);
echo "<br><a href=\"index.php\">[ok]</a>";
?>