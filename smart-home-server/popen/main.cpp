//---------------------------------------------------------------------------
#include <windows.h>
#pragma hdrstop
#include "fstream.h"
#include "dir.h"
int set_dir(char *path,char *dir);
int main_(int argc, char* argv[]);
//---------------------------------------------------------------------------

#pragma argsused
WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
        //путь к файлу
        char run_dir[1024];
        GetModuleFileName(GetModuleHandle(NULL),run_dir,1024);
        //разделяем командную строку
	char* args[16];
        int i=0;
        args[i]=run_dir;
        bool newstr=true;
        bool kav=false;
        for(int k=0;lpCmdLine[k];k++)
        	{
                if(lpCmdLine[k]=='"')
                	{
                        kav = !kav;
                        lpCmdLine[k]=0;
                        }
                else if(newstr)
                        {
                        i++;
                	args[i]=&(lpCmdLine[k]);
                        newstr = false;
                        }
        	else if(lpCmdLine[k]==' ' && !kav)
                	{
                        lpCmdLine[k]=0;
                        for(;lpCmdLine[k+1]==' ' && lpCmdLine[k+1];k++);
                        newstr=true;
                        }
                }
        i++;
     	return main_(i,args);
}
//---------------------------------------------------------------------------
int main_(int argc, char* argv[])
{
        bool flag=false;
        char path[512];
        strcpy(path,argv[0]);
        int i;
        for(i=strlen(path)-1;path[i]!='\\';i--);
        path[i]='\0';
        strcat(path,"\\result");
        ofstream out (path,ios::trunc);
        if(!out)
                return -1;
        if(argc == 1){
                out<<"Необходим один параметр. Вызовите с параметром help для уточнения"<<endl;
                out.close();
                return -1;}
        if(!strcmp(argv[1],"help")){
                out<<"Формат вызова: popen имя_программы"<<endl;
                out.close();
                return -1;}
        char com[1024]="\"";
        strcat(com,argv[1]);
        for(int i=2;i<argc;i++){
                strcat(com,"\" \"");
                strcat(com,argv[i]);}
        strcat(com,"\"");
        FILE *f = _popen(com,"r");
        if(f == NULL){
                out.close();
                return 3;}
        char buffer[1024];
        while (fgets(buffer,sizeof(buffer), f)) {
                flag=true;
                out<<buffer;
        }
        if(!flag)
                out<<"Ошибка чтения потока (файл не найден, не удалось прочитать или команда не вернула никокого значения)"<<endl;
        out.close();
        _pclose(f);
        return -1;

}
/*/---------------------------------------------------------------------------
int set_dir(char *path,char *dir)
{
        int i;
        for(i=strlen(path)-1;path[i]!='\\';i--);
        path[i]='\0';
        if(dir!=NULL)
                strcat(path,dir);
	setdisk(toupper(path[0])-'A');
	if (chdir(path))
                return 1;
        return 0;
}
*/



