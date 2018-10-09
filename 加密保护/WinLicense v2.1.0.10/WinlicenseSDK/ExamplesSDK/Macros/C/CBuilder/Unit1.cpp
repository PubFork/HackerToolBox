//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "..\..\..\..\Include\C\WinlicenseSDK.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
     int        value = 0;

     // the following code, inside the ENCODE macro, will go encrypted
     // all the time and decrypted/encrypted again when it's executed
       
     ENCODE_START

     for (int i = 0; i < 100; i++)
     {
         value += value * i;
     }

     ENCODE_END

     MessageBox(NULL, "The Encode Macro #1 has successfully been executed", "Encode Macro", MB_OK + MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
    int        value = 0;

     // the following code, inside the ENCODE macro, will go encrypted
     // all the time and decrypted/encrypted again when it's executed

     ENCODE_START

     for (int i = 0; i < 100; i++)
     {
         value += value + i * 2;
     }

     ENCODE_END

     MessageBox(NULL, "The Encode Macro #2 has successfully been executed", "Encode Macro", MB_OK + MB_ICONINFORMATION);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
     int        value = 0;

     // the following code, inside the ENCODE macro, will go encrypted
     // all the time and decrypted/encrypted again when it's executed

     ENCODE_START

     for (int i = 0; i < 100; i++)
     {
         value += value * i * 2;
     }

     ENCODE_END

     MessageBox(NULL, "The Encode Macro #3 has successfully been executed", "Encode Macro", MB_OK + MB_ICONINFORMATION);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
    int        value = 0;

     // the following code, inside the CLEAR macro, will go encrypted
     // all the time and decrypted/deleted when it's executed

     CLEAR_START

     for (int i = 0; i < 100; i++)
     {
         value += value * i >> 2;
     }

     CLEAR_END

     MessageBox(NULL, "The Clear Macro has successfully been executed", "Clear Macro", MB_OK + MB_ICONINFORMATION);

     Label1->Visible = true;
     Label2->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
    int        value = 0;

     // the following code, inside the CODEREPLACE macro, will be executed in
     // secured place outside the application

     CODEREPLACE_START

     for (int i = 0; i < 100; i++)
     {
         value += value * i * 2;
     }

     MessageBox(NULL, "The CodeReplace Macro #1 has successfully been executed", "CodeReplace Macro", MB_OK + MB_ICONINFORMATION);

     CODEREPLACE_END
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button6Click(TObject *Sender)
{
   int        value = 0;

     // the following code, inside the CODEREPLACE macro, will be executed in
     // secured place outside the application

     CODEREPLACE_START

     for (int i = 0; i < 100; i++)
     {
         value += value * i;
     }

     MessageBox(NULL, "The CodeReplace Macro #2 has successfully been executed", "CodeReplace Macro", MB_OK + MB_ICONINFORMATION);

     CODEREPLACE_END
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button7Click(TObject *Sender)
{
   int        value = 0;

     // the following code, inside the CODEREPLACE macro, will be executed in
     // secured place outside the application

     CODEREPLACE_START

     for (int i = 0; i < 100; i++)
     {
         value += value * i * 2;
     }

     MessageBox(NULL, "The CodeReplace Macro #3 has successfully been executed", "CodeReplace Macro", MB_OK + MB_ICONINFORMATION);

     CODEREPLACE_END
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button8Click(TObject *Sender)
{

   int        value = 0, RegCode = 0;

     // the following code, inside the Registered macro, will be encrypted and
     // decrypted only in case that a valid license is present

     REGISTERED_START

     for (int i = 0; i < 100; i++)
     {
         value += value * i * 2;
     }

     MessageBox(NULL, "This application is registered!", "Registered Macro", MB_OK + MB_ICONINFORMATION);
     RegCode = 1234567;

     REGISTERED_END

     if (RegCode != 1234567)
        MessageBox(NULL, "This application is not registered!", "Registered Macro", MB_OK + MB_ICONWARNING);


}
//---------------------------------------------------------------------------

