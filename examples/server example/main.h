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
        void __fastcall ServerClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ServerRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall btnPortOkClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall ServerClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall btnDisconnectClick(TObject *Sender);
        void __fastcall cmbClientsDropDown(TObject *Sender);
        void __fastcall FormClick(TObject *Sender);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Memo1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmServer(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmServer *frmServer;
//---------------------------------------------------------------------------
#endif
