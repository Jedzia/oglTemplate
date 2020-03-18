@title 'OpenGLTemplate MSys2 Shell.'
@echo off
call %~dp0%config\config.bat

set CMAKE_GENERATOR=MSYS Makefiles

C:\msys64\msys2_shell_zsh.cmd -here -mingw64 -c "cat config/WelcomeShell.txt ; cd build ; zsh"