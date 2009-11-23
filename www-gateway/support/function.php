<?php

/* You need php compiled with gd library to use this code. See http://php.net/manual/en/book.image.php */
function getPic() {
  $char = $_SESSION['code'];

	$im = @imagecreatetruecolor (120, 25) or die ("Cannot initialize new GD image stream!");
	$bg = imagecolorallocate ($im, 232, 238, 247);
	imagefill($im,119,24,$bg);
	
	for ($i=0; $i<249; $i++) {
	  $colors[] = imagecolorallocate ($im, rand(0,240), rand(0,240), rand(0,240));;
	}

	//создаём шум на фоне
	for ($i=0; $i<=512; $i++) {
		imagesetpixel($im, rand(2,118), rand(2,23), $colors[rand(0,248)]); //рисуем пиксель
	}
  //imagefilter($im, IMG_FILTER_GAUSSIAN_BLUR);
	//выводим символы кода
	for ($i = 0; $i < strlen($char); $i++) {
		$color = imagecolorallocate ($im, rand(0,200), rand(0,128), rand(0,200)); //задаём цвет
		$x = 5 + $i * 20;
		$y = rand(1, 6);
		imagechar ($im, 5, $x, $y, $char[$i], $color);
	}
	//imagefilter($im, IMG_FILTER_GAUSSIAN_BLUR);

	/*/упрощённый вариант
	$color = imagecolorallocate($img, 0, 0, 0);
	imagestring($im, 3, 5, 3, $char, $color);*/

	//антикеширование
	header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");
	header("Cache-Control: no-store, no-cache, must-revalidate");
	header("Cache-Control: post-check=0, pre-check=0", false);
	header("Pragma: no-cache");

	//создание рисунка в зависимости от доступного формата
	if (function_exists("imagepng")) {
		header("Content-type: image/png");
		imagepng($im);
	} elseif (function_exists("imagegif")) {
		header("Content-type: image/gif");
		imagegif($im);
	} elseif (function_exists("imagejpeg")) {
		header("Content-type: image/jpeg");
		imagejpeg($im);
	} else {
		die("No image support in this PHP server!");
	}
	imagedestroy ($im);
}

function CreatePassword() {
	$n=6;
	$sCode='';
//	$chars = "0123456789abcdefghijklmnopqrstuvwxyz";//
	$chars = "23456789ABCDEFGHIJKMNPRSTUVWXYZ";//
	$nNum=0;
	$nSymb=0;
	for ( $i = 0; $i < $n; $i++ )
	{
		$num = rand( 0, 2);
		if ( $num == 0 )
		{
			$sChar=@$chars{rand ( 0,10 )};
		}
		else
		{
			$sChar=@$chars{rand ( 10, (strlen ( $chars )-1) )};
		}
		$sCode.=$sChar;
	}
	return $sCode;
}

function send_mail($to, $subj, $body, $headers, $file = null) {
  $boundary1 = rand(0,9)."-"
  .rand(10000000000,9999999999)."-"
  .rand(10000000000,9999999999)."=:"
  .rand(10000,99999);
  $boundary2 = rand(0,9)."-".rand(10000000000,9999999999)."-"
  .rand(10000000000,9999999999)."=:"
  .rand(10000,99999);
  
  if ($file) {
    $headers[] = "MIME-Version: 1.0";
    $headers[] = "Content-Type: multipart/mixed; boundary=\"$boundary1\"";
    $mail = <<<MAIL
This is a multi-part message in MIME format.

--$boundary1
Content-Disposition: inline
Content-Type: text/plain; charset=utf-8
Content-Transfer-Encoding: quoted-printable

$body

--$boundary1
Content-Type: $file[type]; name="$file[name]"
Content-Transfer-Encoding: base64
Content-Disposition: attachment; filename="$file[name]"

$file[content]

--$boundary1--
MAIL;
    return mail($to, $subj, $mail, join("\r\n",$headers));
  } else {
    $headers[] = "Content-Type: text/plain; charset=utf-8";
  	return mail($to, $subj, $body, join("\r\n",$headers));
  }
}

if (isset($_REQUEST['get_pic'])) {
	getPic();
	exit;
}

function run($to) {
	if ($_POST) {
	  $code = $_SESSION['code'];
	}
	
	$_SESSION['code'] = CreatePassword();
	
	if (!$_POST)
		return '';
	
	foreach ($_POST as $key => $value) {
		$_POST[$key] = trim($value);
	}

	if ($_POST['code'] == '' || $_POST['fio'] == '' || $_POST['web_site'] == '' || $_POST['phone'] == '' || $_POST['email'] == '' || $_POST['subject'] == '' || $_POST['message'] == '') {
		return 'Все поля обязательны для заполнения';
	}

	if (!preg_match("/^\s*[a-zA-Z0-9_-]+([+.][a-zA-Z0-9_-]+)*@[a-zA-Z0-9]+([-.][a-zA-Z0-9]+)*\.[a-zA-Z]{2,}([-.][a-zA-Z]{2,})*\s*$/", $_POST['email'])) {
		return 'Поле E-mail заполнено неверно';
	}
	
	if (strcmp(mb_strtolower($_POST['code']), mb_strtolower($code))) {
		return 'Код подтверждения не совпадает';
	}
	
	$subject = '_utf8'.strip_tags(stripslashes($_POST['subject']));
	$message = 'ФИО: '.strip_tags(stripslashes($_POST['fio']))."\r\n";
	$message .= 'Номер: '.strip_tags(stripslashes($_POST['phone']))."\r\n";
	$message .= 'Точный адрес сайта услугами которого Вы хотели воспользоваться: '.strip_tags(stripslashes($_POST['web_site']))."\r\n";
	$message .= 'E-mail: '.strip_tags(stripslashes($_POST['email']))."\r\n";
	$message .= "Сообщение: \r\n".stripslashes($_POST['message'])."\r\n";
	$headers[] = 'From: noreply@a1agregator.ru';
	
	if (empty($_FILES['scr']['tmp_name'])) {
	  $file = null;
	} else {
		if ($_FILES['scr']['size']>2097152)
		  return 'Слишком большой файл. Принимаются картинки размером до 2 Мб.';
		$name = $_FILES['scr']['name'];
		if (!preg_match('/\.(jpg|jpeg|bmp|gif|png)$/i',$name))
		  return 'Загружен файл неправильного формата. Ожидается картинка размером до 2 Мб.';
		$file = $_FILES['scr'];
		$file['content'] = chunk_split(base64_encode(file_get_contents($_FILES['scr']['tmp_name'])));
	}

  send_mail($to, stripslashes($_POST['subject']), $message, $headers, $file);
	
	return true;	
}

