.code

;�ж�ѡ����ѡ��״̬
;����TRUE ѡ��
IsCheckedBox proc hMain:DWORD,IDCheckButton:DWORD
        invoke IsDlgButtonChecked,hMain,IDCheckButton
        ret
IsCheckedBox endp