<?php
	set_time_limit(0);  //������ ����������� ����������
    	ob_implicit_flush();   //������� echo  �� ���� ����������� ������, � �� � ����� ������ �������

	@$fp = fsockopen ($_GET['ip'], $_GET['port'], $errno, $errstr, 1);

if (!$fp) {
	echo "������ � �������� ����������: �� ������� ������������ � �������.<br><br>";
	echo "�������� ������:<br>";
	echo "$errstr ($errno)<br>";
	} 
else{
	echo "�������� �������:  ".$_GET['cmd']."<br>";
	fputs ($fp, $_GET['cmd']);
	
	//������ �������
	do{
		$d="";
		$ans="";
		do{
			$ans=$ans.$d;
			$d = fgets ($fp,2);
		}while($d != '#');		//���������� �����
		echo "�����:  ".$ans."<br>";
	}while($ans != 'exit');
	
	fclose ($fp);
	
	echo "�������� ���� ������� ���������.";
	}
?>