; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSGMS_MFCDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SGMS_MFC.h"

ClassCount=7
Class1=CSGMS_MFCApp
Class2=CSGMS_MFCDlg

ResourceCount=7
Resource1=IDR_MAINFRAME
Resource2=IDD_DEL_DIALOG
Class3=ADD
Resource3=IDD_HANGE_DIALOG
Class4=Del
Resource4=IDD_ADD_DIALOG
Class5=Change
Resource5=IDD_SEARCH_DIALOG
Class6=Search
Resource6=IDD_SGMS_MFC_DIALOG
Class7=SORT
Resource7=IDD_SORT_DIALOG

[CLS:CSGMS_MFCApp]
Type=0
HeaderFile=SGMS_MFC.h
ImplementationFile=SGMS_MFC.cpp
Filter=N

[CLS:CSGMS_MFCDlg]
Type=0
HeaderFile=SGMS_MFCDlg.h
ImplementationFile=SGMS_MFCDlg.cpp
Filter=D
LastObject=CSGMS_MFCDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_SGMS_MFC_DIALOG]
Type=1
Class=CSGMS_MFCDlg
ControlCount=15
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,button,1342177287
Control3=IDC_BUTTON_Read,button,1342242816
Control4=IDC_BUTTON_Write,button,1342242816
Control5=IDC_BUTTON_Add,button,1342242816
Control6=IDC_BUTTON_Del,button,1342242816
Control7=IDC_BUTTON_Change,button,1342242816
Control8=IDC_BUTTON_Analyse,button,1342242816
Control9=IDC_STATIC,button,1342177287
Control10=IDC_LIST,listbox,1352728833
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287
Control13=IDC_BUTTON_Sort,button,1342242816
Control14=IDC_BUTTON_Search,button,1342242816
Control15=IDC_STATIC,static,1342308352

[DLG:IDD_ADD_DIALOG]
Type=1
Class=ADD
ControlCount=13
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,button,1342177287
Control3=IDC_EDIT_Num,edit,1350631552
Control4=IDC_EDIT_Name,edit,1350631552
Control5=IDC_EDIT_Math,edit,1350631552
Control6=IDC_EDIT_Physics,edit,1350631552
Control7=IDC_EDIT_English,edit,1350631552
Control8=IDC_STATIC,static,1342308865
Control9=IDC_STATIC,static,1342308865
Control10=IDC_STATIC,static,1342308865
Control11=IDC_STATIC,static,1342308865
Control12=IDC_STATIC,static,1342308865
Control13=IDC_BUTTON1,button,1342242816

[CLS:ADD]
Type=0
HeaderFile=ADD.h
ImplementationFile=ADD.cpp
BaseClass=CDialog
Filter=D
LastObject=ADD
VirtualFilter=dWC

[DLG:IDD_DEL_DIALOG]
Type=1
Class=Del
ControlCount=17
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,button,1342177287
Control3=IDC_EDIT_Num,edit,1350633600
Control4=IDC_EDIT_Name,edit,1350633600
Control5=IDC_EDIT_Math,edit,1350633600
Control6=IDC_EDIT_Physics,edit,1350633600
Control7=IDC_EDIT_English,edit,1350633600
Control8=IDC_STATIC,static,1342308865
Control9=IDC_STATIC,static,1342308865
Control10=IDC_STATIC,static,1342308865
Control11=IDC_STATIC,static,1342308865
Control12=IDC_STATIC,static,1342308865
Control13=IDC_BUTTON1,button,1342242816
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,static,1342308865
Control16=IDC_EDIT_IN,edit,1350631552
Control17=IDC_BUTTON3,button,1342242816

[CLS:Del]
Type=0
HeaderFile=Del.h
ImplementationFile=Del.cpp
BaseClass=CDialog
Filter=D
LastObject=Del
VirtualFilter=dWC

[DLG:IDD_HANGE_DIALOG]
Type=1
Class=Change
ControlCount=17
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,button,1342177287
Control3=IDC_EDIT_Num,edit,1350631552
Control4=IDC_EDIT_Name,edit,1350631552
Control5=IDC_EDIT_Math,edit,1350631552
Control6=IDC_EDIT_Physics,edit,1350631552
Control7=IDC_EDIT_English,edit,1350631552
Control8=IDC_STATIC,static,1342308865
Control9=IDC_STATIC,static,1342308865
Control10=IDC_STATIC,static,1342308865
Control11=IDC_STATIC,static,1342308865
Control12=IDC_STATIC,static,1342308865
Control13=IDC_BUTTON1,button,1342242816
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,static,1342308865
Control16=IDC_EDIT_IN,edit,1350631552
Control17=IDC_BUTTON3,button,1342242816

[CLS:Change]
Type=0
HeaderFile=hange.h
ImplementationFile=hange.cpp
BaseClass=CDialog
Filter=D
LastObject=Change
VirtualFilter=dWC

[DLG:IDD_SEARCH_DIALOG]
Type=1
Class=Search
ControlCount=16
Control1=IDCANCEL,button,1342242816
Control2=IDC_LIST,listbox,1352728833
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342308865
Control7=IDC_EDIT_IN,edit,1350631552
Control8=IDC_BUTTON3,button,1342242816
Control9=IDC_COMBO_MENU,combobox,1344340226
Control10=IDC_STATIC,button,1342177287
Control11=IDC_COMBO_DATA,combobox,1344340226
Control12=IDC_EDIT_MIN,edit,1350631552
Control13=IDC_EDIT_MAX,edit,1350631552
Control14=IDC_STATIC,static,1342308864
Control15=IDC_STATIC,static,1342308864
Control16=IDC_BUTTON_Yes,button,1342242816

[CLS:Search]
Type=0
HeaderFile=Search.h
ImplementationFile=Search.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BUTTON_Yes
VirtualFilter=dWC

[DLG:IDD_SORT_DIALOG]
Type=1
Class=SORT
ControlCount=6
Control1=IDCANCEL,button,1342242816
Control2=IDC_X,button,1342242816
Control3=IDC_NUM,button,1342242816
Control4=IDC_MATH,button,1342242816
Control5=IDC_PHYSICS,button,1342242816
Control6=IDC_ENGLISH,button,1342242816

[CLS:SORT]
Type=0
HeaderFile=SORT.h
ImplementationFile=SORT.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

