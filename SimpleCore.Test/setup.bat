@ECHO off
SETLOCAL
FOR /F "usebackq" %%f IN (`PowerShell -NoProfile -Command "Write-Host([Environment]::GetFolderPath('Desktop'))"`) DO (
  SET "DESKTOP_FOLDER=%%f"
  )

REM Copy testfile.txt to desktop
XCOPY testfile.txt %DESKTOP_FOLDER%

REM Copy testfile2.bin to desktop
XCOPY testfile2.bin %DESKTOP_FOLDER%

IF NOT EXIST %DESKTOP_FOLDER%\testdir MKDIR %DESKTOP_FOLDER%\testdir
