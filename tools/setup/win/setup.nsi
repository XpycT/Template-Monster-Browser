!define PRODUCT_NAME "Template Monster Browser"
!define PRODUCT_VERSION "1.2.0.3"
!define PRODUCT_PUBLISHER "XpycT & ALEXANDER"
!define PRODUCT_WEB_SITE "www.torrents.ru"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\orange-uninstall.ico"
# Подключение заголовка с макросами интерфейса Modern UI
!include "MUI.nsh"

# Установка имени разработки, которое будет отображаться во всех окнах установки
Name "${PRODUCT_NAME}"

# Обявление переменной для получения подкаталога стартового меню
Var STARTMENU_FOLDER

# Определение флага использования картинки в заголовке окон установки
!define MUI_HEADERIMAGE

# Подключение заголовка работы с секциями
!include "Sections.nsh"

# Installer pages

# Определение основных картинок установки
# Сплэш картника, которая отображается на начальной и на конечной странице установки в левой части окна
!insertmacro MUI_DEFAULT MUI_WELCOMEFINISHPAGE_BITMAP "splash.bmp"
# Картинка, которая отображается в качестве логотипа в верхней левой части окна на всех страницах,
# кроме начальной и конечной
!insertmacro MUI_DEFAULT MUI_HEADERIMAGE_BITMAP "head.bmp"
  
# Вывод окна приветствия
!insertmacro MUI_PAGE_WELCOME

# Вывод окна лицензионного соглашения
!insertmacro MUI_PAGE_LICENSE "license.rtf"

#Определение дополнительных подсказок для окна выбора устанавливаемых компонент
!define DESCR_SEC0000 "Программа $(^Name) и необходимые плагины, не содержит библиотеки Qt."
!define DESCR_SEC0001 "Дополнительные библиотеки для запуска $(^Name) в среде Windows."
# Вывод окна выбора устанавливаемых компонент
!insertmacro MUI_PAGE_COMPONENTS
  
# Определение содержания текста пояснения, выдаваемого на странице выбора каталога установки
!define MUI_DIRECTORYPAGE_TEXT_TOP "Программа установит $(^Name) в указанную папку. Чтобы установить приложение в другую папку, нажмите 'Обзор' и укажите ее. Нажмите кнопку 'Далее' для продолжения."

# Вывод окна выбора каталога установки
!insertmacro MUI_PAGE_DIRECTORY

# Определение путей в реестре для добавления разработки в стартовое меню
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU" 
!define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\$(^Name)" 
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
  
# Определение имени раздела разработки в сатовом меню
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "${PRODUCT_NAME}"
# Вывод окна выбора раздела разработки в стартовом меню
!insertmacro MUI_PAGE_STARTMENU "TMBrowser" $STARTMENU_FOLDER

# Вывод окна установки файлов разработки
!insertmacro MUI_PAGE_INSTFILES


# Установка данных галочки "Запустить" на финишной странице
# Полный путь и имя запускаемой обработки
!define MUI_FINISHPAGE_RUN "$INSTDIR\tmbrowser.exe"
# Текст для отображения в виде подписи к галочке
!define MUI_FINISHPAGE_RUN_TEXT "Запустить $(^Name)"

# Установка данных галочки показа файла ReadNe.txt
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\ReadMe.txt"
!define MUI_FINISHPAGE_SHOWREADME_TEXT "Показать дополнительную информацию"
!insertmacro MUI_PAGE_FINISH

# Определение языка установки
!insertmacro MUI_LANGUAGE "Russian"

# Информация, помещаемая в свойства файла установки
VIProductVersion "1.0.0.0" # Версия продукта
VIAddVersionKey /LANG=${LANG_RUSSIAN} ProductName "${PRODUCT_NAME}" # Название продукта
VIAddVersionKey /LANG=${LANG_RUSSIAN} ProductVersion "${PRODUCT_VERSION}" # Версия продукта
VIAddVersionKey /LANG=${LANG_RUSSIAN} CompanyName "${PRODUCT_PUBLISHER}" # Название компании
VIAddVersionKey /LANG=${LANG_RUSSIAN} CompanyWebsite "${PRODUCT_WEB_SITE}" # Адрес сайта
VIAddVersionKey /LANG=${LANG_RUSSIAN} FileVersion "${PRODUCT_VERSION}" # Версия файла
VIAddVersionKey /LANG=${LANG_RUSSIAN} FileDescription "Программа просмотра шаблонов от Template Monster" # Описание файла
VIAddVersionKey /LANG=${LANG_RUSSIAN} LegalCopyright "Copyright © 2009, XpycT & ALEXANDER" # Авторские права

OutFile TMBrowserSetup.exe # Имя конечного файла инсталлятора
CRCCheck on # Включение проверси контрольной суммы (включение)
XPStyle on # Включение стиля XP (включено)
BrandingText "${PRODUCT_NAME}" # Определение текста, который отображается на линии над кнопками
Icon setup.ico # Определение иконки для файла установки
#ShowInstDetails show # Отображение деталей установки в окне установки файлов разработки
AutoCloseWindow false # Включение автоматического закрытия окна установки (выключено)

# Описание видов установки
InstType "Полная установка"
InstType "Только программа"
InstType "Только библиотеки"

# Основная секция программы и плагинов
Section "!Программа и плагины" SEC0000
	# Секция включена в первый и во второй виды установки
	SectionIn 1 2
	# Назначение каталога установки
    SetOutPath $INSTDIR
	# Включение разрешения перезаписывать существующие файлы при установке
    SetOverwrite on
	
	# Добавление файлов для установки
    File ReadMe.txt	
	File ..\..\..\bin\tmbrowser.exe
    SetOutPath "$INSTDIR\plugins\imageformats"
    File /r "..\..\..\bin\plugins\imageformats\qgif4.dll"
    File /r "..\..\..\bin\plugins\imageformats\qjpeg4.dll"
	 SetOutPath "$INSTDIR\plugins\sqldrivers"
    File /r "..\..\..\bin\plugins\sqldrivers\qsqlite4.dll"
	
	# Определение функции добавления информации в стартовое меню
	!insertmacro MUI_STARTMENU_WRITE_BEGIN "TMBrowser"
    
		# Добавление основного пункта разработки в стартовое меню
		CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
		# Добавление ярлыка на основную обработку разработки
		CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\$(^Name).lnk" "$INSTDIR\tmbrowser.exe"
		CreateShortCut "$DESKTOP\$(^Name).lnk" "$INSTDIR\tmbrowser.exe"
		# Добавление ярлыка для удаления
		CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Удаление.lnk" "$INSTDIR\uninst.exe"
		# Добавление ярлыка на файл ReadMe.txt
		CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Дополнительная информация.lnk" "$INSTDIR\ReadMe.txt"		
  
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
  MessageBox MB_ICONINFORMATION|MB_OK "Удаление программы $(^Name) было успешно завершено."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Вы уверены в том, что желаете удалить $(^Name) и все компоненты программы?" IDYES +2
  Abort
FunctionEnd
# Дополнительная секция библиотек для нормального запуска программы
Section "Дополнительные библиотеки" SEC0001
	# Секция включена только в первый вид установки
	SectionIn 1 3
	# Назначение каталога установки
    SetOutPath $INSTDIR
	# Включение разрешения перезаписывать существующие файлы при установке
    SetOverwrite on
	
	# Добавление файлов для установки
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
# Функция, выполняемая при инициализации установки
Function .onInit
	# Инициализация временного каталога
    InitPluginsDir
	# Значение по умолчанию для каталога установки
	StrCpy $INSTDIR "$PROGRAMFILES\${PRODUCT_NAME}"	
FunctionEnd

# Функции вывода дополнительной информации о секциях в окне выбора устанавливаемых компонент
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
	!insertmacro MUI_DESCRIPTION_TEXT ${SEC0000} "${DESCR_SEC0000}"
	!insertmacro MUI_DESCRIPTION_TEXT ${SEC0001} "${DESCR_SEC0001}"
!insertmacro MUI_FUNCTION_DESCRIPTION_END

