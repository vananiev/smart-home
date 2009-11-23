//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("main.cpp", frmServer);
USEFORM("GetIP.cpp", frmCon);
USEFORM("Login.cpp", frmLogin);
USEFORM("Msg.cpp", frmMsg);
USEFORM("Config.cpp", frmConfig);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TfrmServer), &frmServer);
                 Application->CreateForm(__classid(TfrmMsg), &frmMsg);
                 Application->CreateForm(__classid(TfrmConfig), &frmConfig);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
