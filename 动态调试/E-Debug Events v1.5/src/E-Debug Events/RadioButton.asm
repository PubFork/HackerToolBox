;RadioButton

.code

;���õ�ѡ���ѡ��״̬
;hMain �����ھ��
;nIDDlgItem �ؼ���ʶ��
;IsChecked ѡ��״̬
CheckRadio proc hMain:DWORD,nIDDlgItem:DWORD,IsChecked:DWORD
        invoke CheckDlgButton,hMain,nIDDlgItem,IsChecked
        ret
CheckRadio endp

;�жϵ�ѡ���ѡ��״̬
;����TRUE ѡ��
IsCheckedRadio proc hMain:DWORD,IDCheckButton:DWORD
        invoke IsDlgButtonChecked,hMain,IDCheckButton
        ret
IsCheckedRadio endp