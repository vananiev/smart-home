<form action="getip_login_act.php<?php echo "?port=".$_GET['port']."&name=".$_GET['name']; ?>" method="post">
    <table>
        <tr>
            <td>Логин:</td>
            <td><input type="text" name="login" value="<?php if(isset($_GET['login'])) echo $_GET['login']; ?>" ></td>
        </tr>
        <tr>
            <td>Пароль:</td>
            <td><input type="password" name="password" /></td>
        </tr>
        <tr>
            <td></td>
            <td><input type="submit" value="Войти" /></td>
        </tr>
    </table>
</form>