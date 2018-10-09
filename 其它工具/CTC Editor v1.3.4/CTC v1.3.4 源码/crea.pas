unit crea;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls,ShellApi;

type
  TCrea_Form = class(TForm)
    Button1: TButton;
    Button2: TButton;
    SaveDialog1: TSaveDialog;
    SaveDialog2: TSaveDialog;
    Button3: TButton;
    Memo1: TMemo;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure creatfile(filename : string;htmlfile:Boolean;copyto:Boolean;ZhuoSe:Boolean);
    procedure Button3Click(Sender: TObject);

  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Crea_Form: TCrea_Form;

implementation

{$R *.dfm}
 uses
 main;



 ////////////////////////////////////////////////////
 procedure TCrea_Form.creatfile(filename : string;htmlfile:boolean;copyto:boolean;ZhuoSe:Boolean);
var i,lastline:integer;
    writefile:textfile;
begin
     assignfile(writefile,filename);
     rewrite(writefile);
     if htmlfile then
     begin
        //�����ļ�����
        writeln(writefile,'<html><head><title>'+Main_form.edit1.text+'</title></head>');
        //д�����߻�����Ϣ
        writeln(writefile,'<pre><font size=2>');
     end;

     //д�����߻�����Ϣ
     if   Main_form.edit1.text<>'' then
     writeln(writefile,Main_form.label1.caption+': '+Main_form.edit1.text);

     if   Main_form.edit2.text<>'' then
     writeln(writefile,Main_form.label2.caption+': '+Main_form.edit2.text);

     if   Main_form.edit3.text<>'' then
     writeln(writefile,Main_form.label3.caption+': '+Main_form.edit3.text);

     if   Main_form.edit4.text<>'' then
     writeln(writefile,Main_form.label4.caption+': '+Main_form.edit4.text);

     if   Main_form.edit5.text<>'' then
     writeln(writefile,Main_form.label5.caption+': '+Main_form.edit5.text);

     if   Main_form.edit6.text<>'' then
     writeln(writefile,Main_form.label6.caption+': '+Main_form.edit6.text);

     if   Main_form.edit7.text<>'' then
     writeln(writefile,Main_form.label7.caption+': '+Main_form.edit7.text);

     if   Main_form.edit8.text<>'' then
     writeln(writefile,Main_form.label8.caption+': '+Main_form.edit8.text);

     if   Main_form.edit9.text<>'' then
     writeln(writefile,Main_form.label9.caption+': '+Main_form.edit9.text);

     if   Main_form.edit10.text<>'' then
     writeln(writefile,Main_form.label10.caption+': '+Main_form.edit10.text);

     if   Main_form.edit11.text<>'' then
     writeln(writefile,Main_form.label11.caption+': '+Main_form.edit11.text);

     if   Main_form.edit12.text<>'' then
     writeln(writefile,Main_form.label12.caption+': '+Main_form.edit12.text);

     if   Main_form.edit13.text<>'' then
     writeln(writefile,Main_form.label13.caption+': '+Main_form.edit13.text);
     //������
     if   Main_form.edit14.text<>'' then
     writeln(writefile,Main_form.label14.caption+': '+Main_form.edit14.text);

     //��������
     if   Main_form.edit200.text<>'' then
       writeln(writefile,Main_form.label200.caption+': '+Main_form.edit200.text);
     if htmlfile then
        writeln(writefile,'<hr color=#999999 size=1 noshade><br>')
     else
         writeln(writefile,'--------------------------------------------------------------------------------');
     //�ƽ�����

     lastline:=Main_Form.Memo1.Lines.Count;
     if   lastline>0 then
     begin
     writeln(writefile,Main_form.GroupBox4.caption);
     for i:=0 to lastline do
        begin
        writeln(writefile,'  '+Main_Form.Memo1.lines[i]);
        end;
     if htmlfile then
        writeln(writefile,'<hr color=#999999 size=1 noshade><br>')
     else
        writeln(writefile,'--------------------------------------------------------------------------------');
     end;


     //�ܽ�

     lastline:=Main_Form.Memo2.Lines.Count;
     if   lastline>0 then
     begin
     writeln(writefile,Main_form.GroupBox5.caption);
     for i:=0 to lastline do
        begin
        writeln(writefile,'  '+Main_Form.Memo2.lines[i]);
        end;
     if htmlfile then
        writeln(writefile,'<hr color=#999999 size=1 noshade><br>')
     else
        writeln(writefile,'--------------------------------------------------------------------------------');
     end;

      //��Ȩ����
     if   Main_form.edit100.text<>'' then
     writeln(writefile,Main_form.label100.caption+': '+Main_form.edit100.text);

     ShortDateFormat:='yyyy��mm��dd��';
      //htmlfile:=true ��ʾ��Ҫ����html�ļ�
     if htmlfile then
        writeln(writefile,'<div align="right">');
     writeln(writefile,#13+#10+'                                                       '+DateTimetostr((now())));

     if htmlfile then
         writeln(writefile,'</div></html>');
     closefile(writefile);
     Crea_form.Close ;

     if not copyto then
     begin
     if htmlfile  then
        application.MessageBox ('�ɹ�����HTM�ļ�','���',0)
     else if  ZhuoSe  then
          begin
           application.MessageBox ('������ɫ,��������Ժ�','ת��',0);

          end
      else
        application.MessageBox ('�ɹ�����TXT�ļ�','���',0);
     end;
end;



 ///////////////////////////////////////////////
procedure TCrea_Form.Button1Click(Sender: TObject);
begin
   //����TEXT�ı��ļ�
   savedialog1.Title :='����txt�ļ�';
   savedialog1.InitialDir :=ExtractFilePath(Application.ExeName)+'txt';
   savedialog1.FileName:= Main_form.edit1.text+'.txt';
   If SaveDialog1.Execute then //�򿪱���Ի���
      creatfile(savedialog1.FileName,false,false,false );

end;

procedure TCrea_Form.Button2Click(Sender: TObject);
var
msg:integer;
xTiNt:String;
begin
    //�ж��Ƿ���ɫ
     msg:=MessageBox(0,'������ɫ��?','Info',MB_YESNO+MB_ICONQUESTION		);
    if msg=6 then
       begin


        //������ɫ����ҳ�ļ�

     savedialog1.Title :='����htm�ļ�����ɫ';
     savedialog1.InitialDir :=ExtractFilePath(Application.ExeName)+'htm';

     savedialog1.FileName:= Main_form.edit1.text+'.asm';

     If SaveDialog1.Execute then //�򿪱���Ի���
      begin
      creatfile(savedialog1.FileName,false,false,True );

    xTiNt:=ExtractFilePath(Application.ExeName)+'xTiNt\xTiNt.exe';
    //showMessage(xTiNt+' /:api '+savedialog1.FileName);
    //ShellExecuteEx(xTiNt+' /:api '+  savedialog1.FileName);
    ShellExecute( Application.handle,'open',PChar(xTiNt),PChar(' /:api '+savedialog1.FileName),nil,SW_HIDE );
    //  ShellExecute(handle,'open','c:\myapp\myapp.exe','-s','',SW_SHOWNORMAL);
    sleep(1000);
    deletefile(savedialog1.FileName);
      end;

       end
    else
      begin
   //������ͨ��HTML��ҳ�ļ�
   savedialog2.Title :='����htm�ļ�';
   savedialog2.InitialDir :=ExtractFilePath(Application.ExeName)+'htm';

   SaveDialog2.FileName:= Main_form.edit1.text+'.htm';
   If SaveDialog2.Execute then //�򿪱���Ի���
      creatfile(savedialog2.FileName,true,false,false );
      end;
end;

procedure TCrea_Form.Button3Click(Sender: TObject);
var
filetemp:string;
begin
   //���Ƶ������
   filetemp:=ExtractFilePath(Application.ExeName)+'tem\'+'copyto.tem';
   creatfile(filetemp,false,True,false );
   memo1.Lines.LoadFromFile(filetemp);
   memo1.SelectAll;
   memo1.CopyToClipboard;

end;

end.
