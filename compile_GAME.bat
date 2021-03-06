:: This file should be placed at the top level of your project
:: i.e. it should be in the same folder as the "src" folder (containing .cpp files)
:: and the "include" folder (containing .h files).

@echo Compiling your program...

@echo off
:: specify location where SDL2 is installed
set SDL2dir="c:\SDL2"
set SDL2libdir="c:\SDL2\lib\x64"

setlocal ENABLEDELAYEDEXPANSION
set cppfiles=
for /f %%i in ('dir GAMEsource\*.cpp /b /a-d') do (
    set cppfiles=!cppfiles! "GAMEsource\%%i"
)
for /f %%i in ('dir GAMEsource\storage\*.cpp /b /a-d') do (
    set cppfiles=!cppfiles! "GAMEsource\storage\%%i"
)
for /f %%i in ('dir GAMEsource\input\*.cpp /b /a-d') do (
    set cppfiles=!cppfiles! "GAMEsource\input\%%i"
)
for /f %%i in ('dir GAMEsource\output\*.cpp /b /a-d') do (
    set cppfiles=!cppfiles! "GAMEsource\output\%%i"
)
for /f %%i in ('dir GAMEsource\logic\*.cpp /b /a-d') do (
    set cppfiles=!cppfiles! "GAMEsource\logic\%%i"
)

echo on


mkdir BatVersion\obj


:: `cl` is the MSVC compiler

cl %cppfiles% /W3 /EHsc /std:c++latest /I GAMEsource\include /I %SDL2dir%\include /Fo.\BatVersion\obj\ /link /SUBSYSTEM:CONSOLE %SDL2libdir%\SDL2.lib %SDL2libdir%\SDL2main.lib /out:BatVersion\GAME.exe
if %errorlevel% neq 0 exit /b %errorlevel%

