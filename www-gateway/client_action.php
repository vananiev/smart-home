<?php
	set_time_limit(0);  //������ ����������� ����������
    	ob_implicit_flush();   //������� echo  �� ���� ����������� ������, � �� � ����� ������ �������

	@$fp = fsockopen ($_POST['ip'], $_POST['port'], $errno, $errstr, 30);

if (!$fp) {
	echo "������ � �������� ����������: �� ������� ������������ � �������.<br><br>";
	echo "�������� ������:<br>";
	echo "$errstr ($errno)<br>";
	} 
else{
	echo "�������� �������:  ".$_POST['cmd']."<br>";
	$cmd = trim($_POST['cmd']);
	if(substr($cmd,0,2) == '��' || substr($cmd,0,2) == 'to'){	//���� �������� ������� �� ��
		$c = substr($cmd,0,2); //�������� ��� ��������
		$cmd=substr($cmd,3); //�������� ��� �������
		$cmd=trim($cmd);
		$arg=substr($cmd,0,strpos($cmd," "));  //�������� ��������
		$cmd=stristr($cmd,' '); //�������� ��������
		$cmd=trim($cmd);
		fputs ($fp, $c." ".$arg." ".$_POST['key']." ".$cmd);
	}else
		fputs ($fp, $_POST['key']." ".$cmd);
	
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
echo "<br><a href=\"index.php\">[ok]</a>";
?>