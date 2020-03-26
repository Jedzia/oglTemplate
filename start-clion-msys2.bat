@title Launching Clion with 'OpenGLTemplate' settings.
@echo off
call %~dp0%config\config.bat

set HOME=%USERPROFILE%

REM set MAKEFLAGS=-j8

set CONSOLE_WIDTH=400
PATH=D:\tools\gnu\bin;%PATH%

start "" "C:\Program Files\JetBrains\CLion\bin\clion64.exe"

REM wait 
@REM sleep 8 seconds
@PING localhost -n 9 >NUL
