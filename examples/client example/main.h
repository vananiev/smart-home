//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ScktComp.hpp>
//---------------------------------------------------------------------------
class TfrmClient : public TForm
{
__published:	// IDE-managed Components
        TClientSocket *Client;
        TEdit *edtPort;
        TMemo *Memo1;
        TMemo *Memo2;
        TLabel *Label1;
        TEdit *edtServer;
        TLabel *Label2;
        TButton *btnDisconnect;
        TButton *btnConnect;
        void __fastcall ClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall ClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall btnDisconnectClick(TObject *Sender);
        void __fastcall btnConnectClick(TObject *Sender);
        void __fastcall ClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall FormClick(TObject *Sender);
        void __fastcall Memo1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmClient(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmClient *frmClient;
//---------------------------------------------------------------------------
#endif
