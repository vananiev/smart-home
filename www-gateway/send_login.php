<p>��������� �������:</p>
<?php
@session_start();

if(isset($_SESSION['user_id']))
	echo "
		<form action=\"index.php?adr=send_login_act.php\" method=\"post\">
		<p><span lang=\"ru\">������ ������� : 
		</span><input type=\"text\" name=\"cmd\" size=\"64\"> </p>
		<p><span lang=\"ru\">������ ����: 
		</span><input type=\"password\" name=\"key\" size=\"20\"> </p>
		<p><input name=\"Submit\" type=submit value=\"   ���������  \"> </p>    
	</form>";
else
	echo "
		<form action=\"index.php?adr=index_login_act.php\" method=\"post\">
		<p><span lang=\"ru\">������� ����� : 
		</span><input type=\"text\" name=\"login\" size=\"20\" ></p>
		<p><span lang=\"ru\">������ ������ : 
		</span><input type=\"password\" name=\"password\" size=\"20\"> </p>
		<p><span lang=\"ru\">������ ������� : 
		</span><input type=\"text\" name=\"cmd\" size=\"64\"> </p>
		<p><span lang=\"ru\">������ ����: 
		</span><input type=\"password\" name=\"key\" size=\"20\"> </p>
		<p><input name=\"Submit\" type=submit value=\"   ���������  \"> </p>    
	</form>";
?>


<?php include "sape_block.php"; ?>