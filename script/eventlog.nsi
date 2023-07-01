# Copyright 2023 Ingemar Hedvall
# SPDX-License-Identifier: MIT 

!include MUI2.nsh
!include x64.nsh
!include FileFunc.nsh
 
Name "Event Log Applications 1.0"
OutFile "..\cmake-build-release\eventlog_setup.exe"
Unicode True

RequestExecutionLevel admin

Var StartMenuFolder

InstallDir "$LOCALAPPDATA\EventLog"
InstallDirRegKey HKLM "Software\EventLog" ""


!define MUI_ABORTWARNING
!define ARP "Software\Microsoft\Windows\CurrentVersion\Uninstall\EventLog"
!define MSVS_DIR "d:\msvs"
!define APP_BUILD_DIR "..\cmake-build-release"
!define UTIL_BUILD_DIR "..\cmake-build-release\_deps\utillib-build"
!define ODS_BUILD_DIR "..\cmake-build-release\_deps\odslib-build"
!define WORKFLOWAPP_BUILD_DIR "..\cmake-build-release\_deps\workflowapp-build"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "..\LICENSE"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY

!define MUI_STARTMENUPAGE_DEFAULTFOLDER "Event Log Applications"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKLM" 
!define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\EventLog"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
!insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder

!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
   
!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH
  
!insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections
Section "Visual Studio Runtime" MSCRT
  SectionIn RO
  SetRegView 64
  SetOutPath "$INSTDIR\bin"
  File "${MSVS_DIR}\VC_redist.x64.exe"
  ExecWait '"$INSTDIR\bin\VC_redist.x64.exe" /passive /norestart'
  Delete "$INSTDIR\bin\VC_redist.x64.exe.exe"
SectionEnd

Section "Applications" APP
  SectionIn RO
  SetRegView 64	
  SetShellVarContext all

  SetOutPath "$INSTDIR\bin"
  File "${UTIL_BUILD_DIR}\listend\*.exe"
  File "${UTIL_BUILD_DIR}\listenviewer\*.exe"
  File "${UTIL_BUILD_DIR}\serviced\serviced.exe"
  File "${UTIL_BUILD_DIR}\serviceexplorer\serviceexplorer.exe"
  
  File "${ODS_BUILD_DIR}\odsconfigurator\odsconfig.exe"

  File "${WORKFLOWAPP_BUILD_DIR}\workflowexplorer\workflowexplorer.exe"

  File "${APP_BUILD_DIR}\eventlogd\eventlogd.exe"
  
  SetOutPath "$INSTDIR\img"
  File "..\img\*.ico"
  
  ;Store installation folder
  WriteRegStr HKLM "Software\EventLog" "" $INSTDIR

  WriteRegNone HKLM "${ARP}" "" 
  WriteRegStr HKLM "${ARP}" "InstallLocation" $INSTDIR
  WriteRegStr HKLM "${ARP}" "DisplayIcon" "$INSTDIR\img\eventlog.ico"
  WriteRegStr HKLM "${ARP}" "DisplayName" "Event Log Applications 1.0"
  WriteRegStr HKLM "${ARP}" "DisplayVersion" "1.0.0"
  WriteRegStr HKLM "${ARP}" "Publisher" "Ingemar Hedvall" 
  WriteRegDWORD HKLM "${ARP}" "NoModify" 1 
  WriteRegDWORD HKLM "${ARP}" "NoRepair" 1 
  WriteRegDWORD HKLM "${ARP}" "VersionMajor" 1 
  WriteRegDWORD HKLM "${ARP}" "VersionMinor" 0 	  
			 
  WriteRegStr HKLM "${ARP}"  "UninstallString" "$\"$INSTDIR\Uninstall.exe$\""

  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
  CreateShortcut "$SMPROGRAMS\$StartMenuFolder\Listen Viewer.lnk" "$INSTDIR\bin\listenviewer.exe"
  CreateShortcut "$SMPROGRAMS\$StartMenuFolder\Service Explorer.lnk" "$INSTDIR\bin\serviceexplorer.exe"
  CreateShortcut "$SMPROGRAMS\$StartMenuFolder\ODS Configurator.lnk" "$INSTDIR\bin\odsconfig.exe"
  CreateShortcut "$SMPROGRAMS\$StartMenuFolder\Workflow Explorer.lnk" "$INSTDIR\bin\workflowexplorer.exe"
  !insertmacro MUI_STARTMENU_WRITE_END 
  
  ; Create Uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

  ; Add /Remove Programs
  ${GetSize} "$INSTDIR" "/S=0K" $0 $1 $2
  IntFmt $0 "0x%08X" $0
  WriteRegDWORD HKLM "${ARP}" "EstimatedSize" "$0"
SectionEnd

LangString DESC_CRT ${LANG_ENGLISH} "Microsoft Visual Studio Runtime."
LangString DESC_APP ${LANG_ENGLISH} "All Event Log Executables."

!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${MSCRT} $(DESC_CRT)
  !insertmacro MUI_DESCRIPTION_TEXT ${APP} $(DESC_APP)
!insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"
  SetRegView 64	  
  SetShellVarContext all
  !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder
  
  Delete "$INSTDIR\Uninstall.exe"

  RMDir /r "$INSTDIR"  
  RMDir /r "$SMPROGRAMS\$StartMenuFolder"
  
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\EventLog"
  DeleteRegKey HKLM "Software\EventLog"

SectionEnd