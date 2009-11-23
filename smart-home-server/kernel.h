#include <fstream.h>
#include <dir.h>
String Login;
String Pass;
int ClientsList();
char cmd[128],arg[1024];   //комманда  и аргумент
char word[2][_WORD][_A];         //слова-заменители(макроопределения)  0-7 это системные
int Do();
int Command();
void SendAns();
void split(char *A, char *X, char *Y);
int Run_Exe_File();
void del_kav(char* cmd, char s = '"');      //удаление кавычек
void cat(char* str);            //конкатация строк
void add_kav(char* cmd);
int find_mac(char* mac);        //поиск макроопределений
int save_mac();                 //сохранение макроопределений
int set_dir(char *dir);        //установка текущей папки
void dic();
void func();
bool cmp_local_adr(char *adr);  //сравниваем локальный адрес(локальное имя) компа со строкой  adr
String Ans;             //результат выполнения
char LastData[_B];        //последнее принятое сообщение
String LastClient;         //от кого принято
char cmd_dir[256];                  //папка с коммандами
char exe_path[MAX_PATH];        //папка в которой находится программа
char* DosToAnsi(unsigned char * s);              //перекодировка строки Dos -> Ansi
char* AnsiToDos(unsigned char * s);              //перекодировка строки Ansi -> Dos
bool AutoDosToAnsi = true;                             //автоматическая перекодировка полученных результатов из программ, запушенных нашей
extern void ShowAns(String str = "");                    //функция вывода ответа(должна дописываться в конкретной реализации программы)
TClientSocket* ClientSocket;               //клиентский сокет
TServerSocket* ServerSocket ;             //серверный сокет
extern void UpdateFace();                      //обновляем внешний вид главного окна   (должна дописываться в конкретной реализации программы)
class CClients{
        public:
        String Clients[128];            //клиенты подключенные к ситеме
        unsigned int Index;     //текущий клиент
        String ClientsWhiteList;            //разрешенные клиенты
        bool IpFilterOn;                        //включен ли ip фильтр
        CClients(){Index=-1;Clear();IpFilterOn=true;}
        void Clear(){Clients[0]="";}     //очистка списка подключенных клиентов
        void Add(String Value){                  //добавление клиента в конец
                Clients[Count] = Value;
                Clients[Count+1]="";
                }
        __property int Count  = { read=GetCount };
        int __fastcall GetCount()
                {
                int i;
                for(i=0;Clients[i]!="";i++);
                return i;
                }
        void SetWhiteList(String &Value){       //Установка белых ip
                ClientsWhiteList = Value;
                char s[MAX_PATH];
                strcpy(s,exe_path);
                strcat(s,"\\config\\ip.cnf");
                ofstream out(s);
                out<<ClientsWhiteList.c_str();
                out.close();}
        } Clients;
//----------------------------------------------------------------------------
void del_kav(char* cmd, char s){
        /*int j=0;
        for(int i=0; cmd[i];i++)
                if(cmd[i]!='"')
                        cmd[j++]=cmd[i];
        cmd[j]=0; */
        unsigned int i;
        if(cmd[0]==s && cmd[strlen(cmd)-1]==s){
                for(i=0; i<strlen(cmd)-2;i++)
                        cmd[i]=cmd[i+1];
                cmd[i]=0;}
}
//----------------------------------------------------------------------------
void add_kav(char* cmd){
        /*int j=0;
        for(int i=0; cmd[i];i++)
                if(cmd[i]!='"')
                        cmd[j++]=cmd[i];
        cmd[j]=0; */
        int i;
        char t[1024];
        strcpy(t,cmd);
        cmd[0]='"';
        for(i=1; t[i-1];i++)
                cmd[i]=t[i-1];
        cmd[i]='"';
        cmd[++i]=0;
}
//----------------------------------------------------------------------------
int find_mac(char* mac){
        for(int j=8;j<_WORD;j++)
                if(!strcmp(mac,word[0][j]))
                        return j;
        return -1;
}
//----------------------------------------------------------------------------
int save_mac(){
        set_dir(NULL);
        ofstream out("config\\word.cnf" , ios::trunc);
                if(!out){
                        Ans="Не возможно сохранить в файл config\\word.cnf";
                        return 1;}
        for(int j=8;j<_WORD;j++)
                if(word[0][j][0]!=0){
                        out<<word[0][j]<<endl;
                        out<<word[1][j]<<endl;
                        }
        return 0;
}
//----------------------------------------------------------------------------
int set_dir(char *dir)    //в конце кавычки
{
        char path[256];
        if(dir==NULL) goto _1;
        //указан относительный или абсолютный путь?
        if(dir[1]!=':'){
_1:
                //определение пути к программе
                strcpy(path,(Application->ExeName).c_str());
                int i;
                for(i=strlen(path)-1;path[i]!='\\';i--);
                path[i]='\0';
                if(dir!=NULL)
                        if(dir[0]!='\\'){
                                strcat(path,"\\");
                                strcat(path,dir);}
                                else
                                strcat(path,dir);
                }
                else
                strcpy(path,dir);
        //установка текущей папки
	setdisk(toupper(path[0])-'A');
	if (chdir(path))
                return 1;
        return 0;
}
//----------------------------------------------------------------------------
void func()
{
        int i,k,n,m;
        char fnc[256];
        char LastData_temp[_B];
        int j=strlen(LastData);
        for(i=0;i<j;i++)
                if(LastData[i]=='('){
                        n=i;
                        i++;
                        fnc[0]=0;
                        int scobka=0;
                        for(k=0;i<j && (LastData[i]!=')' || scobka!=0);i++,k++){
                                if(LastData[i]=='(') scobka++;
                                if(LastData[i]==')') scobka--;
                                fnc[k]=LastData[i];}
                        fnc[k]=0;
                        if(i>=j)
                                return;
                                else
                                m=i;
                        //выполнение функции
                        LastData_temp[0]=0;
                        strcpy(LastData_temp,LastData);
                        LastData[0]=0;
                        strcpy(LastData,fnc);
                        Do();
                        //возвращение результата
                        for(i=0;i<n;i++)                    //до функции
                                LastData[i]=LastData_temp[i];
                        int a=strlen(Ans.c_str());              //результат функции
                        for(k=0;k<a;k++,i++)
                                LastData[i]=Ans.c_str()[k];
                        int s=i;
                        for(k=m+1;LastData_temp[k];k++,i++)                    //после функции
                                LastData[i]=LastData_temp[k];
                        LastData[i]=0;
                        //продолжаем поиск функций
                        i=s-1;
                        j=strlen(LastData);
                        }
}
//-----------------------------------------------------------------------------
void cat(char* str)
{
        int sp=-1;
        bool do_cat=false; //выполнили операцию сложения
        //отсекаем все пробелы вокруг +
        for(int i=0;str[i];i++)
                if(str[i] == '+'){
                        char t[_B];
                        int n,m;
                        for(n=i-1;str[n]==' ';n--);
                        for(m=i+1;str[m]==' ';m++);
                        int k=0;
                        for(int j=0;j<=n;j++,k++)
                                t[k]=str[j];
                        //i снова указывает на +
                        i=k;
                        t[k++]='+';
                        for(int j=m;str[j];j++,k++)
                                t[k]=str[j];
                        t[k]=0;
                        str[0]=0;
                        strcpy(str,t);}
        for(int i=0;str[i];i++){
                if(str[i] == ' ') //поиск предыдущего пробела
                        sp=i;
                if(str[i] == '+'){
                        do_cat=true;
                        //выбор случая
                        if(str[i-1] == '"' && str[i+1] == '"')
                                {int j;
                                for(j=i+2;str[j];j++)
                                        str[j-3]=str[j];
                                str[j-3]=0;
                                i=i-1-1;}
                        else if(str[i-1] == '"')
                                {int j;
                                bool kav=false;
                                //поиск конца строки и установка закрывающей кавычки
                                for(j=i+1;str[j];j++){
                                        if(str[j] == ' '){
                                                kav=true;
                                                str[j-2]='"';
                                                // дальнейшее копирование
                                                for(;str[j];j++)
                                                        str[j-1]=str[j];
                                                break;}
                                        str[j-2]=str[j];}
                                if(!kav){
                                        str[j-2]='"';
                                        j++;
                                        str[j-2]=0;}
                                else
                                        str[j-1]=0;
                                i=i-1-1;}
                        else if(str[i+1] == '"')
                                {char s[_B];
                                int k;
                                if(sp == -1){    //нет пробела начало слова в начале строки
                                        s[0]='"';
                                        int j;
                                        //начало
                                        for(j=0,k=1;j<i;j++,k++)
                                                s[k]=str[j];
                                        //конец
                                        for(j=i+2;str[j];j++,k++)
                                                s[k]=str[j];
                                        }
                                else{         //есть пробел
                                        int j;
                                        //начало
                                        for(j=0,k=0;j <= sp;j++,k++)
                                                s[k]=str[j];
                                        s[k]='"';
                                        k++;
                                        //с установленной програмно кавычки в s[]
                                        for(;j<i;j++,k++)
                                                s[k]=str[j];
                                        //конец
                                        for(j=i+2;str[j];j++,k++)
                                                s[k]=str[j];
                                        }
                                s[k]=0;
                                str[0]=0;
                                strcpy(str,s);
                                i=i-1;}
                        else
                                {char s[_B];
                                int k;
                                if(sp == -1){    //нет пробела начало слова в начале строки
                                        s[0]='"';
                                        int j;
                                        bool kav=false;
                                        //начало
                                        for(j=0,k=1;j<i;j++,k++)
                                                s[k]=str[j];
                                        //конец
                                        for(j=i+1;str[j];j++,k++){
                                                if(str[j] == ' '){
                                                        kav=true;
                                                        s[k]='"';
                                                        k++;
                                                        //дальше
                                                        for(;str[j];j++,k++)
                                                                s[k]=str[j];
                                                        break;}
                                                s[k]=str[j];}
                                        if(!kav)
                                                s[k++]='"';
                                        }
                                else{         //есть пробел
                                        int j;
                                        bool kav=false;
                                        //начало
                                        for(j=0,k=0;j <= sp;j++,k++)
                                                s[k]=str[j];
                                        s[k]='"';
                                        k++;
                                        //с установленной програмно кавычки в s[]
                                        for(;j<i;j++,k++)
                                                s[k]=str[j];
                                        //конец
                                        for(j=i+1;str[j];j++,k++){
                                                if(str[j] == ' '){
                                                        kav=true;
                                                        s[k]='"';
                                                        k++;
                                                        //дальше
                                                        for(;str[j];j++,k++)
                                                                s[k]=str[j];
                                                        break;}
                                                s[k]=str[j];}
                                        if(!kav)
                                                s[k++]='"';
                                        }
                                s[k]=0;
                                str[0]=0;
                                strcpy(str,s);
                                i=i-1;}
                        }
                }
        if(do_cat)
                del_kav(str,'\"');
}
//---------------------------------------------------------------------------
char* DosToAnsi(unsigned char * s)
{
        for(int i=0;s[i];i++)
                {if(s[i]>=0x80 && s[i]<=0xAF) //АБВ-ЭЮЯ,абв-мноп
                        s[i]+=0x40;
                else if(s[i]>=0xE0 && s[i]<=0xEF) //рст-эюя
                        s[i]+=0x10;
                else if(s[i] == 0xF0) 			//Ё
                        s[i] = 0xA8;
                else if(s[i] == 0xF1) 			//ё
			s[i] = 0xB8;
		else if(s[i] == 0xFC) 			//№
			s[i] = 0xB9;
                else if(s[i] == 0xFF)                   //пробел
                        s[i] = 0x20;

                }
        return s;
}
//---------------------------------------------------------------------------
char* AnsiToDos(unsigned char * s)
{
        for(int i=0;s[i];i++)
                {if(s[i]>=0xC0 && s[i]<=0xEF) //АБВ-ЭЮЯ,абв-мноп
                        s[i]-=0x40;
                else if(s[i]>=0xF0 && s[i]<=0xFF) //рст-эюя
                        s[i]-=0x10;
                else if(s[i] == 0xA8) 			//Ё
			s[i] = 0xF0;
                else if(s[i] == 0xB8) 			//ё
			s[i] = 0xF1;
		else if(s[i] == 0xB9) 			//№
			s[i] = 0xFC;
                }
        return s;
}
//---------------------------------------------------------------------------
int Do()
{
   //для символов ;
   char com[_B];
   bool bCompile; //для указания обработки участка кода для компиляции
   int skobki;      //число вложений скобок
   char CmdList[256][_B];
   int iCmdList , jCmdList;
   /*/если команда компиляции фигурные скобки {}
   if((LastData[0]=='c' || LastData[0]=='с') && LastData[1]=='+' && LastData[2]=='+')
        {iCmdList = 0;
        strcpy(CmdList[iCmdList],LastData);
        //поиск комманды и аргументов
        split(LastData,cmd,arg);
        Command();
        //получить результат
        if(Ans != "")
                ShowAns(Ans);
        return 0;} */
   strcpy(com,LastData);        //дублируем
   //составляем список команд
   iCmdList=0;
   jCmdList=0;
   skobki = 0;
   bCompile = false;
   int i=0;
   for(;com[i] == ' ' || com[i] == ';'|| com[i] == '\r'|| com[i] == '\n';i++);   //пропуск пробелов и ,
   for(;com[i];i++){
        if(com[i] == '{')
                {bCompile = true;                /*начало участока кода для компиляции
                                                тип компилятора указан сразу после '{' */
                if(skobki == 0){
                        CmdList[iCmdList][jCmdList] = 0; //устанавливаем 0 в конце
                        if(jCmdList) iCmdList++;         //если педыд. строка не пуста
                        jCmdList = 0;
                        }else
                        CmdList[iCmdList][jCmdList++] = com[i];
                skobki++;
                }
                else if(com[i] == '}')
                {skobki --;
                if(skobki==0){
                        CmdList[iCmdList][jCmdList] = 0; //устанавливаем 0 в конце
                        if(jCmdList) iCmdList++;         //если педыд. строка не пуста
                        jCmdList = 0;
                        bCompile = false;                //конец участока кода для компиляции
                        }else
                        CmdList[iCmdList][jCmdList++] = com[i];
                }else if(!bCompile && com[i] == ';')  {  //не учитываем ; для компилируемого кода
                CmdList[iCmdList][jCmdList] = 0; //устанавливаем 0 в конце
                if(jCmdList) iCmdList++;         //если педыд. строка не пуста
                jCmdList = 0;
                for(;com[i] == ' ' || com[i] == ';'|| com[i] == '\r'|| com[i] == '\n';i++);   //пропуск пробелов и ,
                i--;}
                else
                        CmdList[iCmdList][jCmdList++] = com[i];
        }
   CmdList[iCmdList][jCmdList] = 0;
   if(CmdList[iCmdList][0] == 0)  iCmdList--;    //если строка пуста
   //выполнение комманд
   iCmdList++;
   for(int icom=0; icom< iCmdList ;icom++){
        strcpy(LastData,CmdList[icom]);
        //выполнение
        char cmd_1[64];
        char param[_B];
        //определяем компилируемую команду
        bool CmdForCompiler =false;
        char compTemp[4];
        for(int i=0;i<4;i++)
                compTemp[i] = LastData[i];
        compTemp[3]=0;
        for(int i=0;Compilers[i][0];i++)
                if(!strcmp(Compilers[i],compTemp))
                        {CmdForCompiler = true;
                        break;}
        if(CmdForCompiler == false){   //компилируемая строка?
                //избавляемся от символа \n в конце
                if(LastData[strlen(LastData)-1]=='\n')
                        LastData[strlen(LastData)-1]='\0';
                //добавление пробелов с внутренней стороны скобок (для макроопределений)
                char t[_B];
                t[0]=0;
                strcpy(t,LastData);
                int j=0;
                for(int i=0;t[i];i++,j++)
                        if(t[i]=='('){
                                LastData[j]=t[i];
                                j++;
                                LastData[j]= ' ';}
                                else if(t[i]==')'){
                                LastData[j]=' ';
                                j++;
                                LastData[j]= t[i];}
                                else
                                LastData[j]= t[i];
                LastData[j]=0;
                //поиск макроопределений
                dic();
                //соединение строк оператором '+'
                cat(LastData);
                //выполнение функций
                func();
        }//не для компиляторов
        //поиск комманды и аргументов
        split(LastData,cmd,arg);
        if(CmdForCompiler == false){   //компилируемая строка?
                //надо ли переслать по ЛС комманду (программа в режиме клиента)
                //на(to)
                if(!strcmp(cmd,"на") || !strcmp(cmd,"to")){
                        split(arg,cmd_1,param);
                        if(!cmp_local_adr(cmd_1)){
                                if(ClientSocket->Active){    //передаем ли локальному ком. что-нибудь
                                        if(LastClient == "-1")
                                                ShowMessage("Связь с компьютером локальной сети. Попробуйте позднее.");
                                        else{
                                                Ans = "Связь с компьютером локальной сети. Попробуйте позднее.";
                                                SendAns();}
                                        Ans="";
                                        goto _1;;}
                                //к кому коннектимся
                                ClientSocket->Host = cmd_1;
                                //передаваемая комманда
                                strcpy(arg,param);
                                //коннектимся
                                ClientSocket->Active=True;
                                Ans="";
                                Sleep(1000);
                                goto _1;}
                        else                           //к самим себе не коннектимся
                                split(param,cmd,arg);  //в cmd содержится ключ
                                strcpy(param,arg);     //в arg содержится команда
                                split(param,cmd,arg);
                        }
                }
        //команды идут с нашего компа
        if(LastClient=="-1"){
                Command();
                goto _1;}
        else{
                        //Проверка пароля
                if(!strcmp(cmd,Pass.c_str())){
                        strcpy(param,arg); //временно
                        split(param,cmd,arg);
                        //обработка комманд
                        Command();
                        //Отправка ответа
                        SendAns();}
                else{
                        Ans = "Неверный ключ."; //ругаемся
                        //Отправка ответа
                        SendAns();
                        return 0;}
                }
_1:
        //получить результат
        if(Ans != "")
                ShowAns(Ans);
   }
        return 0;
}
//------------------------------------------------------------------------
int Command()
{
        char cmd_1[64];
        char param[1024];
        //запустить (run)
        void *ret;
        if(!strcmp(cmd,"запустить") || !strcmp(cmd,"run")){
                split(arg,cmd_1,param);
                ret=ShellExecuteA(NULL,"Open",cmd_1, param , NULL, 1);
                if((int)ret>32){
                        Ans="Операция выполнена успешно.(С результатом "
                         + IntToStr((int)ret) + " )";
                        return 0;}
                else{
                        Ans="Операция завершилась ошибкой.(Код ошибки: " +
                        IntToStr((int)ret) +")";
                        return 1;}
                }
        //выключить компьютер
        if(!strcmp(cmd,"выключить") || !strcmp(cmd,"shutdown")){
                //Получаем привелегию на выключение компа
                // Get a token for this process.
                void *hToken;
                TOKEN_PRIVILEGES tkp;
                //int tkp;
                OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
                // Get the LUID for the shutdown privilege.
                LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid);
                tkp.PrivilegeCount = 1;  // one privilege to set
                tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
                // Get the shutdown privilege for this process.
                AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
                //Выключаем комп
                if(ExitWindowsEx(EWX_FORCE | EWX_POWEROFF | EWX_SHUTDOWN, NULL))        //EWX_FORCE - принудительно зыкрывает приложения
                        Ans="Ушли на выключение...";
                else
                        Ans="Ошибка";
                return 0;}
        //завершить сеанс
        if(!strcmp(cmd,"выйти") || !strcmp(cmd,"shut")){
                //Получаем привелегию на выключение компа
                // Get a token for this process.
                void *hToken;
                TOKEN_PRIVILEGES tkp;
                OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
                // Get the LUID for the shutdown privilege.
                LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid);
                tkp.PrivilegeCount = 1;  // one privilege to set
                tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
                // Get the shutdown privilege for this process.
                AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
                if(ExitWindowsEx(EWX_LOGOFF | EWX_FORCE, 0)) //EWX_FORCE - принудительно зыкрывает приложения
                        Ans="Выход из системы...";
                else
                        Ans="Ошибка";
                return 0;}
         //перезагрузить
        if(!strcmp(cmd,"перезагрузить") || !strcmp(cmd,"reboot")){
                //Получаем привелегию на выключение компа
                // Get a token for this process.
                void *hToken;
                TOKEN_PRIVILEGES tkp;
                OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
                // Get the LUID for the shutdown privilege.
                LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid);
                tkp.PrivilegeCount = 1;  // one privilege to set
                tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
                // Get the shutdown privilege for this process.
                AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
                //после перезагрузки запускаем программу
                set_dir(NULL);
                ofstream out("temp\\temp.bat");
                if(out){
                        out<<"Windows Registry Editor Version 5.00"<<endl<<endl;
                        out<<"[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce]"<<endl;
                        out<<"\"Server\"=\"";
                        out<<ParamStr(0).c_str() ; //адрес программы
                        out<<"\""<<endl;
                        out.close();
                        ShellExecuteA(NULL,"Open","regedit.exe", "temp\\temp.bat \hide" , NULL, 1);
                        }
                //перезагружаем
                if(ExitWindowsEx(EWX_REBOOT | EWX_FORCE , 0)) //EWX_FORCE - принудительно зыкрывает приложения
                        Ans="Перезагрузка...";
                else
                        Ans="Ошибка";
                return 0;}
        //вызов командной строки с параметром
        if(!strcmp(cmd,"кмд") || !strcmp(cmd,"cmd")){
                set_dir(NULL);
                ofstream out("temp\\temp.bat");
                if(!out)
                        Ans="Ошибка.Сбой при выполнении.";
                else{
                        out<<arg<<endl;
                        out<<"pause";
                        out.close();
                        ret=ShellExecuteA(NULL,"Open","temp\\temp.bat", NULL , NULL, 1);
                        if((int)ret>32){
                                Ans="Командная строка запущена c параметром: "
                                + (String)arg ;
                        return 0;}
                        else{
                                Ans="Ошибка. Командная строка не запущена.";
                        return 1;}
                        }
                
                }
        //выключение программы
        if(!strcmp(cmd,"остановить") || !strcmp(cmd,"stop"))
                exit(0);
        //установка порта
        if(!strcmp(cmd,"порт") || !strcmp(cmd,"port")){
                if(ClientSocket->Active){    //передаем ли локальному ком. что-нибудь
                        Ans="Связь с компьютером локальной сети. Порты не установлены. Попробуйте позднее.";
                }else{
                        ServerSocket->Active=False;
                        Ans="All connections is closed.";
                        int t;
                        if (TryStrToInt(arg,t))
                                {
                                ServerSocket->Port=StrToInt(arg);
                                ClientSocket->Port=ServerSocket->Port;
                                }
                        else
                                {
                                Ans+="\r\nНомер порта должен быть числом.";
                                }
                        Ans+="\r\nListening port="+IntToStr(ServerSocket->Port);
                        //frmServer->cmbClients->ItemIndex=-1;
                        ServerSocket->Active=True;}
                UpdateFace();   //обновляем внешний вид главного окна
                return 0;
                }
        //показать сообщение
        if(!strcmp(cmd,"сообщение") || !strcmp(cmd,"msg")){
                Beep();
                frmMsg->lblMsg->Caption = arg;
                if(LastClient != "-1")
                        frmMsg->Caption="Сообщение от " + LastClient;
                        else
                        frmMsg->Caption="Сообщение";
                frmMsg->Show();
                Ans = "Сообщение доставлено";
                return 0;
                }
        //макроопределения
        if(!strcmp(cmd,"мкр") || !strcmp(cmd,"define")){
                split(arg,cmd_1,param);
                //удаления символов макроопределения
                del_kav(cmd_1,'|');
                del_kav(param,'|');
                //удаляем кавычки
                int i;
                for(i=0;cmd_1[i]!=' ' && cmd_1[i];i++); //поиск пробела
                if(cmd_1[i]!=' ')
                        del_kav(cmd_1);
                for(i=0;param[i]!=' ' && param[i];i++); //поиск пробела
                if(param[i]!=' ')
                        del_kav(param);
                //удаление
                if(!strcmp(cmd_1,"del")){
                        int i=find_mac(param);//поиск
                        if(i==-1){
                                Ans = "Макроопределение не существует";
                                return 0;}
                        word[0][i][0]=0;
                        word[1][i][0]=0;
                        if(save_mac()== 0)
                                Ans = "Макроопределение удалено";
                                else
                                Ans = "Не удалось удалить макроопределение";
                        return 0;
                        }
                int mc = find_mac(cmd_1);
                if(mc == -1){
                        //добавление
                        for(int j=8;j<_WORD;j++)
                                if(word[0][j][0]==0){
                                        strcpy(word[0][j],cmd_1);
                                        strcpy(word[1][j],param);
                                        break;
                                }
                        if(save_mac()== 0)
                                Ans = "Макроопределение добавлено";
                                else
                                Ans = "Не удалось добавить макроопределение";
                        return 0;
                        }else{
                        //замена
                        if(MessageDlg("Заменить макроопределение ?",
                                mtInformation,mbOKCancel,NULL) == 1){
                                        strcpy(word[0][mc],cmd_1);
                                        strcpy(word[1][mc],param);
                                        if(save_mac()== 0)
                                                Ans = "Макроопределение заменено";
                                        else
                                                Ans = "Не удалось заменить макроопределение ";
                                }
                                else{
                                        Ans = "";
                                }
                        return 0;
                        }
                }
        //компиляция + выполнение
        for(int c=0;Compilers[c][0];c++)
          if(!strcmp(cmd,Compilers[c])){
                //получаем директорию компилятора
                        int i , loop;    //указывает на символ за последним слешем
                        char p[512];            //путь к компилятору
                        char n[64];             //имя файла компилятора без рсширения
                        strcpy(p,Compiler_dir[c]+1);
                        for(i=strlen(p);i>=0;i--){
                                if(p[i] == '\\')
                                        break;
                                }
                        i++;
                        for(loop=i;p[loop] && p[loop]!='.';loop++)
                                n[loop-i]=p[loop];
                        p[i]=0;
                        n[loop-i]=0;
                        char com_dir[256];
                        //получаем директорию программы
                                //i=0;    //указывает на символ за последним слешем
                                char *t = (Application->ExeName).c_str();
                                for(i=strlen(t);i>=0;i--)
                                        if(t[i] == '\\')
                                                break;
                                strcpy(com_dir,(Application->ExeName.SubString(0,i)+"\\temp\\").c_str());
                        if(p[1]!=':'){
                                if(p[0]!='\\')
                                        strcpy(p,(Application->ExeName.SubString(0,i)+"\\" + p).c_str());
                                        else
                                        strcpy(p,(Application->ExeName.SubString(0,i)+p).c_str());
                                }
                //устанавливаем папку
                        set_dir("\\temp\\");
                //конфигурируем параметры компиляции
                char conf[64];
                strcpy(conf,n);
                strcat(conf,".cfg");
                ofstream out( conf, ios::trunc);
                if(!out){
                        Ans="Не возможно сконфигурировать файл компиляции";
                        return 1;}
                out<<"-I"<<Include[c]<<endl;
                out<<"-L"<<Lib[c]<<endl;
                out<<"-n"<<"\""<<com_dir<<"\"";
                out.close();
                //создаем файл .срр
                ofstream out2("current.cpp" , ios::trunc);
                if(!out2){
                        Ans="Не возможно создать файл с исходным кодом";
                        return 1;}
                out2<<arg;
                out2.close();
                //компилируем
                char tmp[_B];
                char tmp2[_B];
                //String tmp3 = Ans;
                strcpy(tmp,cmd);
                strcpy(tmp2,arg);
                strcpy(cmd,"popen");
                strcpy(arg,((String)"\"" + p + n + ".exe " + com_dir + "current.cpp\"").c_str());
                if( Run_Exe_File() != 0){
                        Ans = "Компилятор не найден";
                        strcpy(cmd,tmp);
                        strcpy(arg,tmp2);}
                strcpy(cmd,tmp);
                strcpy(arg,tmp2);
                //запускаем
                remove((Application->ExeName.SubString(0,i)+"\\command\\current.exe").c_str());
                MoveFile("current.exe",(Application->ExeName.SubString(0,i)+"\\command\\current.exe").c_str());
                //установка текущей папки
                set_dir(cmd_dir);
                Ans = Ans + "\r\nРезультат запуска программы:";
                String tmp3 = Ans;
                strcpy(tmp,cmd);
                strcpy(tmp2,arg);
                strcpy(cmd,"popen");
                strcpy(arg,"\"current.exe\"");
                Run_Exe_File();
                strcpy(cmd,tmp);
                strcpy(arg,tmp2);
                Ans = tmp3 +"\r\n" + Ans;
                return 0;
        }
        //выполнение команд из файла
        if(!strcmp(cmd,"file")||!strcmp(cmd,"файл")){
                del_kav(arg,'\"');
                set_dir("\\command\\");
                ifstream in(arg,ios::binary);
                if(!in){
                        Ans = "Не удалось открыть файл";
                        return 1;}
                LastData[0]=0;
                char data;
                int i=0;
                while(!in.eof()){
                        in.get(data);
                        LastData[i++] = data;}
                LastData[--i]=0;
                String t_Ans =((String)"Загрузка файла:\r\n") + LastData +"\r\nВыполнение файла:";
                Do();
                Ans = t_Ans + "\r\nФайл загружен и выполнен";
                return 0;
        }
        //отключение сетевых функций
        if(!strcmp(cmd,"disconnect")||!strcmp(cmd,"отклсеть")){
                ServerSocket->Active=False;
                ClientSocket->Active=False;
                Ans = "Listening off.";
                return 0;
                }
        //поиск исполняемого файла
        Run_Exe_File();
        return 0;
}
//-----------------------------------------------------------------------------
void split(char *A, char *X, char *Y)
{
        int i,j;
        bool Text=False; /*необходимо копировать все символы без прерывания,
                        даже пробельные, если указаны кавычки*/
        //bool S=False; //признак найденного пробела или переноса строки внутри кавычек
        //команда
        int k=strlen(A);
        //отсекаем несколько пробелов
        for(i=0;A[i]==' ' || A[i]=='\r' || A[i]=='\n';i++);
        for(j=0;A[i] && ((A[i]!=' '&& A[i]!='\r' && A[i]!='\n') || Text);i++){
                if(A[i]=='"')
                        Text=!Text;
                //if(Text && (A[i]==' '|| A[i]=='\r' || A[i]=='\n'))
                //        S=True;
                X[j++]=A[i];
                }
        X[j]=0;
        //if(S==False && X[0]=='"' && X[strlen(X)-1]=='"')
        //        del_kav(X);        //удаляем кавычки в которые заключено одно слово
        if(i>=k-1){
                Y[0]=0;
                return;}
        //отсекаем несколько пробелов
        for(i=i+1;A[i]==' '|| A[i]=='\r' || A[i]=='\n';i++);
        //аргументы (параметры)
        //S=False;
        for(j=0;A[i];i++){
                //if(A[i]==' '|| A[i]=='\r' || A[i]=='\n')
                //        S=True;
                Y[j++]=A[i];}
        Y[j]=0;
        //удаляем кавычки в которые заключено одно слово
        //if(S==False && Y[0]=='"' && Y[strlen(Y)-1]=='"')
        //           del_kav(Y);
}
//---------------------------------------------------------------------------
int Run_Exe_File()
{
        struct ffblk file;
        char path[256];
        char cmd_win[128];
        bool with_dir = true;
        int rt;
        if(strlen(cmd)==0) {Ans = "Укажите запускаемую команду";return 3;}
        strcpy(cmd_win,cmd);
        //избавляемся от кавычек если они есть
        del_kav(cmd);
       //запоминание текущей папки
       	char lastdir[256];
       	GetCurrentDirectory(MAX_PATH,lastdir);   //запоминаем текущую директорию
        //установка текущей папки
        set_dir(cmd_dir);
        //папка с коммандами
        strcpy(path,cmd_dir);
	//seach file
        if(!findfirst(strcat(cmd,".*"),&file,0)){
        //make full adr
        strcat(path,file.ff_name);
        //установка запомненных директорий
        SetCurrentDirectory(lastdir);
        //запускаем
_1:
        if(arg[0]!=0)
                strcat(strcat(path," "),arg);
        //ставим кавычки
        add_kav(path);
        int r = system(path);
        //результат
        if(r==-1){
                set_dir(cmd_dir);
                ifstream in("result");
                SetCurrentDirectory(lastdir);
                if(!in){
                        Ans = "Не возможно получить результат из файла";
                        return 4;}
                char result[1024];
                Ans = "";
                while(in){ //возврат строки
                        in.getline(result,1024);
                        if(result[0]){
                                Ans  = Ans + result + "\r\n";
                                result[0]=0;}
                        }
                Ans = Ans.SubString(0,Ans.Length() - 2); // убираем перенос строки в конце
                in.close();
                remove("result");
                //автоматически определяем кодировку
                const unsigned char *str = Ans.c_str();
                int cnt=0;
                for(int i=0; str[i]; i++)
                        if(str[i]>=0x80 && str[i]<=0xAF) //этот интервал для русских символов
                                cnt++;
                if(AutoDosToAnsi && Ans.Length()!=0)
                        if((float)cnt/Ans.Length() > 0.01)  //использует только Dos
                                DosToAnsi(Ans.c_str());    //кол-во таких символов более 10%,то конвертируем
                rt =0;
                goto _2;
        }else if(r==0){    // возврат кода
                Ans="Операция выполнена успешно. ( С результатом "
                         + IntToStr(r) + " ).";
                        rt=0;
                        goto _2;}
        else if(with_dir){   //ошибка вызова с указанием полного пути, вызов по имени
                with_dir =false;
                path[0]=0;
                strcpy(path,file.ff_name);
                goto _1;}
      }
      //запускаем
        void *ret;
        ret=ShellExecuteA(NULL,"Open",cmd_win, arg , NULL, 1);
        //результат
        if((int)ret==2){
                Ans="Неверная комманда.";
                rt = 2;
                goto _2;}
        if((int)ret>32){
                Ans="Операция выполнена успешно. ( С результатом "
                         + IntToStr((int)ret) + " ).";
                        rt = 0;
                        goto _2;}
                else{
                Ans="Операция завершилась ошибкой. ( Код ошибки: " +
                        IntToStr((int)ret) +" ).";
                        rt = 3;
                        goto _2;}
_2:
        //установка запомненных директорий
        SetCurrentDirectory(lastdir);
        //возврат
        return rt;
}
//---------------------------------------------------------------------------
void dic()
{
          char x[_B];
          char y[_B];
          char c[_B];

          strcpy(y,LastData);
          LastData[0]='\0';
          do{
                c[0]=0;
                strcpy(c,y);
                split(c,x,y);
                for(int j=0;j<_WORD;j++)
                        if(!strcmp(x,word[0][j])){
                                x[0]='\0';
                                strcpy(x,word[1][j]);
                                break;}
                strcat(LastData,x);
                int i=strlen(LastData);
                LastData[i]=' ';
                LastData[i+1]=0;

          }while(y[0]!='\0');
          LastData[strlen(LastData)-1]='\0';
          /*
          int i,j,k;
          for(i=0;LastData[i];i++)
                for(j=0;j<_WORD;j++)
                        if(LastData[i] == word[0][j][0]){
                                for(k=1;word[0][j][k] && LastData[i+k] && word[0][j][k] == LastData[i+k]; k++);
                                if(k<_A && word[0][j][k] == '\0' &&
                                        (LastData[i+k]==' ' ||
                                        LastData[i+k]=='\0' ||
                                        LastData[i+k]=='\n')){
                                        //найдено макроопределение
                                        int f,g,c,d;
                                        //начальная часть
                                        for(f=0;f<i;f++)
                                                temp[f]=LastData[f];
                                        //добавляем макроопределение
                                        g=strlen(word[1][j]);
                                        for(f=i,c=0;f<i+g;f++,c++)
                                                temp[f]=word[1][j][c];
                                        //конечная часть
                                        for(f=i+g,d=i+k;LastData[d];f++,d++)
                                                temp[f]=LastData[d];
                                        temp[f]='\0';
                                        strcpy(LastData,temp);
                                        //проверяем остальные символы в LastData
                                        //начиная после замененного макроопределения
                                        i=i+g;
                                        }                                        
                                } */

}
//---------------------------------------------------------------------------
bool cmp_local_adr(char *adr)
{
        //адрес компьютера в локальной сети
        char hn[128];
        char LocalIp[15];
        char LocalIp_2[15];
        WORD wVersionRequested;
        WSADATA wsaData;
        wVersionRequested = MAKEWORD(1, 0);
        int err = WSAStartup(wVersionRequested, &wsaData);
        if(err == 0)
                {
                if(gethostname((char *)&hn, 128))
                        return false;
                struct hostent *adress;
                adress = gethostbyname(hn);
                if(adress){
                        sprintf(LocalIp,"%d.%d.%d.%d",
                        (unsigned char)adress->h_addr_list[0][0],
                        (unsigned char)adress->h_addr_list[0][1],
                        (unsigned char)adress->h_addr_list[0][2],
                        (unsigned char)adress->h_addr_list[0][3]);}
                struct hostent *adress_2;
                adress_2 = gethostbyname(adr);
                if(adress_2){
                        sprintf(LocalIp_2,"%d.%d.%d.%d",
                        (unsigned char)adress_2->h_addr_list[0][0],
                        (unsigned char)adress_2->h_addr_list[0][1],
                        (unsigned char)adress_2->h_addr_list[0][2],
                        (unsigned char)adress_2->h_addr_list[0][3]);}
                if (!strcmp(LocalIp,LocalIp_2))
                        return true;
                else
                        return false;
                }
        else
                return false;
}
//---------------------------------------------------------------------------
void start_program()
{
        //загружаем разрешенные ip
        ifstream in3("config\\ip.cnf");
        Clients.ClientsWhiteList ="";
        if(in3){
                do{
                        char s[256];
                        in3.getline(s,sizeof s,'\n');
                        Clients.ClientsWhiteList +=s;
                        //Clients.ClientsWhiteList +="\r\n";
                        }while(!in3.eof());
                }
        in3.close();
        //открываем файл config\\word.cnf с макроопределениями
        set_dir(NULL);
        ifstream in("config\\word.cnf");
        if(in){
                for(int i=8;in && i < _WORD;i++){
                        in.getline(word[0][i],256,'\n');
                        in.getline(word[1][i],256,'\n');
                }
        in.close();}
        //загружаем параметры компиляторов
        set_dir(NULL);
        ifstream in2("config\\compilers.cnf");
        if(in2)
            for(int i=0;i<17 && in2;i++){
                in2.getline(Compilers[i],sizeof(Compilers[i]),'\n');
                in2.getline(Compiler_dir[i],sizeof(Compiler_dir[i]),'\n');
                in2.getline(Include[i],sizeof(Include[i]),'\n');
                in2.getline(Lib[i],sizeof(Lib[i]),'\n');}
        in2.close();

        //если имеются параметры коммандной строки
        //пропускаем 1 параметр = адрес самой программы
        char *comLine = CmdLine + 1;
        for(; *comLine && *comLine != '"';comLine++);
        for(; *comLine == ' ' || *comLine == '"';comLine++);  //пропускаем пробелы и кавычки
        if(strlen(comLine) != 0){
                //получаем ключ
                for(; *comLine && *comLine != ' ';comLine++)
                                Pass += *comLine;
                        //пропускаем пробелы
                        for(; *comLine == ' ';comLine++);
                        if(*comLine == 0)
                                exit(1);  //нет логина
                //получаем логин
                for(; *comLine && *comLine != ' ';comLine++)
                                Login += *comLine;
                        if(Login == "NULL")  Login = "";
                        //пропускаем пробелы
                        for(; *comLine == ' ';comLine++);
                        if(*comLine == 0)
                                goto _1; //нет комманды
                //получаем комманду
                strcpy(LastData, comLine);
                LastClient = "-1";
                Do();
                exit(0);                     //выходим
                }
_1:

        //если уже работает программа
        int i;
        //Находим папку программы
        strcpy(exe_path,ParamStr(0).c_str());
        for(i=strlen(exe_path)-1;exe_path[i]!='\\';i--);
        exe_path[i]='\0';
        //Находим папку с командами
        strcpy(cmd_dir,exe_path);
        strcat(cmd_dir,"\\command\\");
}
//---------------------------------------------------------------------------
int ClientsList()
{
        Clients.Clear();
        for(int i=0;i<ServerSocket->Socket->ActiveConnections;i++)
                {
                Clients.Add
                        (ServerSocket->Socket->Connections[i]->
                        RemoteAddress);
                }
        return 0;
}
//---------------------------------------------------------------------------
void SendAns()
{
        //проверка не отключился ли клиент
        int k=-1;
        for(int i=0;i<ServerSocket->Socket->ActiveConnections;i++)
                if(ServerSocket->Socket->Connections[i]->RemoteAddress==LastClient)
                        k=i;
        //обработка результата
        if(k!=-1){
                String snd = Ans;
                if(snd[snd.Length()-1]!='\n' && snd.Length()!=0)
                        snd +="\n";
                ServerSocket->Socket->Connections[k]
                        ->SendText(snd);
                ShowAns("To " +
                        ServerSocket->Socket->Connections[k]
                        ->RemoteAddress + ": " + snd);
                //отключение от клиента
                ServerSocket->Socket->Connections[k]
                        ->SendText("exit\n");
                ShowAns("To " +
                        ServerSocket->Socket->Connections[k]
                        ->RemoteAddress + ": exit\n");}
        else
                ShowAns("Клиент отключился. Ответ ( " + Ans + " ) не отослан.\n");
}
//---------------------------------------------------------------------------
