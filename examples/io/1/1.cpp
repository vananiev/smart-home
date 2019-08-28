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
	//����� ������������� ������ ������ LPT � ����� � �����
	int LPT[8]={1,2,4,8,16,32,64,128};

	ofstream out("result",ios::trunc);
	if(!out)
		return 1;

	if(argc<=1 || argc > 3){
		out<< "������ ���������� ���������� : 1)���������: �����_���������  ��������  2) ��������� ���������: �����_��������� (�� 1 �� 8), ��� ��������: 1 - �������� ; 0 - ���������.";
		out.close();
		return -1;
	}
	
	if(!strcmp(argv[1],"help")){
		out<< "������ :1)���������: �����_���������  ��������  2) ��������� ���������: �����_��������� . ��� �����_��������� ����� �� 1 �� 8, � ��������: 1 - �������� ; 0 - ���������.";
		out.close();
		return -1;
	}
	
	bool status=InstallDriverWithSCManager();
	if (status==false){
		out<< "error : �� ������� ��������� Port.sys";
		out.close();
		return -1;
	}

	if(argc==2){ 		//������ �� �����
		adr =atoi(argv[1]);
		if(adr<1 || adr>8){
			out<< "�������� �����a_���������. ��� ������� ��������� � ���������� help";
			out.close();
			return -1;}
		data = ReadFromPort(888);
		data= data & LPT[adr-1];
		StopDriver();
		if(data==0)
			out << "���������� "<<adr<<" ���������";
		else
			out << "���������� "<<adr<<" ��������";
		out.close();
		return -1;

	}

	if(argc == 3){			//������ � ����
		adr =atoi(argv[1]);
		data =atoi(argv[2]);
		if(adr<1 || adr>8 ){
			out<< "�������� �����a_���������. ��� ������� ��������� � ���������� help";
			out.close();
			return -1;}
		if(data<0 || data>1){
			out << "�������� ��������� (2 ��������). ��� ������� ��������� � ���������� help";
			out.close();
			return -1;}
		if(data==1)
			data=LPT[adr - 1];
		else
			data = 0;
		//���������
		short int t=ReadFromPort(888);
		t= t | data;
		WriteToPort(888, t);
		//��������
		t=ReadFromPort(888);
		t= t & LPT[adr - 1];
		if(data == t){
			StopDriver();
			if(data == 0)
				out << "���������� "<<adr<<" ���������";
			else
				out << "���������� "<<adr<<" ��������";
			out.close();
			return -1;
		}
		else{
			t=ReadFromPort(888);
			t= t & LPT[adr - 1];
			StopDriver();
			if(t == 0)
				out<<"������ ���������� ����������� "<<adr<<". ������: ��������";
			else
				out<<"������ ���������� ����������� "<<adr<<". ������: �������";
			out.close();
			return -1;
		}
	}
	return 2;
}


