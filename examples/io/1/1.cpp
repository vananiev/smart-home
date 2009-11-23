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
	//карта сопоставления номера вывода LPT с пором и битом
	int LPT[8]={1,2,4,8,16,32,64,128};

	ofstream out("result",ios::trunc);
	if(!out)
		return 1;

	if(argc<=1 || argc > 3){
		out<< "Ошибка применения аргументов : 1)Установки: Номер_утройства  Значение  2) Просмотра состояния: Номер_утройства (от 1 до 8), где Значение: 1 - включить ; 0 - выключить.";
		out.close();
		return -1;
	}
	
	if(!strcmp(argv[1],"help")){
		out<< "Формат :1)Установки: Номер_утройства  Значение  2) Просмотра состояния: Номер_утройства . Где Номер_утройства число от 1 до 8, а Значение: 1 - включить ; 0 - выключить.";
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
		if(adr<1 || adr>8){
			out<< "Неверный Номерa_утройства. Для справки выполните с параметром help";
			out.close();
			return -1;}
		data = ReadFromPort(888);
		data= data & LPT[adr-1];
		StopDriver();
		if(data==0)
			out << "Устройство "<<adr<<" выключено";
		else
			out << "Устройство "<<adr<<" включено";
		out.close();
		return -1;

	}

	if(argc == 3){			//запись в порт
		adr =atoi(argv[1]);
		data =atoi(argv[2]);
		if(adr<1 || adr>8 ){
			out<< "Неверный Номерa_утройства. Для справки выполните с параметром help";
			out.close();
			return -1;}
		if(data<0 || data>1){
			out << "Неверное состояние (2 параметр). Для справки выполните с параметром help";
			out.close();
			return -1;}
		if(data==1)
			data=LPT[adr - 1];
		else
			data = 0;
		//установка
		short int t=ReadFromPort(888);
		t= t | data;
		WriteToPort(888, t);
		//проверка
		t=ReadFromPort(888);
		t= t & LPT[adr - 1];
		if(data == t){
			StopDriver();
			if(data == 0)
				out << "Устройство "<<adr<<" выключено";
			else
				out << "Устройство "<<adr<<" включено";
			out.close();
			return -1;
		}
		else{
			t=ReadFromPort(888);
			t= t & LPT[adr - 1];
			StopDriver();
			if(t == 0)
				out<<"Ошибка управления устройством "<<adr<<". Статус: выключен";
			else
				out<<"Ошибка управления устройством "<<adr<<". Статус: включен";
			out.close();
			return -1;
		}
	}
	return 2;
}


