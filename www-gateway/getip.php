<?php
	@set_time_limit(0);  //������ ����������� ����������
    	ob_implicit_flush();   //������� echo  �� ���� ����������� ������, � �� � ����� ������ �������

	$ip=$_SERVER['REMOTE_ADDR'];  //���������� ip �������������
	echo "��� ip: ".$ip."<br>";

	if(!isset($_GET['port']))  //���� ���� �� ������
		$port=12001;
	else
		$port=trim($_GET['port']);
	if(!isset($_GET['name']))  //���� ���� �� ������
		$name=NULL;
	else
		$name=trim($_GET['name']);

	//�����������
	@$fp = fsockopen ($ip, $port, $errno, $errstr, 30);

if (!$fp) {
	echo "������ � �������� ����������: �� ������� ������������ � �������.<br><br>";
	echo "�������� ������:<br>";
	echo "$errstr ($errno).<br>";
	} 
else{
	//���� ip ������ � "��������� �������", �� ��������� �������
	if($ip == trim($name))
		$name = NULL;
	
	echo "�������� ��� ip ���������.<br><br>";
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
	echo "�������� ���� ������� ���������.";
	}
?>
