<html>

<head>
<meta name='yandex-verification' content='4edc809b1b1fe511' />
<meta http-equiv="Content-Language" content="ru">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1251">
<title>Удаленный доступ по СМС</title>
</head>

<body bgcolor="#161616" text="#CCFF99" link="#FF9999" vlink="#FFFF99" alink="#00FFFF">

<table border="0" cellpadding="0" cellspacing="0" width=100% height="551">
	<!-- MSTableType="layout" -->
	<tr>
		<td valign="top" bgcolor="#008000">
		<!-- MSCellType="ContentHead2" -->
		<?php include "in.php" ?></td>
		<td valign="top" height="54" bgcolor="#008000">
		<?php
				echo "<p align=\"right\"><i>".date("l dS of F Y H:i")."</i></p>";
		?>		
		</td>
	</tr>
	<tr>
		<td valign="top" width="1028" rowspan="2">
		<!-- MSCellType="ContentBody" -->
		<br>
		<?php
			if(isset($_GET['adr']))
				include $_GET['adr'];
			else
				include "how.htm";	
		?>
		</td>
		
		<td valign="top" bgcolor="#333333" height="418">
		<!-- MSCellType="NavBody" -->
		&nbsp;<p align="right"><i><span lang="ru">Отправить команду с помощью: 
		</span></i></p>
		<p align="right"><span lang="ru"><a href="index.php?adr=send_login.php">Учетной записи</a></span></p>
		<p align="right"><a href="index.php?adr=send.php">IP<span lang="ru"> и номера порта</span></a></p>
		<p align="right">&nbsp;</p>
		<p align="right"><a href="index.php?adr=command.htm">Поддерживаемые 
		команды</a></p>
		<p align="right"><span lang="ru"><a href="index.php?adr=FAQ.htm">Ответы на вопросы</a></span></p>
		<p align="right"><span lang="ru"><a href="http://support.anvitek.my-data.ru">Техническая поддержка</a></span></p>
		<p>&nbsp;</p>
		<p align="right">&nbsp;</p>
		<p>&nbsp;</td>
	</tr>
	<tr>
		<td valign="top" height="79" bgcolor="#333333" width="213">
		<i><span lang="ru">
		<font size="2" face="Times New Roman" color="#FFFF99">Посещено  
			<?php
				//увеличиваем счетчик			
				$file=fopen("see_page_num.txt","a+");
				flock($file,LOCK_EX);
				$all=fread($file,100);
				ftruncate($file,0);
				$all++;
				echo $all;
				fwrite($file,$all);
				flock($file,LOCK_UN);
				fclose($file);
			?>
			страниц</font></span><font size="2" face="Times New Roman" color="#FFFF99">.</font></i><font color="#FFFF00">
		</font>
			
			<br>
			<i><font face="Times New Roman" color="#FFFF99" size="2"><span lang="ru">&#1057;&#1082;&#1086;&#1088;&#1086;&#1089;&#1090;&#1100; &#1087;&#1077;&#1088;&#1077;&#1093;&#1086;&#1076;&#1086;&#1074;</span></font></i><font color="#FFFF00"><font size="2">
		</font>
			<i><span lang="ru">
		<font size="2" face="Times New Roman" color="#11a0f0">
			<?php
				//скорость посещения
				$file=fopen("speed.txt","a+");
				flock($file,LOCK_EX);
				$last=fread($file,100);
				ftruncate($file,0);
				echo round(1/(time()-$last+0.00001),3);
				fwrite($file,time());
				flock($file,LOCK_UN);
				fclose($file);
?>
			</font><font face="Times New Roman" color="#FFFF99" size="2">&#1089;&#1090;&#1088;/&#1089;&#1077;&#1082;</font></span></i><font size="2">
		</font>		
	</font>		
	</td>
	</tr>
</table>


<!-- begin of Top100 code -->
<script id="top100Counter" type="text/javascript" src="http://counter.rambler.ru/top100.jcn?1929213"></script><noscript><img src="http://counter.rambler.ru/top100.cnt?1929213" alt="" width="1" height="1" border="0"/></noscript>
<!-- end of Top100 code -->

<!-- begin of Top100 logo -->
<a href="http://top100.rambler.ru/home?id=1929213" target="_blank"><img src="http://top100-images.rambler.ru/top100/b0.gif" alt="Rambler's Top100" width="88" height="31" border="0" /></a>
<!-- end of Top100 logo -->


</body>

</html>