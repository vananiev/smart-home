//---------------------------------------------------------------------------
#include "head.h"
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "GetIP.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCon *frmCon;
//---------------------------------------------------------------------------
__fastcall TfrmCon::TfrmCon(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCon::Button1Click(TObject *Sender)
{
        SerGetIP->Active=False;
        //устанавливаем адреса сайтов
        strcpy(SITE ,edtSite->Text.c_str());
        strcpy(ADR1,(edtSite->Text + "/getip.php").c_str());
        strcpy(ADR2 , (edtSite->Text + "/getip_login.php").c_str());
        //адрес компьютера в локальной сети
        char hn[128];
        char LocalIp[15];
        WORD wVersionRequested;
        WSADATA wsaData;
        wVersionRequested = MAKEWORD(1, 0);
        int err = WSAStartup(wVersionRequested, &wsaData);
        if(err == 0)
                {
                if(gethostname((char *)&hn, 128))
                        edName->Text = "Ошибка.";
                struct hostent *adr;
                adr = gethostbyname(hn);
                if(adr){
                        sprintf(LocalIp,"%d.%d.%d.%d",
                        (unsigned char)adr->h_addr_list[0][0],
                        (unsigned char)adr->h_addr_list[0][1],
                        (unsigned char)adr->h_addr_list[0][2],
                        (unsigned char)adr->h_addr_list[0][3]);}
                else
                        edName->Text = "Ошибка.";
                edName->Text = hn;
                }
        else
                edName->Text = "Ошибка.";
        //IP
        //установка порта
        int t;
        if (TryStrToInt(edtPort->Text,t))
                SerGetIP->Port=StrToInt(edtPort->Text);
                else{
                 ShowMessage("Номер порта должен быть числом.");
                 edtPort->Text = SerGetIP->Port;}
        //попытка соединения
        char a[1024];
        if(edtLogin->Text=="")
                sprintf(a,"http://%s?port=%d&name=%s",
                                ADR1,
                                SerGetIP->Port,
                                LocalIp);
        else
                sprintf(a,"http://%s?port=%d&name=%s&login=%s",
                                ADR2,
                                SerGetIP->Port,
                                LocalIp,
                                edtLogin->Text.c_str());
        SerGetIP->Active=True;
        void *ret=ShellExecuteA(0,NULL,a,NULL , NULL, 1);
        if((int)ret <= 32){
                SerGetIP->Active=False;
                edIP->Text = "Ошибка. Проверьте интерет соединение.";}
}
//---------------------------------------------------------------------------
void __fastcall TfrmCon::FormCreate(TObject *Sender)
{
        SerGetIP->Active=False;
        edtSite->Text = SITE;        
}
//---------------------------------------------------------------------------
void __fastcall TfrmCon::SerGetIPClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
        edIP->Text=Socket->ReceiveText();
        Socket->SendText("ok\n");
        Socket->SendText("exit\n");
        SerGetIP->Active=False;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCon::FormDestroy(TObject *Sender)
{
        SerGetIP->Active=False;        
}

