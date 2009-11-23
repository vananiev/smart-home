<p>Отправить команду по IP:</p>
			<form action="index.php?adr=client_action.php" name="send_qwes" method="post"> 
 				<p><span lang="ru">Введите адрес / ip : 
				</span><input type="text" name="ip" size="20"></p>
				<p><span lang="ru">Ведите номер порта : 
				</span><input type="text" name="port" size="20"> </p>
				<p><span lang="ru">Ведите команду : 
				</span><input type="text" name="cmd" size="64"> </p>
				<p><span lang=\"ru\">Ведите ключ: 
				</span><input type="password" name="key" size="20"> </p>
				<p><input name="Submit" type=submit value="   Выполнить  "> </p>
			</form>
			


<?php include "sape_block.php"; ?>