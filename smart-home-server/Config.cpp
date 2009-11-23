//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "head.h"
#include "Config.h"
#include<fstream.h>
extern set_dir(char *dir);
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmConfig *frmConfig;
//---------------------------------------------------------------------------
__fastcall TfrmConfig::TfrmConfig(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfig::PagesChange(TObject *Sender)
{
        switch (Pages->ActivePageIndex){
                case 0:         //компилятор с++
                        break;
                }
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfig::FormShow(TObject *Sender)
{
        edtPath->Text = Compiler_dir[0];
        edtInc->Text = Include[0];
        edtLib->Text = Lib[0];
        mComp->Lines->Clear();
        for(int i=1;i<17 && strlen(Compilers[i]);i++){
                mComp->Lines->Add(Compilers[i]);
                mComp->Lines->Add(Compiler_dir[i]);
                mComp->Lines->Add(Include[i]);
                mComp->Lines->Add(Lib[i]);
                }
}
//---------------------------------------------------------------------------

void __fastcall TfrmConfig::FormHide(TObject *Sender)
{
        strcpy(Compiler_dir[0],edtPath->Text.c_str());
        strcpy(Include[0],edtInc->Text.c_str());
        strcpy(Lib[0],edtLib->Text.c_str());
        //подгоняем чтоб делилось на 4
        mComp->Lines->Add("");
        mComp->Lines->Add("");
        mComp->Lines->Add("");
        mComp->Lines->Add("");
        for(int i=0,j=1;mComp->Lines->Count-i>=4;j++){
                strcpy(Compilers[j],mComp->Lines->Strings[i++].c_str());
                strcpy(Compiler_dir[j],mComp->Lines->Strings[i++].c_str());
                strcpy(Include[j],mComp->Lines->Strings[i++].c_str());
                strcpy(Lib[j],mComp->Lines->Strings[i++].c_str());
                }
        //сохраняем параметряы компиляторов
        set_dir(NULL);
        ofstream out("config\\compilers.cnf",ios::trunc);
        if(out)
           for(int i=0;i<17 && strlen(Compilers[i]);i++){
                out<<Compilers[i]<<endl;
                out<<Compiler_dir[i]<<endl;
                out<<Include[i]<<endl;
                out<<Lib[i]<<endl;
                }
        out.close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfig::FormCreate(TObject *Sender)
{
        Example->Caption = "В каждой новой строке указывается код компилятора (три символа), \r\nпуть к компилятору, путь к Include директории, путь к Library директории.\r\nВсе пути заключены кавычки. В пути к папке не допустимо наличие пробелов. Если не задаются Include и Lib директории, то оставлять пустые строчки.\r\nДлжны быть указаны полные пути.\r\nВсего возможно указать 15 компиляторов.\r\nНапример:\r\ncom\r\n\"c:\\compil\\compil.exe\"\r\n\r\n\r\ng++\r\n\"c:\\g++\\g.exe\"\r\n\"c:\\g++\\Include\";\"c:\\g++\\Include\\my\"\r\n\"c:\\g++\\Lib\";\"c:\\g++\\Lib\\my\"\r\n";
}
//---------------------------------------------------------------------------
