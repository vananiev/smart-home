<?php
@session_start();

if(isset($_SESSION['user_id'])){
	include "DB.php";
    // ������ ������ � ��
    $query = "SELECT login
            FROM user
            WHERE id='{$_SESSION['user_id']}'";
    $sql = mysql_query($query,$msconnect) or die(mysql_error());
    $row = mysql_fetch_assoc($sql);
    echo "������������, ".$row[login]."!<br>";
    echo "<a href=\"index.php?adr=exit_user.php\">[�����]</a>"."    ";
    echo "<a href=\"index.php?adr=update_user.php\">[�������� ������]</a>"."    ";
    echo "<a href=\"index.php?adr=unreg_user.php\">[�������]</a>"."    ";	
    //��������� ��
    mysql_close($msconnect);}
else{
	echo "
	<form action=\"index.php?adr=login.php\" method=\"post\">
    		<table>
        	<tr>
            		<td>�����:</td>
            		<td><input type=\"text\" name=\"login\" /></td>
        	</tr>
        	<tr>
            		<td>������:</td>
            		<td><input type=\"password\" name=\"password\" /></td>
        	</tr>
        	<tr>
            	<td></td>
            		<td><input type=\"submit\" value=\"�����\" /></td>
        	</tr>
    		</table>
	</form>";
	echo "<a href=\"index.php?adr=reg_user.php\">[������� ������� ������]</a>";}

?>

<?php include "sape_block.php"; ?>