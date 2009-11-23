<?php 
session_start();
include_once('function.php');

$res = run('an-vitek@yandex.ru'); // <-- Ваш адрес e-mail здесь

if ($res === true) {
	$err = '';
	$msg = 'Ваше обращение принято. В ближайшее время с Вами свяжется специалист поддержки.'; // <-- Ответ сервиса при положительном результате
} else {
	$err = $res;
}

$base='/';

header("Content-Type: text/html; charset=utf-8");

 /* Next code is XHTML 1.0 Transitional complied. Do not brake it! */
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="ru">
	<head>
	    <title>Служба поддержки абонентов</title>
	    <link rel="stylesheet" href="<?php echo $base?>css/style.css" type="text/css"/>
	    <meta http-equiv="content-type" content="text/html; charset=utf-8"/>
	</head>
	<body>
		
		<div id="wrapper">
			<a href="<?php echo $base?>">
		  <!--<img src="<?php echo $base?>images/header_logo.png" alt="Site logo" style="border: 0"/>-->
		  </a>
			<br/>
			<br/>
			<!--[if lte IE 6]><div id="ie6fix"><![endif]-->
			<div id="wrapper_top">&nbsp;</div>
			<div id="wrapper_content">
				<h3 style="margin-top: 0">СЛУЖБА ПОДДЕРЖКИ АБОНЕНТОВ</h3>
				<p>
					<b style="color:#F00">Обращаем Ваше внимание, что срок разбора заявки напрямую зависит от полноты и точности указанной Вами информации.</b>
				</p>
 				<div id="white_form">
					<div id="white_form_content">

					<? if ($res === true):?>
						<span><b><?=$msg?></b></span>
					<? else:?>
						<? if ($err <> ''):?>
						<span style='color:red'><?=$err?></span>
					  <? endif ?>
						
						<form id="form" action="." method="post" enctype="multipart/form-data" onsubmit="this.submit.disabled=true;this.submit.value='отправлено';return true">
						<p style="margin-bottom: 0">
								<label for="fio">ФИО:</label><br/>
								<input type="text" class="text" name="fio" value="<?=htmlspecialchars(stripslashes($_POST['fio']))?>"/><br/>
								
								<label for="phone">Номер телефона с которого было отправлено SMS в формате 7 XXX XXXXXXX:</label><br/>
								<input type="text" class="text" name="phone" value="<?=htmlspecialchars(stripslashes($_POST['phone']))?>"/><br/>
								
								<label for="email">Адрес E-mail для ответа на Вашу заявку:</label><br/>
								<input type="text" class="text" name="email" value="<?=htmlspecialchars(stripslashes($_POST['email']))?>"/><br/>
								
								<label for="web_site">Адрес сайта услугами которого Вы хотели воспользоваться:</label><br/>
								<input type="text" class="text" name="web_site" value="<?=htmlspecialchars(stripslashes($_POST['web_site']))?>"/><br/>
								
								<label for="subject">Тема сообщения:</label><br/>
								<input type="text" class="text" name="subject" value="<?=htmlspecialchars(stripslashes($_POST['subject']))?>"/><br/>
								
								<label for="message">Суть проблемы:</label><br/>
								<textarea name="message" rows="3" cols="60" ><?=htmlspecialchars(stripslashes($_POST['message']))?></textarea><br/>
								
								<label for="subject">При необходимости, приложите снимок экрана</label><br/>
								<input type="file" class="file" name="scr" style="width: 500px"/><br/>
								
								<label>Последовательность символов:</label><br/>
								<img src="./index.php?get_pic=1" alt="Перезагрузите страницу, если вы не видите эту картинку"/><br/>
								
								<label>Введите символы, указанные на картинке</label><br/>
								<input type="text" class="text" name="code" value="" maxlength="6" onkeyup="this.value=this.value.toUpperCase();"/><br/>
								<br/>
								<input type="submit" class="submit" style="margin-left: 180px; width: 100px" name="submit" value="ОТПРАВИТЬ"/>
						</p>
						</form>
						
						<? endif; ?>
					</div>
				</div>
			
			</div>
			<div id="wrapper_bottom">&nbsp;</div>
			<!--[if lte IE 6]></div><![endif]-->
			<div id="footer" style="padding: 10px 0 0 20px;">
			    <a href="http://www.a1agregator.ru/main/abonent" target="_blank">Стоимости коротких номеров</a>
			</div>
		</div>
	</body>
</html>
