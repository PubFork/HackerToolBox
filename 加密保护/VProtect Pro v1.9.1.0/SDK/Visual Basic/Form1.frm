VERSION 5.00
Begin VB.Form Form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "VProtect Sdk Example [Visual Basic]"
   ClientHeight    =   2145
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   5010
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2145
   ScaleWidth      =   5010
   StartUpPosition =   2  '��Ļ����
   Begin VB.CommandButton Command3 
      Caption         =   "ע�������ʹ����ʾ"
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Top             =   1680
      Width           =   4695
   End
   Begin VB.CommandButton Command2 
      Caption         =   "������루������ܣ�"
      Height          =   375
      Left            =   840
      TabIndex        =   3
      Top             =   1200
      Width           =   3015
   End
   Begin VB.CommandButton Command1 
      Caption         =   "������루��������ܣ�"
      Default         =   -1  'True
      Height          =   375
      Left            =   840
      TabIndex        =   2
      Top             =   720
      Width           =   3060
   End
   Begin VB.TextBox Text1 
      Height          =   315
      Left            =   1920
      TabIndex        =   1
      Top             =   195
      Width           =   2775
   End
   Begin VB.Label Label1 
      Caption         =   "��������:"
      Height          =   255
      Left            =   360
      TabIndex        =   0
      Top             =   240
      Width           =   1050
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
  MsgBox "�����������ʾ��", vbInformation + vbOKOnly, "ע��"
  '�����������ʾ
  'ע������Ҫ�ɶԳ���
  Call VarPtr("VP_Virtualize_Begin")
  '��ȷ������ 47
  If Val(Text1.Text) Mod 17 = 13 Then
   MsgBox "������ȷ", vbInformation + vbOKOnly, "��ʾ"
  Else
   MsgBox "�������", vbCritical + vbOKOnly, "����"
   Text1.SetFocus
  End If
  
  Call VarPtr("VP_Virtualize_End")
End Sub

Private Sub Command2_Click()
  MsgBox "ʹ���������������ʾ��", vbInformation + vbOKOnly, "ע��"
  'ʹ���������������ʾ
  'ע������Ҫ�ɶԳ���
  Call VarPtr("VP_Mutation_Begin")
  
  If Val(Text1.Text) Mod 17 = 13 Then
   MsgBox "������ȷ", vbInformation + vbOKOnly, "��ʾ"
  Else
   MsgBox "�������", vbCritical + vbOKOnly, "����"
   Text1.SetFocus
  End If
  
  Call VarPtr("VP_Mutation_End")
End Sub

Private Sub Command3_Click()
  MsgBox "�������ֻ����һ����ȷ��Ȩ�ļ�����²Ż�ִ�С�", vbInformation + vbOKOnly, "ע��"
  
  'ʹ��ע����������ʾ
  '**ע�⣺ʹ��ע���������ڼ���ʱѡ��ʹ����Ȩϵͳ��
  '�������´�����Ч
  'ע������Ҫ�ɶԳ���
  Call VarPtr("VP_Regdecode_Begin")
  
  If Val(Text1.Text) Mod 17 = 13 Then
   MsgBox "������ȷ", vbInformation + vbOKOnly, "��ʾ"
  Else
   MsgBox "�������", vbCritical + vbOKOnly, "����"
   Text1.SetFocus
  End If
  
  Call VarPtr("VP_Regdecode_End")
End Sub
