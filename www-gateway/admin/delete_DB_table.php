<?php

include "DB.php";

//удаляем тавлицу
mysql_query("DROP TABLE user ",$msconnect) or die(mysql_error()); 

echo "Delete ok";

mysql_close($msconnect);
?>