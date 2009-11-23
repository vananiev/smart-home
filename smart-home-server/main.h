//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ScktComp.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <AppEvnts.hpp>
#include <Menus.hpp>
#include "trayicon.h"
#include <Buttons.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TfrmServer : public TForm
{
__published:	// IDE-managed Components
        TServerSocket *Server;
        TEdit *edtPort;
        TLabel *Label1;
        TMemo *Memo1;
        TMemo *Memo2;
        TButton *btnPortOk;
        TButton *btnDisconnect;
        TComboBox *cmbClients;
        TLabel *Label2;
        TTimer *Timer;
        TButton *btnExecute;
        TClientSocket *Client;
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TMenuItem *N4;
        TTrayIcon *Tray;
        TMemo *memIP;
        TLabel *Label4;
        TLabel *lblIP;
        TCheckBox *EnableIP;
        TMenuItem *N5;
        TMenuItem *N6;
        TMenuItem *Dos1;
        TMenuItem *ANSIF41;
        TMenuItem *N7;
        TMenuItem *N8;
        TMenuItem *N9;
        TMenuItem *N10;
        TLabel *Label5;
        TShape *Shape;
        TMenuItem *N11;
        TMenuItem *N12;
        TRichEdit *edExe;
        void __fastcall ServerClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ServerRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall btnPortOkClick(TObject *Sender);
        void __fastcall ServerClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall btnDisconnectClick(TObject *Sender);
        void __fastcall cmbClientsDropDown(TObject *Sender);
        void __fastcall Memo1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall TimerTimer(TObject *Sender);
        void __fastcall btnExecuteClick(TObject *Sender);
        void __fastcall ClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall ClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientConnecting(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall N3Click(TObject *Sender);
        void __fastcall N4Click(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall ServerAccept(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall EnableIPClick(TObject *Sender);
        void __fastcall memIPExit(TObject *Sender);
        void __fastcall N6Click(TObject *Sender);
        void __fastcall Dos1Click(TObject *Sender);
        void __fastcall ANSIF41Click(TObject *Sender);
        void __fastcall N7Click(TObject *Sender);
        void __fastcall N8Click(TObject *Sender);
        void __fastcall N9Click(TObject *Sender);
        void __fastcall N10Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Memo2MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall N11Click(TObject *Sender);
        void __fastcall ShapeMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall N12Click(TObject *Sender);
        void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall ShapeMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
	void __fastcall edExeKeyPress(TObject *Sender, char &Key);
	void __fastcall edExeKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
private:
        int __fastcall GetCount();	// User declarations
public:		// User declarations
        __fastcall TfrmServer(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmServer *frmServer; 
//---------------------------------------------------------------------------
#endif
