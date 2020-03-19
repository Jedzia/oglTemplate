REM echo %*
REM "C:\msys64\usr\bin\ccache.exe" %*

:: all_but_first.bat
REM echo all: %*
for /f "tokens=1,* delims= " %%a in ("%*") do set ALL_BUT_FIRST=%%b
REM echo all but first: %ALL_BUT_FIRST%

REM "C:\msys64\usr\bin\ccache.exe" "%1" %ALL_BUT_FIRST%
"C:\msys64\usr\bin\ccache.exe" "C:/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe" %ALL_BUT_FIRST%
