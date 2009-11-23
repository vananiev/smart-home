//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "fstream.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmClient *frmClient;
char LastData[2048];
//---------------------------------------------------------------------------
__fastcall TfrmClient::TfrmClient(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmClient::ClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        Memo2->Lines->Add("Connect to: " + Socket->RemoteHost);
        Memo1->Enabled=True;
}
//---------------------------------------------------------------------------
void __fastcall TfrmClient::ClientError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
        Memo2->Lines->Add("Error connecting to:" + edtServer->Text);
        ErrorCode = 0;        
}
//---------------------------------------------------------------------------
void __fastcall TfrmClient::ClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
        strcpy(LastData,Socket->ReceiveText().c_str());
        Memo2->Lines->Add(Client->Host + ": " +LastData);
}
//---------------------------------------------------------------------------
void __fastcall TfrmClient::FormCreate(TObject *Sender)
{
        edtPort->Text=Client->Port;
        Memo1->Lines->Clear();
        Memo2->Lines->Clear();        
}
//---------------------------------------------------------------------------
void __fastcall TfrmClient::btnDisconnectClick(TObject *Sender)
{
        Client->Active = false;
        Memo2->Lines->Add("");
}
//---------------------------------------------------------------------------
void __fastcall TfrmClient::btnConnectClick(TObject *Sender)
{
        Client->Active=False;
        Memo2->Lines->Add("All connections is closed.");
        if (TryStrToInt(edtPort->Text,Client->Port))
                {
                Client->Port=StrToInt(edtPort->Text);
                }
                else
                {
                 ShowMessage("Номер порта должен быть числом.");
                }
        Client->Host=edtServer->Text;
        Memo2->Lines->Add("Connecting to " + edtServer->Text
        + " port: "+IntToStr(Client->Port));
        Client->Active=True;
}
//---------------------------------------------------------------------------


void __fastcall TfrmClient::ClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        Memo2->Lines->Add("Disconnected from " + edtServer->Text
        + " port: "+IntToStr(Client->Port));
        Memo2->Lines->Add("");
}
//---------------------------------------------------------------------------
int get_data ()
{
	unsigned char data[512];
        char command[32],value[255];
        int num=0,i,j;
        bool flag=True;
        command[0]='\0';
        for(;flag;)
                {
                Sleep(50);
                //находим команду
                for(i=0;i<strlen(LastData);i++)
                        if(LastData[i]!=':')
                                command[i]=LastData[i];
                        else
                                {
                                command[i]='\0';
                                //находим параметр
                                for(j=i+1;j<strlen(LastData);j++)
                                        value[j-i-1]=LastData[j];
                                value[j-i-1]='\0';
                                flag=False;
                                break;
                                }
                }
        if(!strcmp(command,"file"))
                frmClient->Client->Socket
                                ->SendText("file_name_ok");
                else
                        return 1;

	// open
	ofstream out("C:\\1.txt" , ios::out| ios::binary);
	if (!out) return 1;

	//  получаем пакетами по размеру буфера data
	do
	        {
                //команда
                flag=true;
                for(;flag;)
                        {
                        Sleep(50);
                        for(i=0;i<strlen(LastData);i++)
                                if(LastData[i]!=':')
                                        command[i]=LastData[i];
                                        else
                                        command[i]='\0';
                        if (!strcmp(command,strcat("file_block_",IntToStr(num).c_str())))
                                {for(int j=i+1;i<strlen(LastData);i++)
                                        data[j-i-1]=LastData[i];
                                flag=false;}
                        if(!strcmp(command,"end_file" ))
				{
				data[0]='\0';
                                flag=false;
				}
                        }
		out.write((char *) data,sizeof data);
                frmClient->Client->Socket->
                                SendText
                                ("file_block_" + IntToStr(num)+ "_ok");
                num++;
	        }while(strcmp(command,"end_file"));
	out.close();
	return 0;
}
void __fastcall TfrmClient::FormClick(TObject *Sender)
{
        get_data ();
}
//---------------------------------------------------------------------------



void __fastcall TfrmClient::Memo1KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == VK_RETURN)
                {
                String snd = Memo1->Lines->Text.SubString(0,Memo1->Lines->Text.Length()-2);
                snd+='\n';
                Client->Socket->SendText(snd);
                Memo2->Lines->Add("To server: " +snd);
                Memo1->Lines->Clear();
                }
}
//---------------------------------------------------------------------------

