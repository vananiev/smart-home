#include "stdafx.h"

#include "iostream.h"
#include "conio.h"
#include "stdlib.h"
#include "windows.h"
#include "h.h"
#include "fstream.h"

extern HANDLE hDrv;


int main(int argc, char* argv[])
{
	unsigned short int adr;
	unsigned short data;

	ofstream out("result",ios::trunc);
	if(!out)
		return 1;

	if(argc<=1 || argc > 3){
		out<< "Ошибка : Формар вызова чтения: PORT ; записи PORT DATA";
		out.close();
		return -1;
	}
	
	if(!strcmp(argv[1],"help")){
		out<< "Формар вызова чтения: PORT ; записи PORT DATA";
		out.close();
		return -1;
	}
	
	bool status=InstallDriverWithSCManager();
	if (status==false){
		out<< "error : Не удалось запустить Port.sys";
		out.close();
		return -1;
	}

	if(argc==2){ 		//чтение из порта
		adr =atoi(argv[1]);
		data = ReadFromPort(adr);
		StopDriver();
		out << "Порт "<<adr<<" установлен в "<<data;
		out.close();
		return -1;

	}

	if(argc == 3){			//запись в порт
		adr =atoi(argv[1]);
		data =atoi(argv[2]);
		WriteToPort(adr, data);
		if(data == ReadFromPort(adr)){
			StopDriver();
			out << "Порт "<<adr<<" установлен в "<<data;
			out.close();
			return -1;
		}
		else{
			StopDriver();
			out<<"Ошибка записи в порт "<<adr<<" значения "<<data;
			out.close();
			return -1;
		}
	}
	return 2;
}


