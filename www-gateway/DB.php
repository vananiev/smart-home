<?php
$mshost = "localhost"; // ����
$msuser = "---"; 	// ��� ������������
$mspassword = "---"; 	// ������
$msname = "---"; 	// ��� ���� ������

//����������� � ������� ��
$msconnect = mysql_connect($mshost, $msuser, $mspassword) or die(mysql_error());

//���� ��� �� �� ������� ��
mysql_query("CREATE DATABASE IF NOT EXISTS $msname CHARACTER SET utf8",$msconnect) or die(mysql_error());

//����� ��
mysql_select_db($msname,$msconnect) or die(mysql_error());
?>