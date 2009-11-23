//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "net.h"
#include "fstream.h"
//#include "cstring.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmServer *frmServer;
int ClientsList();
int send_data (char file[255]);
char LastData[2048];
//---------------------------------------------------------------------------
__fastcall TfrmServer::TfrmServer(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::ServerClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        if(cmbClients->Items->Count==0) Memo1->Enabled=False;
        Memo2->Lines->Add("Disconnect: " + Socket->RemoteAddress);
        //Составление списка клиентов
        Sleep(1000);
        ClientsList();
        Memo2->Lines->Add("");
        Memo2->Lines->Add("Listening port="+IntToStr(Server->Port));
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::ServerRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
        strcpy(LastData,Socket->ReceiveText().c_str());
        Memo2->Lines->Add(Socket->RemoteAddress + ": "+
        LastData);
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::btnPortOkClick(TObject *Sender)
{
       Server->Active=False;
       Memo2->Lines->Add("All connections is closed.");
       if (TryStrToInt(edtPort->Text,Server->Port))
                {
                Server->Port=StrToInt(edtPort->Text);
                }
                else
                {
                 ShowMessage("Номер порта должен быть числом.");
                }
        Memo2->Lines->Add("Listening port="+IntToStr(Server->Port));
        cmbClients->ItemIndex=-1;
        Server->Active=True;
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::FormCreate(TObject *Sender)
{
        Memo1->Lines->Clear();
        Memo2->Lines->Clear();
        edtPort->Text=IntToStr(Server->Port);
        Memo2->Lines->Add( "Listening port="+IntToStr(Server->Port));
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::ServerClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        Memo2->Lines->Add ("");
        Memo2->Lines->Add("Connect to: " + Socket->RemoteAddress);
        //Составление списка клиентов
        Memo1->Enabled=True;
}
//---------------------------------------------------------------------------

void __fastcall TfrmServer::btnDisconnectClick(TObject *Sender)
{
        Server->Active=False;
        Memo2->Lines->Add("Listening off.");
}
//---------------------------------------------------------------------------
int ClientsList()
{
        frmServer->cmbClients->Clear();
        for(int i=0;i<frmServer->Server->Socket->ActiveConnections;i++)
                {
                frmServer->cmbClients->Items->Add
                        (frmServer->Server->Socket->Connections[i]->
                        RemoteAddress);
                }
        return 0;
}
//---------------------------------------------------------------------------




void __fastcall TfrmServer::cmbClientsDropDown(TObject *Sender)
{
        ClientsList();
}
//---------------------------------------------------------------------------

int send_data (char file[255])
{
	unsigned char data[512];
        char file_name[255];
        bool flag;
        int num=0,i,j;
	// open
	ifstream in(file, ios::in| ios::binary);
	if (!in) return 1;
        //находим имя файла
        flag=True;
        for(i=0;i<strlen(file) && flag;i++)
                if(file[i]!='\\')
                        ;
                        else
                        {for(j=i+1;j<strlen(file);j++)
                                file_name[j-i-1]=file[j];
                        file_name[j-i-1]='\0';
                        flag=False;}

	// send data передаем пакетами по размеру буфера data
        //передаем имя файла
        frmServer->Server->Socket->Connections[frmServer->cmbClients->ItemIndex]
                                -> SendText
                                (strcat("file:" , file_name));
        for(;;)
                {
                Sleep(50);
                if(!strcmp(LastData,"file_name_ok"))
                        break;
                }
	while (in)
	        {
		in.read((char *) data,sizeof data);
                frmServer->Server->Socket->Connections[frmServer->cmbClients->ItemIndex]
                                -> SendText
                                (strcat(strcat(strcat("file_block_" , IntToStr(num).c_str()),
                                         ":"), data));
                for(;;)
                        {
                        Sleep(50);
                        if(!strcmp(LastData,strcat(strcat("file_block_",IntToStr(num).c_str()),"_ok")))
                                break;
                        }
                num++;
	        }
        frmServer->Server->Socket->Connections[frmServer->cmbClients->ItemIndex]
                                -> SendText
                                ("end_file");
	in.close();
	return 0;
} 

void __fastcall TfrmServer::FormClick(TObject *Sender)
{
        send_data("C:\\1.txt");        
}
//---------------------------------------------------------------------------

void __fastcall TfrmServer::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == VK_RETURN)
                {
                if(cmbClients->ItemIndex!=-1)
                        {
                        String snd = Memo1->Lines->Text.SubString(0,Memo1->Lines->Text.Length()-2);
                        snd+='\n';
                        Server->Socket->Connections[cmbClients->ItemIndex]
                                ->SendText
                                (snd);
                        Memo2->Lines->Add("To " +
                                Server->Socket->Connections[cmbClients->
                                ItemIndex]->RemoteAddress + ": " +snd);
                        Memo1->Lines->Clear();
                        }
                        else
                        {
                        ShowMessage("Выберите клиента.");
                        }
                }        
}
//---------------------------------------------------------------------------

void __fastcall TfrmServer::Memo1KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == VK_RETURN)
                {
                Memo1->Lines->Text = Memo1->Lines->Text.SubString(0,Memo1->Lines->Text.Length()-2);
                if(cmbClients->ItemIndex!=-1)
                        {
                        String snd = Memo1->Lines->Text + '\n';
                        Server->Socket->Connections[cmbClients->ItemIndex]
                                ->SendText(snd);
                        Memo2->Lines->Add("To " +
                                Server->Socket->Connections[cmbClients->
                                ItemIndex]->RemoteAddress + ": " + snd);
                        Memo1->Lines->Clear();
                        }
                        else
                        {
                        ShowMessage("Выберите клиента.");
                        }
                }        
}
//---------------------------------------------------------------------------

