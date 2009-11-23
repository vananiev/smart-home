#ifndef _HEAD
#ifdef _MAIN            //разные определения для головного и остальных модулей
//---------------------------------------------------------------------------
char* SITE = "cmd.paradoxos.ru";           //адрес сайта
char* ADR1 = "cmd.paradoxos.ru/getip.php";         //адрес проверки вашего ip
char* ADR2 = "cmd.paradoxos.ru/getip_login.php";  //адрес проверки вашего ip с авторизацией
char Compilers[17][4] = {"c++\0","","","","","","","","","","","","","","","","\0"}; //список соддерживаемых компиляторов, последняя строка обязательно пустая
char Compiler_dir[17][256]={"\"\\command\\bcc32.exe\"","","","","","","","","","","","","","","","","\0"};
char Include[17][256] = {"\"C:\\Program Files\\Borland\\CBuilder6\\Include\";\"C:\\Program Files\\Borland\\CBuilder6\\Include\\vcl\"","","","","","","","","","","","","","","","","\0"};     //для компилятора с++  Include директория
char Lib[17][256] = {"\"C:\\Program Files\\Borland\\CBuilder6\\lib\";\"C:\\Program Files\\Borland\\CBuilder6\\lib\\obj\";\"C:\\Program Files\\Borland\\CBuilder6\\lib\\release\";\"C:\\Program Files\\Borland\\CBuilder6\\lib\\PSDK\"","","","","","","","","","","","","","","","","\0"};     //для компилятора с++  Lib директория
#else
extern char* SITE;     //адрес сайта
extern char* ADR1;         //адрес проверки вашего ip
extern char* ADR2;  //адрес проверки вашего ip с авторизацией
extern char Compilers[17][4]; //список соддерживаемых компиляторов, последняя строка обязательно пустая
extern char Compiler_dir[17][256];       //пути с компиляторам
extern char Include[17][256];     //для компилятора с++  Include директория
extern char Lib[17][256];     //для компилятора с++  Lib директория
#endif
//#define SITE
//#define ADR1
//#define ADR2
#define _WORD 1024			//число макроопределений
#define _A 32				//max длинна слова-макроопределения
#define _B 2048				//длинна команд
#define _C 8				//длинна очереди команд
//---------------------------------------------------------------------------
#endif
#define _HEAD
