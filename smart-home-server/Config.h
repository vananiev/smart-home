//---------------------------------------------------------------------------

#ifndef ConfigH
#define ConfigH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmConfig : public TForm
{
__published:	// IDE-managed Components
        TPageControl *Pages;
        TTabSheet *TabSheet1;
        TLabel *Label1;
        TEdit *edtInc;
        TEdit *edtLib;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *edtPath;
        TLabel *Label5;
        TLabel *Label6;
        TPanel *Panel1;
        TLabel *Label7;
        TMemo *mComp;
        TLabel *Example;
        void __fastcall PagesChange(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmConfig(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmConfig *frmConfig;
//---------------------------------------------------------------------------
#endif
