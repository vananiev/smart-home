<head>
	<meta name='yandex-verification' content='4edc809b1b1fe511' />
	<meta http-equiv="Content-Language" content="ru">
	<meta http-equiv="Content-Type" content="text/html; charset=windows-1251">
	<title>��������� ������ �� ����. ��������� ������ �� ���. ���������!</title>
	<link rel="stylesheet" type="text/css" href="css/style2.css" />
</head>

<body text="#008000" link="#11A0F0" vlink="#33CC33" alink="#00FFFF">
<!-- sape-->
<?php 
	global $sape;
     if (!defined('_SAPE_USER')){
        define('_SAPE_USER', '52a486f491a19ccbaee81f67a8aa307c'); 
     }
     require_once($_SERVER['DOCUMENT_ROOT'].'/'._SAPE_USER.'/sape.php'); 
     $sape = new SAPE_client();
?>
<!-- sape-->

<div class="container">

<div class="titleblock2">
<div class="titleblock" style="width: 1261px; height: 142px">
	<br />
	<h1>��������� ������</h1><p>�������� � ��������</p>
</div>
</div>

<div><ul class="navbar">
		 <li><a class="nav" title="�������" href="index.php?adr=how.htm">�������</a></li>
		 <li>
			<a class="nav" title="����� ������� ����� ������������" href="index.php?adr=command.htm">������ ������</a></li>
		 <li>
			<a class="nav" title="��������� ������" href="index.php?adr=send_select.htm">�������� �������</a></li>
		 <li>
			<a class="nav" title="��������� ��� ������" href="index.php?adr=FAQ.htm#��������� ������� ����� ���.">��� �������</a></li>
		 <li>
			<a class="nav" title="������ ���� IP-�����" href="index.php?adr=ip.php">����� ���� IP</a></li>
		 <li>
			<a class="nav" title="������ ������� � ������" href="index.php?adr=FAQ.htm">FAQ</a></li>
		 <li>
			<a class="nav" title="��������� ������ ������ ���������" href="http://support.cmd.my-data.ru">������ ���������</a></li>
</ul></div>
<div class="rightcontainer"><ul class="navbar">
		<li>
		<a class="nav" title="���� /  �����������  /  ������� ����� � ������" href="index.php?adr=in.php"><font color="#F0C030">����</font></a></li>
		<li>
		<a class="nav" title="�����������" href="index.php?adr=reg_user.php"><font color="#F0C030">�����������</font></a></li>
</ul></div>

<div class="rightcontainer" style="height: 686px;width:169px">

	<div class="rightbox">
	  <h2><img src="images/fleche.gif" alt="arrow"/>&nbsp;������� ������ </h2>
	  <p>���� �������� ��������������:</p>
	  <p>
	  	<a href="index.php?adr=how.htm">
	  	<img style="border: 1px solid ; vertical-align: bottom;" src="images/index.1.gif" width="50" height="43" align="senter"></a>
		<p align="center">
		����� ������.</p>
		<p align="center">
		<a href="index.php?adr=how.htm">
		<img style="border: 1px solid ; vertical-align: bottom;" src="images/money.jpg" width="70" height="63"></a></p>
		<p align="center">
		<span style="vertical-align: bottom">���������� 
		���������!</span></p>
	  </p>
	  <p><a title="������������� �����" href="index.php?adr=about.htm">���������</a></p>
	  <h2><img src="images/fleche.gif" alt="arrow" />&nbsp;�������� �����</h2>
  		 <p>
			<font size="1">
			<a title="���� �����������" href="mailto:admin@cmd.my-data.ru?subject=��������� ������ &lt;�����������&gt;">���� ����������� �� ��������� �������� �����</a></font></p>
		<p>
  		 	<font size="1" color="#F0C030">
			<a href="mailto:support@cmd.my-data.ru?subject=��������� ������ &lt;������&gt;">
			���� �������?</a></font><br />
 		</p>
 	  <h2><img src="images/fleche.gif" alt="arrow" />&nbsp;����������</h2>
 	  <p align="left"><i><font size="2" face="Times New Roman" color="#C0C0C0"><span lang="ru">
			&nbsp;&nbsp; �������� &nbsp;&nbsp;   
			<?php
				//����������� �������			
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
	  </font></span>
	  <span lang="ru"><font size="2" face="Times New Roman" color="#C0C0C0"> ���.</font></span><br>
	  <i><font face="Times New Roman" color="#C0C0C0" size="2"><span lang="en-us">&nbsp;&nbsp; </span>
	  <span lang="ru">�������� ���������</font></span>
	  <span lang="ru">
	  <font size="2" color="#C0C0C0">
			<?php
				//�������� ���������
				$file=fopen("speed.txt","a+");
				flock($file,LOCK_EX);
				$last=fread($file,100);
				ftruncate($file,0);
				echo round(1/(time()-$last+0.00001),3);
				fwrite($file,time());
				flock($file,LOCK_UN);
				fclose($file);
			?>
		</font><font size="2" face="Times New Roman" color="#C0C0C0"> &#1089;&#1090;&#1088;/&#1089;&#1077;&#1082;.</font></span></i></p>
			<div class="rightbox">
			<?php
				echo "<p align=\"right\"><font size=\"2\" face=\"Times New Roman\"><i>".date("l")."<br>";
				echo date("dS F Y")."<br>";
				echo date("H:i")."</i></font></p>"
			?>
	</div>
		
	</div>		

</div>

<div class="content">
<br />
	<blockquote>
	<p>&nbsp;</p>
	<p>&nbsp;</p>
		<?php
			if(isset($_GET['adr']))
				include $_GET['adr'];
			else
				include "how.htm";	
		?>
	</blockquote>
	
</div>

<table cellpadding="0" cellspacing="0" width="100%">
	<!-- MSTableType="layout" -->
	<tr>
		<td valign="top" width="20%">
			<p align="center"><a href="http://cmd.my-data.ru/dir-catalogue/"><font size="2">
			������� ������</font></a><font size="2">
			</font> </p>
		</td>
		<td valign="top" width="20%">
			<p align="center">
			<!-- sape-->
				<?php include "sape_2.php"; ?>					
			<!-- sape-->
		</td>
		<td valign="top" width="20%">
			<p align="center">
			<!-- begin of Top100 code -->
			<script id="top100Counter" type="text/javascript" src="http://counter.rambler.ru/top100.jcn?1929213"></script><noscript><img src="http://counter.rambler.ru/top100.cnt?1929213" alt="" width="1" height="1" border="0"/></noscript>
			<!-- end of Top100 code -->
			
			<!-- begin of Top100 logo -->
			<a href="http://top100.rambler.ru/home?id=1929213" target="_blank">
			<img src="http://top100-images.rambler.ru/top100/b0.gif" alt="Rambler's Top100" width="74" height="28" border="0" /></a>
			<!-- end of Top100 logo -->
			</p>
		</td>
		<td valign="top" width="20%">
			<p align="center">
			<!-- sape-->
				<?php include "sape.php"; ?>			
			<!-- sape-->
		</td>
		<td width="20%"></td>
		<td valign="top" width="20%" height="63">
			<p align="center">
				<!--LiveInternet counter--><script type="text/javascript"><!--
				document.write("<a href='http://www.liveinternet.ru/click' "+
				"target=_blank><img src='http://counter.yadro.ru/hit?t21.6;r"+
				escape(document.referrer)+((typeof(screen)=="undefined")?"":
				";s"+screen.width+"*"+screen.height+"*"+(screen.colorDepth?
				screen.colorDepth:screen.pixelDepth))+";u"+escape(document.URL)+
				";"+Math.random()+
				"' alt='' title='LiveInternet: �������� ����� ���������� �� 24"+
				" ����, ����������� �� 24 ���� � �� �������' "+
				"border='0' width='88' height='31'><\/a>")
				//--></script><!--/LiveInternet-->	
		</td>
		</tr>
</table>

<div class="footer">
  <div class="right">
      <p>Copyright 2008, ��������� ������</p>
  </div>
</div>

</div>

</body>
</html>
