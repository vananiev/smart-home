#define _MAIN
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "main.h"
#include "GetIP.h"
#include "Login.h"
#include "Msg.h"
#include "Config.h"
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
#include "head.h"
#include "kernel.h"
//---------------------------------------------------------------------------
TfrmServer *frmServer;
bool key_ctrl_down;  //������ ctrl
#define _TAB 7         //����� �������
TShape* Tab[_TAB];       //�������
unsigned int TabIndex=0;        //�������� �������
bool fTab = false;
unsigned int iTab=-1;
//---------------------------------------------------------------------------
void ShowAns(String str)
{
        if(str == "")
                frmServer->Memo2->Lines->Add(Ans);
        else
                frmServer->Memo2->Lines->Add(str);
}
//---------------------------------------------------------------------------
__fastcall TfrmServer::TfrmServer(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::ServerClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        if(Clients.Count==0) Memo1->Enabled=False;
        ShowAns("Disconnect: " + Socket->RemoteAddress);
        //����������� ������ ��������
        Sleep(1000);
        ClientsList();
        //Memo2->Lines->Add("");
        ShowAns("Listening port="+IntToStr(ServerSocket->Port));
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::ServerRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
        strcpy(LastData,Socket->ReceiveText().c_str());
        ShowAns(Socket->RemoteAddress + ": "+
        LastData);
        //��� �������
        LastClient=Socket->RemoteAddress;
        //��������� ����������
        Do();
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::btnPortOkClick(TObject *Sender)
{
       LastClient ="-1";
       strcpy(LastData, ((String)"port "+edtPort->Text).c_str());
       Do();
       /*
       if(ClientSocket->Active){    //�������� �� ���������� ���. ���-������
                ShowMessage("����� � ����������� ��������� ����. ����� �� �����������. ���������� �������.");
       }else{
       ServerSocket->Active=False;
       ShowAns("All connections is closed.");
       int t;
       if (TryStrToInt(edtPort->Text,t))
                {
                ServerSocket->Port=StrToInt(edtPort->Text);
                ClientSocket->Port=ServerSocket->Port;
                }
                else
                {
                 ShowMessage("����� ����� ������ ���� ������.");
                 edtPort->Text = ServerSocket->Port;
                }
        ShowAns("Listening port="+IntToStr(ServerSocket->Port));
        ServerSocket->Active=True;
        ClientsList();}   */
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::ServerClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        //ShowAns ("");
        ShowAns("Connect to: " + Socket->RemoteAddress);
        Memo1->Enabled=True;
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::btnDisconnectClick(TObject *Sender)
{
        LastClient="-1";
        strcpy(LastData,"disconnect");
        Do();
        /*ServerSocket->Active=False;
        ClientSocket->Active=False;
        ShowAns("Listening off.");*/
}
//---------------------------------------------------------------------------
int RefreshClientsList()
{
        frmServer->cmbClients->Clear();
        int cnt=Clients.Count;
        for(int i=0;i<cnt;i++)
                {
                frmServer->cmbClients->Items->Add
                        (Clients.Clients[i]);
                }
        return 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::cmbClientsDropDown(TObject *Sender)
{
        ClientsList();
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
                        ServerSocket->Socket->Connections[cmbClients->ItemIndex]
                                ->SendText(snd);
                        ShowAns("To " +
                                ServerSocket->Socket->Connections[cmbClients->
                                ItemIndex]->RemoteAddress + ": " + snd);
                        Memo1->Lines->Clear();
                        }
                        else
                        {
                        ShowMessage("�������� �������.");
                        }
                }
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::TimerTimer(TObject *Sender)
{
        //��� ������� �� ����� ������������?
        if(Clients.IpFilterOn){
        int n = Clients.Count;          // memIP->Lines->Count;
        for(int j=0;j<ServerSocket->Socket->ActiveConnections;j++){
                bool exist=false;
                for(int i=0;i<n;i++)
                        if(Clients.Clients[i].Trim() ==
                           ServerSocket->Socket->Connections[j]->RemoteAddress)
                                   exist=true;
                 if(!exist){
                        ShowAns("�� ����������� IP: " +
                        ServerSocket->Socket->Connections[j]->RemoteAddress
                                  + " ���������� ���������.");
                        ServerSocket->Socket->Disconnect(j);}
                 }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::btnExecuteClick(TObject *Sender)
{
        LastData[0]=0;
        strcpy(LastData,edExe->Text.c_str());
        LastClient = "-1";  //���� � ���� ������
        Do();
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::ClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        //�������� �������
        ClientSocket->Socket->SendText(arg);
        if(LastClient == "-1")//��� ��?
                ShowAns(Socket->RemoteAddress + ": " + arg);
        else
                ShowAns("�������� ������ ( " + Socket->RemoteAddress + " ).");
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::ClientError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
        ShowAns("Error connecting to:" + Socket->RemoteAddress);
        ErrorCode = 0;
        if(LastClient != "-1"){   //��� �� ����������?
        //�������� �� ���������� �� ������
        int k=-1;
        for(int i=0;i<ServerSocket->Socket->ActiveConnections;i++)
                if(ServerSocket->Socket->Connections[i]->RemoteAddress==LastClient)
                        k=i;
        if(k!=-1){
                if(!Socket->Connected)
                        ServerSocket->Socket->Connections[k]
                                        ->SendText("������ ��� �����������. ������ �� ��������.\n");
                else
                        ServerSocket->Socket->Connections[k]
                                        ->SendText("����������� ��������, �� ������ �����. ���������� ����� ��������� �����.\n");
                ServerSocket->Socket->Connections[k]
                                        ->SendText("exit\n");}
        else
                ShowAns("������ ����������. �����  �� �������.\n");
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::ClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
        Ans = Socket->ReceiveText();
        if(LastClient != "-1"){//��� ��?
        ShowAns("������� ����� ( " + Socket->RemoteAddress + " ).");
        //�������� ������
        //�������� �� ���������� �� ������
        int k=-1;
        for(int i=0;i<ServerSocket->Socket->ActiveConnections;i++)
                if(ServerSocket->Socket->Connections[i]->RemoteAddress==LastClient)
                        k=i;
        //��������� ����������
        if(k!=-1){
                String snd = Ans;
                if(snd[snd.Length()]!='\n' && snd.Length()!=0)
                        snd +="\n";
                ServerSocket->Socket->Connections[k]
                        ->SendText(snd);}
        else
                ShowAns("������ ����������. ����� �� �������.\n");
        }
        else
                ShowAns(Socket->RemoteAddress + ": " +Ans);
        //����������� ��� ���������� ��������
        if(Ans == "exit\n")
                ClientSocket->Active=False;
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::ClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        ShowAns("Disconnected from:  " +
                Socket->RemoteAddress + "      port: " + Socket->RemotePort);
        //ShowAns("");
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::ClientConnecting(TObject *Sender,
      TCustomWinSocket *Socket)
{
        ShowAns("Connecting to: " + ClientSocket->Host);
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::N3Click(TObject *Sender)
{
        if(ClientSocket->Active) //�������� �� ���������� ���. ���-��
                ShowMessage("����� � ����������� ��������� ����. ���������� �������.");
        else{
                //�����������
                btnDisconnectClick(Sender);
                //
                frmCon = new TfrmCon(frmServer);
                frmCon->edtPort->Text=edtPort->Text;
                frmCon->edtLogin->Text=Login;
                frmCon->ShowModal();
                if(edtPort->Text != frmCon->edtPort->Text)
                        {edtPort->Text = frmCon->edtPort->Text;
                        btnPortOkClick(Sender);}
                delete  frmCon;
                //������������
                btnPortOkClick(Sender);
                }
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::N4Click(TObject *Sender)
{
        exit(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::FormPaint(TObject *Sender)
{
        for(int i=0; i<ParamCount();i++)
                if(ParamStr(i)=="/hide")
                        frmServer->Visible=False;
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::ServerAccept(TObject *Sender,
      TCustomWinSocket *Socket)
{
if(Clients.IpFilterOn){
        int n = Clients.Count;          // memIP->Lines->Count;
        for(int j=0;j<ServerSocket->Socket->ActiveConnections;j++){
                bool exist=false;
                for(int i=0;i<n;i++)
                        if(Clients.Clients[i].Trim() ==
                           ServerSocket->Socket->Connections[j]->RemoteAddress)
                                   exist=true;
                 if(!exist){
                        ShowAns("�� ����������� IP: " +
                        ServerSocket->Socket->Connections[j]->RemoteAddress
                                  + " ���������� ���������.");
                        ServerSocket->Socket->Disconnect(j);}
                 }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::EnableIPClick(TObject *Sender)
{
        Clients.IpFilterOn = EnableIP->Checked;
        lblIP->Visible = Clients.IpFilterOn;
        memIP->Visible = Clients.IpFilterOn;
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::memIPExit(TObject *Sender)
{
        String s = memIP->Lines->Text;
        Clients.SetWhiteList(s);
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::N6Click(TObject *Sender)
{
        //�������� ����� ����
        unsigned char CHARSET[18]={ANSI_CHARSET ,
                DEFAULT_CHARSET,
                SYMBOL_CHARSET,
                SHIFTJIS_CHARSET,
                HANGEUL_CHARSET,
                HANGUL_CHARSET,
                GB2312_CHARSET,
                CHINESEBIG5_CHARSET,
                OEM_CHARSET,
                JOHAB_CHARSET,
                HEBREW_CHARSET,
                ARABIC_CHARSET,
                GREEK_CHARSET,
                TURKISH_CHARSET,
                VIETNAMESE_CHARSET,
                THAI_CHARSET,
                EASTEUROPE_CHARSET,
                RUSSIAN_CHARSET};
        char CHARSET_str[sizeof(CHARSET)][32]={"ANSI_CHARSET" ,
                "DEFAULT_CHARSET",
                "SYMBOL_CHARSET",
                "SHIFTJIS_CHARSET",
                "HANGEUL_CHARSET",
                "HANGUL_CHARSET",
                "GB2312_CHARSET",
                "CHINESEBIG5_CHARSET",
                "OEM_CHARSET",
                "JOHAB_CHARSET",
                "HEBREW_CHARSET",
                "ARABIC_CHARSET",
                "GREEK_CHARSET",
                "TURKISH_CHARSET",
                "VIETNAMESE_CHARSET",
                "THAI_CHARSET",
                "EASTEUROPE_CHARSET",
                "RUSSIAN_CHARSET"};
        static unsigned int CHARSET_int =-1;
        CHARSET_int++;
        Memo2->Font->Name = "Courier New";
        Memo2->Font->Charset= CHARSET[CHARSET_int%sizeof(CHARSET)];
        MessageBox(NULL,CHARSET_str[CHARSET_int%sizeof(CHARSET)],"���������� ����� ��������",0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::Dos1Click(TObject *Sender)
{
        Memo2->Lines->SetText(AnsiToDos(Memo2->Lines->GetText()));
        MessageBox(NULL,"Dos","���������� ����� ��������",0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::ANSIF41Click(TObject *Sender)
{
        Memo2->Lines->SetText(DosToAnsi(Memo2->Lines->GetText()));
        MessageBox(NULL,"Ansi","���������� ����� ��������",0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::N7Click(TObject *Sender)
{
        Memo2->Lines->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::N8Click(TObject *Sender)
{
        N8->Checked = !N8->Checked;
        AutoDosToAnsi =  N8->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::N9Click(TObject *Sender)
{
        btnDisconnectClick(Sender);
        frmConfig->ShowModal();
        btnPortOkClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::edExeKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	        if(GetAsyncKeyState(VK_CONTROL) < 0 && Key == 16)
                btnExecuteClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::edExeKeyPress(TObject *Sender, char &Key)
{
	//if(Key == VK_TAB)
        //	{
        //        edExe->
        //        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::N10Click(TObject *Sender)
{
        //���������� ������ � ����
        set_dir("\\command\\");
        ofstream out("commads.txt",ios::trunc);
        if(!out){
                MessageBox(NULL,"������ ��� ����������","������",NULL);
                return;}
        for(int i=0;i<edExe->Lines->Count;i++)
                out<<edExe->Lines->Strings[i].c_str()<<endl;
        MessageBox(NULL,"�������� � \\command\\commands.txt\"","��������",NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::FormCreate(TObject *Sender)
{
        start_program();
        //���� ��������� � ������� ������ ��
        int i;
        for(i=0; i<ParamCount();i++)
                if(ParamStr(i)=="/hide")
                        break;
        if(i!=ParamCount()){
                Pass=ParamStr(i+1);
                if(Pass=="") Pass="default";
                Login=ParamStr(i+2);
                frmServer->Visible=False;
                Tray->Visible=False;
                }
                else{
                //����� ����� � ������ ������ � ������
                frmLogin=new TfrmLogin(frmServer);
                int ret;
                do{
                        ret=frmLogin->ShowModal();
                        if(ret==2)
                                 ExitProcess(1);
                }while(ret!=1 || frmLogin->edtPass->Text=="");
                Pass=frmLogin->edtPass->Text;
                Login=frmLogin->edtLogin->Text;
                delete frmLogin;}
        //�������������� ������� ���
        Memo1->Lines->Clear();
        Memo2->Lines->Clear();
        Tab[i] = Shape;
        EnableIP->Checked=Clients.IpFilterOn;
        lblIP->Visible = Clients.IpFilterOn;
        memIP->Visible = Clients.IpFilterOn;
        Height = 530;
        //���� �������������
        AutoDosToAnsi = N8->Checked;
        //����������� �������
        ClientSocket = Client;
        ServerSocket = Server;
        //���� �������
        Timer->Enabled =Clients.IpFilterOn;
        edtPort->Text=IntToStr(ServerSocket->Port);
        ClientSocket->Port=ServerSocket->Port;
        ShowAns( "Listening port="+IntToStr(ServerSocket->Port));
        //��������� ���������� �������� ����
        UpdateFace();
}
//---------------------------------------------------------------------------
void UpdateFace()
{
        //��������� �����
        frmServer->edtPort->Text=ServerSocket->Port;
        //��������� ������ ������������ ��������
        RefreshClientsList();
        //������ ����� ip-�������
        frmServer->memIP->Lines->Text = Clients.ClientsWhiteList;
}

void __fastcall TfrmServer::Memo2MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Memo2->Hint="��� ������";
}
//---------------------------------------------------------------------------

void __fastcall TfrmServer::N11Click(TObject *Sender)
{
        int i;
        //����� ����� �������
        for(i=0;i<_TAB;i++)if(Tab[i]==NULL) break;
        //
        if(i==_TAB)
                {MessageBox(NULL,"������ ������� ������� ������",NULL,NULL);
                return;}
        int C[_TAB]={0x00ffffff,0x00FF9B9B,0x00FFED9B,0x009BFF9D,0x009BFFFE,0x009BBAFF,0x00FF9BFE};
        Tab[i]=new TShape(frmServer);
        Tab[i]->Parent=frmServer;
        Tab[i]->Brush->Color=(TColor)C[i];
        Tab[i]->Top = Shape->Top;
        Tab[i]->Height = Shape->Height;
        Tab[i]->Width = Shape->Width;
        Tab[i]->Left = Shape->Left + i*(1.5*Shape->Width);
        Tab[i]->Tag = i;
        Tab[i]->OnMouseUp = Shape->OnMouseUp;
        Tab[i]->Cursor = Shape->Cursor;
        Tab[i]->Hint = (String)"������� "+(i+1);
        Tab[i]->ShowHint = Shape->ShowHint;
        Tab[i]->OnMouseMove = Shape->OnMouseMove;
        //���������� ������� �������
        set_dir("temp");
        edExe->Lines->SaveToFile(TabIndex);
        //��������� �� ���������
        ofstream out(IntToStr(i).c_str(),ios::trunc);
        out.close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::ShapeMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        set_dir("temp");
        edExe->Lines->SaveToFile(TabIndex);
        //��������� �� ���������
        TabIndex = ((TShape*)Sender)->Tag;
        edExe->Lines->Clear();
        edExe->Lines->LoadFromFile(TabIndex);
        edExe->Color = Tab[TabIndex]->Brush->Color;
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::N12Click(TObject *Sender)
{
        //������� �������
        if(TabIndex != 0){
                delete (Tab[TabIndex]);
                Tab[TabIndex]=NULL;
                //��������� �� ������� � ������� �������
                for(;TabIndex>0 && Tab[TabIndex]==NULL;TabIndex--);
                //��������� �� ���������
                edExe->Lines->Clear();
                edExe->Lines->LoadFromFile(TabIndex);
                edExe->Color = Tab[TabIndex]->Brush->Color;
                }
        else{
                MessageBox(NULL,"������ ������� ������ �������",NULL,NULL);
                return;}
}
//---------------------------------------------------------------------------

void __fastcall TfrmServer::FormMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        if(Y>470){
                if(Height < 590) {for(;Height < 610;Height++);return;}
                if(Height > 590) {for(;Height > 530;Height--);return;}
                }
}
//---------------------------------------------------------------------------
void __fastcall TfrmServer::ShapeMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
        if(!fTab){
                iTab=((TShape*)Sender)->Tag;
                Tab[iTab]->Width += 2;
                Tab[iTab]->Height += 2;
                Tab[iTab]->Top --;
                Tab[iTab]->Left--;
                fTab=true;}
}
//---------------------------------------------------------------------------

void __fastcall TfrmServer::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
        //������ �������� �����
        if(fTab && Tab[iTab]!=NULL){
                Tab[iTab]->Width -= 2;
                Tab[iTab]->Height -= 2;
                Tab[iTab]->Top ++;
                Tab[iTab]->Left++;
                fTab=false;}        
}
//---------------------------------------------------------------------------




