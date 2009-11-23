//---------------------------------------------------------------------------

#ifndef MsgH
#define MsgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmMsg : public TForm
{
__published:	// IDE-managed Components
        TLabel *lblMsg;
        TButton *btnOK;
        void __fastcall btnOKClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmMsg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMsg *frmMsg;
//---------------------------------------------------------------------------
#endif
