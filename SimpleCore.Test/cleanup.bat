@ECHO off
SETLOCAL
FOR /F "usebackq" %%f IN (`PowerShell -NoProfile -Command "Write-Host([Environment]::GetFolderPath('Desktop'))"`) DO (
  SET "DESKTOP_FOLDER=%%f"
  )

REM Remove directory testdir from desktop
RMDIR %DESKTOP_FOLDER%\testdir

REM Remove file testfile.txt from desktop
DEL %DESKTOP_FOLDER%\testfile.txt

REM Remove file testfile2.bin from desktop
DEL %DESKTOP_FOLDER%\testfile2.bin
