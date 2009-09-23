!define PRODUCT_NAME "Template Monster Browser"
!define PRODUCT_VERSION "1.2.0.3"
!define PRODUCT_PUBLISHER "XpycT & ALEXANDER"
!define PRODUCT_WEB_SITE "www.torrents.ru"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\orange-uninstall.ico"
# ����������� ��������� � ��������� ���������� Modern UI
!include "MUI.nsh"

# ��������� ����� ����������, ������� ����� ������������ �� ���� ����� ���������
Name "${PRODUCT_NAME}"

# ��������� ���������� ��� ��������� ����������� ���������� ����
Var STARTMENU_FOLDER

# ����������� ����� ������������� �������� � ��������� ���� ���������
!define MUI_HEADERIMAGE

# ����������� ��������� ������ � ��������
!include "Sections.nsh"

# Installer pages

# ����������� �������� �������� ���������
# ����� ��������, ������� ������������ �� ��������� � �� �������� �������� ��������� � ����� ����� ����
!insertmacro MUI_DEFAULT MUI_WELCOMEFINISHPAGE_BITMAP "splash.bmp"
# ��������, ������� ������������ � �������� �������� � ������� ����� ����� ���� �� ���� ���������,
# ����� ��������� � ��������
!insertmacro MUI_DEFAULT MUI_HEADERIMAGE_BITMAP "head.bmp"
  
# ����� ���� �����������
!insertmacro MUI_PAGE_WELCOME

# ����� ���� ������������� ����������
!insertmacro MUI_PAGE_LICENSE "license.rtf"

#����������� �������������� ��������� ��� ���� ������ ��������������� ���������
!define DESCR_SEC0000 "��������� $(^Name) � ����������� �������, �� �������� ���������� Qt."
!define DESCR_SEC0001 "�������������� ���������� ��� ������� $(^Name) � ����� Windows."
# ����� ���� ������ ��������������� ���������
!insertmacro MUI_PAGE_COMPONENTS
  
# ����������� ���������� ������ ���������, ����������� �� �������� ������ �������� ���������
!define MUI_DIRECTORYPAGE_TEXT_TOP "��������� ��������� $(^Name) � ��������� �����. ����� ���������� ���������� � ������ �����, ������� '�����' � ������� ��. ������� ������ '�����' ��� �����������."

# ����� ���� ������ �������� ���������
!insertmacro MUI_PAGE_DIRECTORY

# ����������� ����� � ������� ��� ���������� ���������� � ��������� ����
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU" 
!define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\$(^Name)" 
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
  
# ����������� ����� ������� ���������� � ������� ����
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "${PRODUCT_NAME}"
# ����� ���� ������ ������� ���������� � ��������� ����
!insertmacro MUI_PAGE_STARTMENU "TMBrowser" $STARTMENU_FOLDER

# ����� ���� ��������� ������ ����������
!insertmacro MUI_PAGE_INSTFILES


# ��������� ������ ������� "���������" �� �������� ��������
# ������ ���� � ��� ����������� ���������
!define MUI_FINISHPAGE_RUN "$INSTDIR\tmbrowser.exe"
# ����� ��� ����������� � ���� ������� � �������
!define MUI_FINISHPAGE_RUN_TEXT "��������� $(^Name)"

# ��������� ������ ������� ������ ����� ReadNe.txt
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\ReadMe.txt"
!define MUI_FINISHPAGE_SHOWREADME_TEXT "�������� �������������� ����������"
!insertmacro MUI_PAGE_FINISH

# ����������� ����� ���������
!insertmacro MUI_LANGUAGE "Russian"

# ����������, ���������� � �������� ����� ���������
VIProductVersion "1.0.0.0" # ������ ��������
VIAddVersionKey /LANG=${LANG_RUSSIAN} ProductName "${PRODUCT_NAME}" # �������� ��������
VIAddVersionKey /LANG=${LANG_RUSSIAN} ProductVersion "${PRODUCT_VERSION}" # ������ ��������
VIAddVersionKey /LANG=${LANG_RUSSIAN} CompanyName "${PRODUCT_PUBLISHER}" # �������� ��������
VIAddVersionKey /LANG=${LANG_RUSSIAN} CompanyWebsite "${PRODUCT_WEB_SITE}" # ����� �����
VIAddVersionKey /LANG=${LANG_RUSSIAN} FileVersion "${PRODUCT_VERSION}" # ������ �����
VIAddVersionKey /LANG=${LANG_RUSSIAN} FileDescription "��������� ��������� �������� �� Template Monster" # �������� �����
VIAddVersionKey /LANG=${LANG_RUSSIAN} LegalCopyright "Copyright � 2009, XpycT & ALEXANDER" # ��������� �����

OutFile TMBrowserSetup.exe # ��� ��������� ����� ������������
CRCCheck on # ��������� �������� ����������� ����� (���������)
XPStyle on # ��������� ����� XP (��������)
BrandingText "${PRODUCT_NAME}" # ����������� ������, ������� ������������ �� ����� ��� ��������
Icon setup.ico # ����������� ������ ��� ����� ���������
#ShowInstDetails show # ����������� ������� ��������� � ���� ��������� ������ ����������
AutoCloseWindow false # ��������� ��������������� �������� ���� ��������� (���������)

# �������� ����� ���������
InstType "������ ���������"
InstType "������ ���������"
InstType "������ ����������"

# �������� ������ ��������� � ��������
Section "!��������� � �������" SEC0000
	# ������ �������� � ������ � �� ������ ���� ���������
	SectionIn 1 2
	# ���������� �������� ���������
    SetOutPath $INSTDIR
	# ��������� ���������� �������������� ������������ ����� ��� ���������
    SetOverwrite on
	
	# ���������� ������ ��� ���������
    File ReadMe.txt	
	File ..\..\..\bin\tmbrowser.exe
    SetOutPath "$INSTDIR\plugins\imageformats"
    File /r "..\..\..\bin\plugins\imageformats\qgif4.dll"
    File /r "..\..\..\bin\plugins\imageformats\qjpeg4.dll"
	 SetOutPath "$INSTDIR\plugins\sqldrivers"
    File /r "..\..\..\bin\plugins\sqldrivers\qsqlite4.dll"
	
	# ����������� ������� ���������� ���������� � ��������� ����
	!insertmacro MUI_STARTMENU_WRITE_BEGIN "TMBrowser"
    
		# ���������� ��������� ������ ���������� � ��������� ����
		CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
		# ���������� ������ �� �������� ��������� ����������
		CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\$(^Name).lnk" "$INSTDIR\tmbrowser.exe"
		CreateShortCut "$DESKTOP\$(^Name).lnk" "$INSTDIR\tmbrowser.exe"
		# ���������� ������ ��� ��������
		CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\��������.lnk" "$INSTDIR\uninst.exe"
		# ���������� ������ �� ���� ReadMe.txt
		CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\�������������� ����������.lnk" "$INSTDIR\ReadMe.txt"		
  
	!insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\tmbrowser.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "�������� ��������� $(^Name) ���� ������� ���������."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "�� ������� � ���, ��� ������� ������� $(^Name) � ��� ���������� ���������?" IDYES +2
  Abort
FunctionEnd
# �������������� ������ ��������� ��� ����������� ������� ���������
Section "�������������� ����������" SEC0001
	# ������ �������� ������ � ������ ��� ���������
	SectionIn 1 3
	# ���������� �������� ���������
    SetOutPath $INSTDIR
	# ��������� ���������� �������������� ������������ ����� ��� ���������
    SetOverwrite on
	
	# ���������� ������ ��� ���������
	File ..\..\..\bin\mingwm10.dll
	File ..\..\..\bin\QtCore4.dll
	File ..\..\..\bin\QtGui4.dll
	File ..\..\..\bin\QtSql4.dll
	File ..\..\..\bin\QtNetwork4.dll	
	
SectionEnd

Section Uninstall
	Delete "$INSTDIR\plugins\imageformats\*.*"
	Delete "$INSTDIR\plugins\sqldrivers\*.*"
	Delete "$INSTDIR\plugins\*.*"
	Delete "$INSTDIR\images\*.*"
	Delete "$INSTDIR\*.*"
	Delete "$SMPROGRAMS\Template Monster Browser\*.*"
	Delete "$DESKTOP\${PRODUCT_NAME}.lnk"
	RMDir "$INSTDIR\plugins\imageformats"
	RMDir "$INSTDIR\plugins\sqldrivers"
	RMDir "$INSTDIR\plugins"
	RMDir "$INSTDIR\images"
	RMDir "$INSTDIR"
	RMDir "$SMPROGRAMS\${PRODUCT_NAME}"
	DeleteRegKey /ifempty HKCU "Software\${PRODUCT_NAME}"
	DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
	
	SetAutoClose true 
SectionEnd
# �������, ����������� ��� ������������� ���������
Function .onInit
	# ������������� ���������� ��������
    InitPluginsDir
	# �������� �� ��������� ��� �������� ���������
	StrCpy $INSTDIR "$PROGRAMFILES\${PRODUCT_NAME}"	
FunctionEnd

# ������� ������ �������������� ���������� � ������� � ���� ������ ��������������� ���������
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
	!insertmacro MUI_DESCRIPTION_TEXT ${SEC0000} "${DESCR_SEC0000}"
	!insertmacro MUI_DESCRIPTION_TEXT ${SEC0001} "${DESCR_SEC0001}"
!insertmacro MUI_FUNCTION_DESCRIPTION_END

