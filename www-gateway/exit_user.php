<?php
	@session_start();	
	unset($_SESSION['user_id']);
	session_unregister('user_id') or die("������ ����������� ��� ���.");
	echo "����� ������� ��������.";
	echo "<a href=\"index.php\">[ok]</a>";
?> 	