#ifndef _HEAD
#ifdef _MAIN            //������ ����������� ��� ��������� � ��������� �������
//---------------------------------------------------------------------------
char* SITE = "cmd.paradoxos.ru";           //����� �����
char* ADR1 = "cmd.paradoxos.ru/getip.php";         //����� �������� ������ ip
char* ADR2 = "cmd.paradoxos.ru/getip_login.php";  //����� �������� ������ ip � ������������
char Compilers[17][4] = {"c++\0","","","","","","","","","","","","","","","","\0"}; //������ �������������� ������������, ��������� ������ ����������� ������
char Compiler_dir[17][256]={"\"\\command\\bcc32.exe\"","","","","","","","","","","","","","","","","\0"};
char Include[17][256] = {"\"C:\\Program Files\\Borland\\CBuilder6\\Include\";\"C:\\Program Files\\Borland\\CBuilder6\\Include\\vcl\"","","","","","","","","","","","","","","","","\0"};     //��� ����������� �++  Include ����������
char Lib[17][256] = {"\"C:\\Program Files\\Borland\\CBuilder6\\lib\";\"C:\\Program Files\\Borland\\CBuilder6\\lib\\obj\";\"C:\\Program Files\\Borland\\CBuilder6\\lib\\release\";\"C:\\Program Files\\Borland\\CBuilder6\\lib\\PSDK\"","","","","","","","","","","","","","","","","\0"};     //��� ����������� �++  Lib ����������
#else
extern char* SITE;     //����� �����
extern char* ADR1;         //����� �������� ������ ip
extern char* ADR2;  //����� �������� ������ ip � ������������
extern char Compilers[17][4]; //������ �������������� ������������, ��������� ������ ����������� ������
extern char Compiler_dir[17][256];       //���� � ������������
extern char Include[17][256];     //��� ����������� �++  Include ����������
extern char Lib[17][256];     //��� ����������� �++  Lib ����������
#endif
//#define SITE
//#define ADR1
//#define ADR2
#define _WORD 1024			//����� ����������������
#define _A 32				//max ������ �����-����������������
#define _B 2048				//������ ������
#define _C 8				//������ ������� ������
//---------------------------------------------------------------------------
#endif
#define _HEAD
