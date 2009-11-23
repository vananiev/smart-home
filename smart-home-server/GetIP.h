//---------------------------------------------------------------------------

#ifndef GetIPH
#define GetIPH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ScktComp.hpp>
//---------------------------------------------------------------------------
class TfrmCon : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TEdit *edtPort;
        TEdit *edIP;
        TEdit *edName;
        TLabel *Label2;
        TLabel *Label3;
        TButton *Button1;
        TServerSocket *SerGetIP;
        TLabel *Label4;
        TEdit *edtLogin;
        TLabel *Label5;
        TLabel *Label6;
        TEdit *edtSite;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall SerGetIPClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmCon(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCon *frmCon;
//---------------------------------------------------------------------------
#endif
